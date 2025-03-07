#(SD) fast@api:~/$ nohup uvicorn main:app --host 0.0.0.0 --port 12345 --reload > uvicorn_output_gpu4.log 2>&1 &

'''
(SD) fast@api:~/$ lsof -i :12345
'''

import uvicorn
from fastapi import FastAPI, File, Form, UploadFile
from typing import List, Optional
import asyncio
import websockets
import secrets
import json
import os
import threading
import requests
import base64
from datetime import datetime
import subprocess

app = FastAPI()

# Node.js 웹소켓 주소 입력란, 필드명 : /receive-text
NODE_WS_ADDRESS = "ws://1.2.3.4:33333"
NODE_RECEIVE_TIMS_URL = "http://1.2.3.4:33333/receive-text"

# AI 처리를 위한 Flask 서버, 필드명 : /generate
FLASK_GENERATE_URL = "http://2.3.4.5:44444/generate" 

# GPU 모니터링 활성화 플래그
GPU_MONITORING_ACTIVE = True

# 웹소켓 메시지에 사용할 클라이언트 정보
client_info = {
    'type': 'hello',
    'host': '4.5.6.7',  # Node.js에서 접근 가능한 본 서버용 공인IP
    'port': 14141 #250307_1011_glory : 포트포워딩, 외부 14141 내부 12345
}

# LLaMA 3.3 based on abc 번역 관련 설정 (GPU 4번 사용)
LLAMA_EXEC_CMD = (
    "CUDA_VISIBLE_DEVICES=4 ./abc.llamafile "
    "--cli "
    '-p "{prompt}" '
    "--log-disable "
    "--temp 0.2 "
    "--predict 50 "
    "--repeat-penalty 1.18 "
    "--repeat-last-n 256 "
    "--top-k 40 "
    "--top-p 0.5 "
    "--min-p 0.0"
)

# 번역 후 LLaMA 출력에 포함되어야 하는 마커
MARKER = "no explanation or additional context."

# 유틸리티 함수들
def get_gpu_power_usage():
    cmd = 'nvidia-smi -i 4 --query-gpu=power.draw --format=csv,noheader,nounits' #4번 GPU 활용
    result_str = os.popen(cmd).read().strip()
    try:
        return float(result_str)
    except Exception as e:
        print("GPU 사용량 측정 에러:", e)
        return 999.0

async def monitor_and_send_gpu_usage(uri, client_info):
    global GPU_MONITORING_ACTIVE
    while True:
        try:
            async with websockets.connect(uri) as websocket:
                while True:
                    if GPU_MONITORING_ACTIVE:
                        power_usage = get_gpu_power_usage()
                        # 임의 기준(예: 77W 미만)일 때만 메시지 전송
                        if power_usage < 77:
                            data_to_send = {
                                'type': client_info['type'],
                                'host': client_info['host'],
                                'ai_type': 4,  # 예시 값 (TTIS)
                                'port': client_info['port']
                            }
                            print("[GPU Monitor] Sending add message:", data_to_send)
                            await websocket.send(json.dumps(data_to_send))
                    await asyncio.sleep(5)
        except websockets.exceptions.ConnectionClosedError:
            print("[GPU Monitor] 웹소켓 연결이 끊김. 5초 후 재시도...")
            await asyncio.sleep(5)
        except Exception as e:
            print("[GPU Monitor] 예외 발생:", e, "5초 후 재시도...")
            await asyncio.sleep(5)

def start_gpu_monitoring():
    asyncio.run(monitor_and_send_gpu_usage(NODE_WS_ADDRESS, client_info))

#llama 미리 올리기
def warmup_llama():
    print("Warming up LLAMA model on GPU 4...")
    dummy_prompt = "warmup query"
    llama_cmd = LLAMA_EXEC_CMD.format(prompt=dummy_prompt)
    try:
        # 타임아웃 120초.
        result = subprocess.run(llama_cmd, shell=True, capture_output=True, text=True, timeout=120)
        print("Warmup result:", result.stdout)
    except subprocess.TimeoutExpired as e:
        print("LLAMA warmup 타임아웃 ㅇㅁㅇ", e)
        # 타임아웃이 발생해도 에러 무시 후 진행
    except Exception as e:
        print("LLAMA warmup 실패 ㅜㅜ", e)

def translate_text(input_text: str) -> Optional[str]: #250307_1009_glory : 입력테스트를 영어로 번역 기능
    prompt = f'{input_text} Translate this text into only English. Provide only the translation, no explanation or additional context.'
    llama_cmd = LLAMA_EXEC_CMD.format(prompt=prompt)
    print("[translate_text] LLaMA 명령어:", llama_cmd)
    try:
        result = subprocess.run(llama_cmd, shell=True, capture_output=True, text=True, timeout=20)
    except subprocess.TimeoutExpired as e:
        print("[translate_text] 타임아웃 발생:", e)
        return None
    except Exception as e:
        print("[translate_text] 실행 중 예외 발생:", e)
        return None

    if result.returncode != 0:
        print("[translate_text] LLaMA 실행 실패:", result.stderr)
        return None

    full_output = result.stdout.strip()
    print("[translate_text] LLaMA 전체 출력:", full_output)
    if MARKER not in full_output:
        print("[translate_text] 마커가 출력에 없음.")
        return None
    translated = full_output.split(MARKER, 1)[1].strip()
    return translated

