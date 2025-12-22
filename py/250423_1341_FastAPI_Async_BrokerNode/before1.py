'''
INFO:     Finished server process [2502880]
(p---b) a@b:~/glory/P---$ nohup uvicorn broker:app --host 0.0.0.0 --port 1111 > fastapi.log 2>&1 &
'''

import asyncio
import os
import shutil
import zipfile
import requests
import websockets
import json
import aiofiles
from typing import List
from datetime import datetime
import base64
from io import BytesIO
from PIL import Image

from fastapi import FastAPI, File, UploadFile, Form
from fastapi.responses import JSONResponse

app = FastAPI()

# 경로 설정
UPLOAD_DIR = "./uploads"                # 일반 업로드/ZIP 경로
ZIP_FILE_PATH = "./uploads/uploaded_images.zip"
TIMS_UPLOAD_DIR = "./uploads_folder"       # TIMS 업로드/ZIP 경로 (작업용)
TIMS_ZIP_FILE_PATH = "./uploads_folder/uploaded_images.zip"

# 외부 서버 설정
FLASK_SERVER_URL = "http://127.0.0.1:44147/process"  # Flask 서버 엔드포인트
NODE_SERVER_URL = "http://123.456.789.01:12000/receive"
NODE_TIMS_SERVER_URL = "http://123.456.789.01:12000/receive2"
NODE_WS_ADDRESS = "ws://123.456.789.01:12000"

# GPU 모니터링 상태
GPU_MONITORING_ACTIVE = True

# WebSocket 통신 시 전송할 클라이언트 정보
client_info = {
    "type": "add",
    "host": "234.123.234.12",  # 외부 접근 가능한 IP
    "port": 2222            # 외부 접근 포트 2222 -> 1111
}

# 디렉토리 초기 세팅
if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR)
if not os.path.exists(TIMS_UPLOAD_DIR):
    os.makedirs(TIMS_UPLOAD_DIR)

def get_gpu_power_usage():
    # nvidia-smi 명령어로 GPU 전력 사용량 추출
    # GPU 1번 모니터링, 실패 시 999.0 반환
    cmd = "nvidia-smi -i 1 --query-gpu=power.draw --format=csv,noheader,nounits"
    result_str = os.popen(cmd).read().strip()
    try:
        return float(result_str)
    except:
        return 999.0

async def monitor_and_send_gpu_usage(uri: str, client_info: dict):
    # GPU 모니터링 코루틴
    # - WebSocket 연결 시도
    # - 일정 주기로 전력 사용량 검사, 80W 미만이면 메시지 전송
    global GPU_MONITORING_ACTIVE
    while True:
        try:
            print(f"[monitor_and_send_gpu_usage] Attempting to connect to {uri}...")
            async with websockets.connect(uri) as websocket:
                print("[monitor_and_send_gpu_usage] WebSocket connection established.")
                while True:
                    if GPU_MONITORING_ACTIVE:
                        power_usage = get_gpu_power_usage()
                        if power_usage < 80:
                            data_to_send = {
                                "type": client_info["type"],
                                "host": client_info["host"],
                                "ai_type": 1,
                                "port": client_info["port"]
                            }
                            print("[monitor_and_send_gpu_usage] Sending add message:", data_to_send)
                            await websocket.send(json.dumps(data_to_send))
                    await asyncio.sleep(5)
        except websockets.exceptions.ConnectionClosedError:
            print("[monitor_and_send_gpu_usage] WebSocket disconnected. Retrying in 5 seconds...")
            await asyncio.sleep(5)
        except Exception as e:
            print("[monitor_and_send_gpu_usage] Exception occurred:", e)
            await asyncio.sleep(5)

@app.on_event("startup")
async def on_startup():
    # FastAPI 시작 시 백그라운드에서 GPU 모니터링 태스크 실행
    print("=== FastAPI Startup ===")
    loop = asyncio.get_event_loop()
    loop.create_task(monitor_and_send_gpu_usage(NODE_WS_ADDRESS, client_info))

