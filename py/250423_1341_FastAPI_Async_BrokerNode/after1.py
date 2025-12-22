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

from fastapi import FastAPI, File, UploadFile, Form, BackgroundTasks
from fastapi.responses import JSONResponse

app = FastAPI()

# • 경로 설정
UPLOAD_DIR = "./uploads"                # 일반 업로드/ZIP 경로
ZIP_FILE_PATH = "./uploads/uploaded_images.zip"
TIMS_UPLOAD_DIR = "./uploads_folder"       # TIMS 업로드/ZIP 경로 (작업용)
TIMS_ZIP_FILE_PATH = "./uploads_folder/uploads_images.zip"

# • 외부 서버 설정
FLASK_SERVER_URL = "http://127.0.0.1:44147/process"  # Flask 서버 엔드포인트
NODE_SERVER_URL = "http://123.456.789.01:12000/receive"
NODE_TIMS_SERVER_URL = "http://123.456.789.01:12000/receive2"
NODE_WS_ADDRESS = "ws://123.456.789.01:12000"

# • GPU 모니터링 상태
GPU_MONITORING_ACTIVE = True

# • WebSocket 통신 시 전송할 클라이언트 정보
client_info = {
    "type": "add",
    "host": "234.123.234.12",  # 외부 접근 가능한 IP
    "port": 2222            # 외부 접근 포트 2222 -> 1111
}

# • 디렉토리 초기 세팅 (존재하지 않으면 생성)
os.makedirs(UPLOAD_DIR, exist_ok=True)
os.makedirs(TIMS_UPLOAD_DIR, exist_ok=True)

# • GPU 전력 사용량 함수
def get_gpu_power_usage():
    # - GPU 1번 전력 사용량 조회, 실패 시 999.0 반환
    cmd = "nvidia-smi -i 1 --query-gpu=power.draw --format=csv,noheader,nounits"
    result_str = os.popen(cmd).read().strip()
    try:
        return float(result_str)
    except:
        return 999.0

# • GPU 모니터링 및 웹소켓 전송 코루틴
async def monitor_and_send_gpu_usage(uri: str, client_info: dict):
    global GPU_MONITORING_ACTIVE
    while True:
        try:
            print(f"[monitor_and_send_gpu_usage] {uri}에 연결 시도")
            async with websockets.connect(uri) as websocket:
                print("[monitor_and_send_gpu_usage] 웹소켓 연결 성공")
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
                            print("[monitor_and_send_gpu_usage] 메시지 전송:", data_to_send)
                            await websocket.send(json.dumps(data_to_send))
                    await asyncio.sleep(5)
        except websockets.exceptions.ConnectionClosedError:
            print("[monitor_and_send_gpu_usage] 연결 종료. 5초 후 재시도")
            await asyncio.sleep(5)
        except Exception as e:
            print("[monitor_and_send_gpu_usage] 예외:", e)
            await asyncio.sleep(5)

@app.on_event("startup")
async def on_startup():
    print("=== FastAPI Startup ===")
    loop = asyncio.get_event_loop()
    loop.create_task(monitor_and_send_gpu_usage(NODE_WS_ADDRESS, client_info))

# ★ 백그라운드 작업 함수: /upload 엔드포인트 처리
def process_upload(saved_path: str, folderName: str, cam_seq: str, user_id: str, user_seq: str):
    global GPU_MONITORING_ACTIVE
    print("[process_upload] 백그라운드 작업 시작")
    GPU_MONITORING_ACTIVE = False

    try:
        # • Flask 서버에 이미지 전송 및 프레임 이미지 받기
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
                print(f"[process_upload] 프레임 저장: {frame_path}")
        else:
            print(f"[process_upload] Flask 에러: {flask_resp.status_code}, {flask_resp.text}")
            return

        # • frame으로 시작하는 파일 압축 (ZIP)
        with zipfile.ZipFile(TIMS_ZIP_FILE_PATH, 'w') as zipf:
            for root, _, filenames in os.walk(TIMS_UPLOAD_DIR):
                for filename in filenames:
                    if filename.startswith("frame"):
                        filepath = os.path.join(root, filename)
                        arcname = os.path.relpath(filepath, TIMS_UPLOAD_DIR)
                        zipf.write(filepath, arcname)
                        print(f"[process_upload] 압축 파일에 추가: {filepath}")

        # • Node.js TIMS 서버에 ZIP 파일 전송
        with open(TIMS_ZIP_FILE_PATH, 'rb') as zip_file:
            files_to_send = {"file": zip_file}
            response = requests.post(
                NODE_TIMS_SERVER_URL, 
                files=files_to_send,
                data={"user_id": user_id, "user_seq": user_seq, "cam_seq": cam_seq}
            )
        print(f"[process_upload] Node.js 응답: {response.status_code}, {response.text}")
    except Exception as e:
        print("[process_upload] 예외 발생:", e)
    finally:
        # • 작업 완료 후 TIMS 디렉토리 및 ZIP 파일 삭제
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        if os.path.exists(TIMS_ZIP_FILE_PATH):
            os.remove(TIMS_ZIP_FILE_PATH)
        GPU_MONITORING_ACTIVE = True
        print("[process_upload] 백그라운드 작업 종료")