# ---------- API 엔드포인트 ----------
@app.on_event("startup")
def on_startup():
    print("=== FastAPI Startup ===")
    # LLAMA 모델을 미리 로딩
    warmup_llama()
    # GPU 모니터링 시작
    threading.Thread(target=start_gpu_monitoring, daemon=True).start()

#250307_1010_glory : 이미지 전달 받으면 돌려 보내는 기능
@app.post("/upload")
async def upload(
    folderName: str = Form(...),
    cam_seq: str = Form(...),
    user_rtext: Optional[str] = Form(None),
    user_id: str = Form(...),
    user_seq: str = Form(...),
    images: List[UploadFile] = File([])
):
    global GPU_MONITORING_ACTIVE
    print("=== /upload 엔드포인트 진입 ===")
    print(f"folderName: {folderName}, cam_seq: {cam_seq}")
    print(f"user_id: {user_id}, user_seq: {user_seq}, user_rtext: {user_rtext}")

    os.makedirs("public", exist_ok=True)
    # 원본 이미지 저장
    for idx, img in enumerate(images):
        content = await img.read()
        file_path = os.path.join("public", img.filename)
        with open(file_path, "wb") as f:
            f.write(content)
        print(f"[upload] 파일 저장됨: {file_path}")

    # user_rtext가 있을 경우 번역 및 이미지 생성 진행
    if user_rtext:
        print("[upload] user_rtext 감지 → GPU 모니터링 OFF")
        GPU_MONITORING_ACTIVE = False

        # 1) 텍스트 번역
        translated_text = translate_text(user_rtext)
        if not translated_text:
            print("[upload] 번역 실패")
            GPU_MONITORING_ACTIVE = True
            return {"status": "failed", "error": "번역 실패"}
        print("[upload] 번역 성공:", translated_text)

        # 2) Flask 서버에 이미지 생성 요청
        flask_payload = {
            "prompts": [translated_text],
            "style_name": "Japanese animation"
        }
        try:
            print("[upload] Flask 서버 호출:", FLASK_GENERATE_URL)
            flask_resp = requests.post(FLASK_GENERATE_URL, json=flask_payload, timeout=30)
            flask_resp.raise_for_status()
            flask_data = flask_resp.json()
            if flask_data.get("status") != "success":
                print("[upload] Flask 서버 오류:", flask_data)
                GPU_MONITORING_ACTIVE = True
                return {"status": "failed", "error": "Flask 서버 오류"}
            base64_images = flask_data.get("images", [])
            if not base64_images:
                print("[upload] Flask 서버에서 이미지 없음")
                GPU_MONITORING_ACTIVE = True
                return {"status": "failed", "error": "이미지 생성 실패"}
        except Exception as e:
            print("[upload] Flask 서버 호출 예외:", e)
            GPU_MONITORING_ACTIVE = True
            return {"status": "failed", "error": "Flask 서버 호출 중 오류"}

        # 3) 생성된 이미지를 로컬에 저장 후 Node.js로 전달
        now_str = datetime.now().strftime("%Y%m%d_%H%M%S")
        saved_files = []
        for idx, b64_str in enumerate(base64_images):
            file_bytes = base64.b64decode(b64_str)
            filename = f"{now_str}_{idx}.png"
            file_path = os.path.join("public", filename)
            with open(file_path, "wb") as f:
                f.write(file_bytes)
            saved_files.append(file_path)
            print(f"[upload] 생성 이미지 저장됨: {file_path}")

        # Node.js로 이미지 전달
        files_to_upload = []
        for fp in saved_files:
            with open(fp, "rb") as f:
                files_to_upload.append(("file", (os.path.basename(fp), f.read(), "image/png")))
        data_fields = {
            "cam_seq": cam_seq,
            "user_id": user_id,
            "user_seq": user_seq
        }
        try:
            print("[upload] Node.js 서버에 이미지 전송:", NODE_RECEIVE_TIMS_URL)
            node_resp = requests.post(NODE_RECEIVE_TIMS_URL, files=files_to_upload, data=data_fields, timeout=20)
            print("[upload] Node.js 응답:", node_resp.status_code, node_resp.text)
        except Exception as e:
            print("[upload] Node.js 전송 중 예외 발생:", e)

        GPU_MONITORING_ACTIVE = True

        return {
            "status": "ok",
            "translated_text": translated_text,
            "images": base64_images
        }
    else:
        print("[upload] user_rtext 없음 → 번역/이미지 생성 생략")
        return {
            "status": "ok",
            "message": "번역/이미지 생성 요청 없음.",
            "cam_seq": cam_seq
        }

@app.get("/health")
def health_check():
    return {"status": "ok"}

if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=12345, reload=True)