@app.post("/upload")
async def upload_file(
    image: UploadFile = File(...),
    folderName: str = Form(...),
    cam_seq: str = Form(...),
    user_id: str = Form(...),
    user_seq: str = Form(...)
):
    # /upload 엔드포인트
    # 1. GPU 모니터링 중지
    # 2. 수신 이미지 TIMS_UPLOAD_DIR에 저장
    # 3. Flask 서버에 이미지 전송 → 처리 결과(프레임) 응답 대기
    # 4. 응답 받은 파일 중 frame으로 시작하는 것만 ZIP 압축
    # 5. Node.js 서버에 ZIP 파일 전송
    # 6. GPU 모니터링 재개
    global GPU_MONITORING_ACTIVE
    try:
        GPU_MONITORING_ACTIVE = False

        # 기존 TIMS 폴더 삭제 후 재생성
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        os.makedirs(TIMS_UPLOAD_DIR)

        # 이미지 수신 후 로컬 저장
        saved_path = os.path.join(TIMS_UPLOAD_DIR, image.filename)
        async with aiofiles.open(saved_path, 'wb') as out_file:
            content = await image.read()
            await out_file.write(content)

        # Flask 서버에 이미지 전송 및 프레임 이미지 받기
        try:
            with open(saved_path, 'rb') as f:
                files = {'image': f}
                flask_resp = requests.post(FLASK_SERVER_URL, files=files)
            if flask_resp.status_code == 200:
                data = flask_resp.json()
                frames = data.get('frames', [])
                for i, frame_b64 in enumerate(frames):
                    frame_bytes = base64.b64decode(frame_b64)
                    frame_image = Image.open(BytesIO(frame_bytes))
                    frame_path = os.path.join(TIMS_UPLOAD_DIR, f"frame_{i}.png")
                    frame_image.save(frame_path)
            else:
                print(f"[FLASK ERROR] status_code={flask_resp.status_code}, msg={flask_resp.text}")
                return JSONResponse(
                    content={"error": "Flask 처리 실패", "details": flask_resp.text},
                    status_code=flask_resp.status_code
                )
        except Exception as e:
            print("[Exception] Flask 요청 에러:", e)
            return JSONResponse(
                content={"error": "Flask 서버 통신 오류", "details": str(e)},
                status_code=500
            )

        # frame으로 시작하는 파일만 ZIP으로 압축
        with zipfile.ZipFile(TIMS_ZIP_FILE_PATH, 'w') as zipf:
            for root, _, filenames in os.walk(TIMS_UPLOAD_DIR):
                for filename in filenames:
                    if filename.startswith("frame"):
                        filepath = os.path.join(root, filename)
                        arcname = os.path.relpath(filepath, TIMS_UPLOAD_DIR)
                        zipf.write(filepath, arcname)

        # Node.js 서버에 ZIP 파일 전송
        with open(TIMS_ZIP_FILE_PATH, 'rb') as zip_file:
            files_to_send = {"file": zip_file}
            response = requests.post(
                NODE_TIMS_SERVER_URL, 
                files=files_to_send,
                data={"user_id": user_id, "user_seq": user_seq, "cam_seq": cam_seq}
            )

        if response.status_code == 200:
            return JSONResponse(
                content={
                    "message": "파일 업로드+Flask처리+Node.js 전송 완료",
                    "flask_status": flask_resp.status_code,
                    "node_response": response.json()
                },
                status_code=200
            )
        else:
            return JSONResponse(
                content={
                    "error": "Node.js 서버 전송 실패",
                    "details": response.text
                },
                status_code=response.status_code
            )
    except Exception as e:
        return JSONResponse(content={"error": str(e)}, status_code=500)
    finally:
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        if os.path.exists(TIMS_ZIP_FILE_PATH):
            os.remove(TIMS_ZIP_FILE_PATH)
        GPU_MONITORING_ACTIVE = True

@app.post("/upload-images")
async def upload_images(files: List[UploadFile] = File(...)):
    # 일반 업로드 엔드포인트 (변경 없음)
    try:
        if os.path.exists(UPLOAD_DIR):
            shutil.rmtree(UPLOAD_DIR)
        os.makedirs(UPLOAD_DIR)

        for file in files:
            filepath = os.path.join(UPLOAD_DIR, file.filename)
            async with aiofiles.open(filepath, 'wb') as out_file:
                content = await file.read()
                await out_file.write(content)

        with zipfile.ZipFile(ZIP_FILE_PATH, 'w') as zipf:
            for root, _, filenames in os.walk(UPLOAD_DIR):
                for filename in filenames:
                    filepath = os.path.join(root, filename)
                    arcname = os.path.relpath(filepath, UPLOAD_DIR)
                    zipf.write(filepath, arcname)

        with open(ZIP_FILE_PATH, 'rb') as zip_file:
            files_to_send = {"file": zip_file}
            response = requests.post(NODE_SERVER_URL, files=files_to_send)

        if response.status_code == 200:
            return JSONResponse(
                content={
                    "message": "Images sent successfully",
                    "response": response.json()
                },
                status_code=200
            )
        else:
            return JSONResponse(
                content={
                    "error": "Failed to send images",
                    "details": response.text
                },
                status_code=response.status_code
            )
    except Exception as e:
        return JSONResponse(content={"error": str(e)}, status_code=500)
    finally:
        if os.path.exists(UPLOAD_DIR):
            shutil.rmtree(UPLOAD_DIR)
        if os.path.exists(ZIP_FILE_PATH):
            os.remove(ZIP_FILE_PATH)

@app.post("/upload-images-tims")
async def upload_images_tims(files: List[UploadFile] = File(...)):
    # TIMS 업로드 엔드포인트 (변경 없음)
    try:
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        os.makedirs(TIMS_UPLOAD_DIR)

        for file in files:
            filepath = os.path.join(TIMS_UPLOAD_DIR, file.filename)
            async with aiofiles.open(filepath, 'wb') as out_file:
                content = await file.read()
                await out_file.write(content)

        with zipfile.ZipFile(TIMS_ZIP_FILE_PATH, 'w') as zipf:
            for root, _, filenames in os.walk(TIMS_UPLOAD_DIR):
                for filename in filenames:
                    filepath = os.path.join(root, filename)
                    arcname = os.path.relpath(filepath, TIMS_UPLOAD_DIR)
                    zipf.write(filepath, arcname)

        with open(TIMS_ZIP_FILE_PATH, 'rb') as zip_file:
            files_to_send = {"file": zip_file}
            response = requests.post(NODE_TIMS_SERVER_URL, files=files_to_send)

        if response.status_code == 200:
            return JSONResponse(
                content={
                    "message": "TIMS images sent successfully",
                    "response": response.json()
                },
                status_code=200
            )
        else:
            return JSONResponse(
                content={
                    "error": "Failed to send TIMS images",
                    "details": response.text
                },
                status_code=response.status_code
            )
    except Exception as e:
        return JSONResponse(content={"error": str(e)}, status_code=500)
    finally:
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        if os.path.exists(TIMS_ZIP_FILE_PATH):
            os.remove(TIMS_ZIP_FILE_PATH)

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=1111)