# ★ 백그라운드 작업 함수: /upload-images 엔드포인트 처리
def process_upload_images():
    try:
        with zipfile.ZipFile(ZIP_FILE_PATH, 'w') as zipf:
            for root, _, filenames in os.walk(UPLOAD_DIR):
                for filename in filenames:
                    filepath = os.path.join(root, filename)
                    arcname = os.path.relpath(filepath, UPLOAD_DIR)
                    zipf.write(filepath, arcname)
                    print(f"[process_upload_images] 압축 추가: {filepath}")

        with open(ZIP_FILE_PATH, 'rb') as zip_file:
            files_to_send = {"file": zip_file}
            response = requests.post(NODE_SERVER_URL, files=files_to_send)
        print(f"[process_upload_images] Node.js 응답: {response.status_code}, {response.text}")
    except Exception as e:
        print("[process_upload_images] 예외 발생:", e)
    finally:
        if os.path.exists(UPLOAD_DIR):
            shutil.rmtree(UPLOAD_DIR)
        if os.path.exists(ZIP_FILE_PATH):
            os.remove(ZIP_FILE_PATH)
        print("[process_upload_images] 작업 종료")

# ★ 백그라운드 작업 함수: /upload-images-tims 엔드포인트 처리
def process_upload_images_tims():
    try:
        with zipfile.ZipFile(TIMS_ZIP_FILE_PATH, 'w') as zipf:
            for root, _, filenames in os.walk(TIMS_UPLOAD_DIR):
                for filename in filenames:
                    filepath = os.path.join(root, filename)
                    arcname = os.path.relpath(filepath, TIMS_UPLOAD_DIR)
                    zipf.write(filepath, arcname)
                    print(f"[process_upload_images_tims] 압축 추가: {filepath}")

        with open(TIMS_ZIP_FILE_PATH, 'rb') as zip_file:
            files_to_send = {"file": zip_file}
            response = requests.post(NODE_TIMS_SERVER_URL, files=files_to_send)
        print(f"[process_upload_images_tims] Node.js 응답: {response.status_code}, {response.text}")
    except Exception as e:
        print("[process_upload_images_tims] 예외 발생:", e)
    finally:
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        if os.path.exists(TIMS_ZIP_FILE_PATH):
            os.remove(TIMS_ZIP_FILE_PATH)
        print("[process_upload_images_tims] 작업 종료")

# ★ /upload 엔드포인트: TIMS 처리 (백그라운드 작업으로 heavy 처리)
@app.post("/upload")
async def upload_file(
    image: UploadFile = File(...),
    folderName: str = Form(...),
    cam_seq: str = Form(...),
    user_id: str = Form(...),
    user_seq: str = Form(...),
    background_tasks: BackgroundTasks = None
):
    global GPU_MONITORING_ACTIVE
    try:
        GPU_MONITORING_ACTIVE = False
        # • TIMS_UPLOAD_DIR 재생성 (이전 파일 제거)
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        os.makedirs(TIMS_UPLOAD_DIR)

        # • 업로드 파일 저장 (비동기 파일 I/O)
        saved_path = os.path.join(TIMS_UPLOAD_DIR, image.filename)
        async with aiofiles.open(saved_path, 'wb') as out_file:
            content = await image.read()
            await out_file.write(content)
        print(f"[upload] 파일 저장됨: {saved_path}")

        # • heavy 작업은 백그라운드에서 실행
        background_tasks.add_task(process_upload, saved_path, folderName, cam_seq, user_id, user_seq)

        # • 즉시 200 응답 반환
        return JSONResponse(
            content={"status": "accepted", "message": "요청 수신, 백그라운드 처리 중"},
            status_code=200
        )
    except Exception as e:
        return JSONResponse(content={"error": str(e)}, status_code=500)

# ★ /upload-images 엔드포인트: 일반 이미지 업로드 (백그라운드 처리)
@app.post("/upload-images")
async def upload_images(files: List[UploadFile] = File(...), background_tasks: BackgroundTasks = None):
    try:
        if os.path.exists(UPLOAD_DIR):
            shutil.rmtree(UPLOAD_DIR)
        os.makedirs(UPLOAD_DIR)
        for file in files:
            filepath = os.path.join(UPLOAD_DIR, file.filename)
            async with aiofiles.open(filepath, 'wb') as out_file:
                content = await file.read()
                await out_file.write(content)
            print(f"[upload-images] 파일 저장됨: {filepath}")
        background_tasks.add_task(process_upload_images)
        return JSONResponse(
            content={"status": "accepted", "message": "이미지 업로드 수신, 백그라운드 처리 중"},
            status_code=200
        )
    except Exception as e:
        return JSONResponse(content={"error": str(e)}, status_code=500)

# ★ /upload-images-tims 엔드포인트: TIMS 이미지 업로드 (백그라운드 처리)
@app.post("/upload-images-tims")
async def upload_images_tims(files: List[UploadFile] = File(...), background_tasks: BackgroundTasks = None):
    try:
        if os.path.exists(TIMS_UPLOAD_DIR):
            shutil.rmtree(TIMS_UPLOAD_DIR)
        os.makedirs(TIMS_UPLOAD_DIR)
        for file in files:
            filepath = os.path.join(TIMS_UPLOAD_DIR, file.filename)
            async with aiofiles.open(filepath, 'wb') as out_file:
                content = await file.read()
                await out_file.write(content)
            print(f"[upload-images-tims] 파일 저장됨: {filepath}")
        background_tasks.add_task(process_upload_images_tims)
        return JSONResponse(
            content={"status": "accepted", "message": "TIMS 이미지 업로드 수신, 백그라운드 처리 중"},
            status_code=200
        )
    except Exception as e:
        return JSONResponse(content={"error": str(e)}, status_code=500)

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=1111)
