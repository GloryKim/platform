#(sf) a@b:~/glory/sf$ nohup uvicorn main:app --host 0.0.0.0 --port 12345 --reload > uvicorn_output.log 2>&1 &
#(sf) a@b:~/glory/sf$ nohup uvicorn main:app --host 0.0.0.0 --port 12345 > uvicorn_output.log 2>&1 &
'''
(sf) a@b:~/glory/sf$ lsof -i :12345
COMMAND    PID  USER   FD   TYPE   DEVICE SIZE/OFF NODE NAME
uvicorn 1111 black    3u  IPv4 1111      0t0  TCP *:14957 (LISTEN)
python3 2222 black    3u  IPv4 2222      0t0  TCP *:14957 (LISTEN)
'''
import uvicorn
from fastapi import FastAPI, File, Form, UploadFile, BackgroundTasks
from typing import List, Optional
import asyncio
import websockets
import json
import os
import requests
import base64
from datetime import datetime
import subprocess

app = FastAPI()

# --- 설정 값 ---
# • Node.js 웹소켓 주소 및 /receive-text URL
NODE_WS_ADDRESS = "ws://1.23.4.56:12000"
NODE_RECEIVE_TIMS_URL = "http://1.23.4.56:12000/receive"
# • Flask 서버(Stable Diffusion) URL
FLASK_GENERATE_URL = "http://127.0.0.1:23456/gen"  # glory
# • GPU 모니터링 활성화 플래그
GPU_MONITORING_ACTIVE = True
# • 웹소켓 메시지에 사용할 클라이언트 정보
client_info = {
    'type': 'add',
    'host': '3.45.6.78',  # Node.js에서 접근 가능한 공인IP
    'port': 45678             # glory: 바꿔야 함
}
# • LLaMA 3.3 번역 관련 설정 (GPU 3번 사용)
LLAMA_EXEC_CMD = (
    "CUDA_VISIBLE_DEVICES=0 ./obs.onnx "  # glory
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
# • 번역 후 LLaMA 출력에 포함되어야 하는 마커
MARKER = "no explanation or additional context."

# --- 유틸리티 함수 ---
def get_gpu_power_usage():
    # • GPU 전력 사용량 조회 (GPU 0)
    cmd = 'nvidia-smi -i 0 --query-gpu=power.draw --format=csv,noheader,nounits'
    result_str = os.popen(cmd).read().strip()
    try:
        return float(result_str)
    except Exception as e:
        print("GPU 사용량 측정 에러:", e)
        return 999.0

async def monitor_and_send_gpu_usage(uri, client_info):
    # • GPU 모니터링 및 웹소켓을 통해 데이터 전송
    global GPU_MONITORING_ACTIVE
    while True:
        try:
            async with websockets.connect(uri) as websocket:
                while True:
                    if GPU_MONITORING_ACTIVE:
                        power_usage = get_gpu_power_usage()
                        # - 전력 사용량 80W 미만일 때 메시지 전송
                        if power_usage < 80:
                            data_to_send = {
                                'type': client_info['type'],
                                'host': client_info['host'],
                                'ai_type': 2,
                                'port': client_info['port']
                            }
                            print("[GPU Monitor] Sending add message:", data_to_send)
                            await websocket.send(json.dumps(data_to_send))
                    await asyncio.sleep(5)
        except websockets.exceptions.ConnectionClosedError:
            print("[GPU Monitor] 웹소켓 연결 끊김. 5초 후 재시도...")
            await asyncio.sleep(5)
        except Exception as e:
            print("[GPU Monitor] 예외 발생:", e, "5초 후 재시도...")
            await asyncio.sleep(5)

def warmup_llama():
    # • LLAMA 모델 사전 로딩 (warmup query)
    print("Warming up LLAMA model on GPU 0...")
    dummy_prompt = "warmup query"
    llama_cmd = LLAMA_EXEC_CMD.format(prompt=dummy_prompt)
    try:
        result = subprocess.run(llama_cmd, shell=True, capture_output=True, text=True, timeout=120)
        print("Warmup result:", result.stdout)
    except subprocess.TimeoutExpired as e:
        print("LLAMA warmup 타임아웃:", e)
    except Exception as e:
        print("LLAMA warmup 실패:", e)

def translate_text(input_text: str) -> Optional[str]:
    # • LLaMA 3.3을 이용하여 입력 텍스트를 영어로 번역
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
        print("[translate_text] 마커 미포함")
        return None
    translated = full_output.split(MARKER, 1)[1].strip()
    return translated

# --- 백그라운드 작업 함수 ---
def background_process(user_rtext: str, folderName: str, cam_seq: str, user_id: str, user_seq: str):
    global GPU_MONITORING_ACTIVE
    print("[Background Process] 작업 시작")
    GPU_MONITORING_ACTIVE = False

    # 1. 텍스트 번역
    translated_text = translate_text(user_rtext)
    if not translated_text:
        print("[Background Process] 번역 실패")
        GPU_MONITORING_ACTIVE = True
        return
    print("[Background Process] 번역 성공:", translated_text)

    # 2. Flask 서버에 이미지 생성 요청
    flask_payload = {
        "prompts": [translated_text],
        "style_name": "Japanese animation"
    }
    try:
        print("[Background Process] Flask 서버 호출:", FLASK_GENERATE_URL)
        flask_resp = requests.post(FLASK_GENERATE_URL, json=flask_payload, timeout=30)
        flask_resp.raise_for_status()
        flask_data = flask_resp.json()
        if flask_data.get("status") != "success":
            print("[Background Process] Flask 서버 오류:", flask_data)
            GPU_MONITORING_ACTIVE = True
            return
        base64_images = flask_data.get("images", [])
        if not base64_images:
            print("[Background Process] Flask 서버에서 이미지 없음")
            GPU_MONITORING_ACTIVE = True
            return
    except Exception as e:
        print("[Background Process] Flask 서버 호출 예외:", e)
        GPU_MONITORING_ACTIVE = True
        return

    # 3. 생성된 이미지 로컬 저장
    now_str = datetime.now().strftime("%Y%m%d_%H%M%S")
    saved_files = []
    for idx, b64_str in enumerate(base64_images):
        file_bytes = base64.b64decode(b64_str)
        filename = f"{now_str}_{idx}.png"
        file_path = os.path.join("public", filename)
        with open(file_path, "wb") as f:
            f.write(file_bytes)
        saved_files.append(file_path)
        print(f"[Background Process] 생성 이미지 저장됨: {file_path}")

    # 4. Node.js 서버로 이미지 전송
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
        print("[Background Process] Node.js 서버에 이미지 전송:", NODE_RECEIVE_TIMS_URL)
        node_resp = requests.post(NODE_RECEIVE_TIMS_URL, files=files_to_upload, data=data_fields, timeout=20)
        print("[Background Process] Node.js 응답:", node_resp.status_code, node_resp.text)
    except Exception as e:
        print("[Background Process] Node.js 전송 예외:", e)

    GPU_MONITORING_ACTIVE = True

# --- API 엔드포인트 ---
@app.on_event("startup")
async def startup_event():
    print("=== FastAPI Startup ===")
    # • LLAMA 모델 사전 로딩 (동기 방식)
    warmup_llama()
    # • GPU 모니터링 백그라운드 태스크 등록
    loop = asyncio.get_event_loop()
    loop.create_task(monitor_and_send_gpu_usage(NODE_WS_ADDRESS, client_info))

@app.post("/upload")
async def upload(
    folderName: str = Form(...),
    cam_seq: str = Form(...),
    user_rtext: Optional[str] = Form(None),
    user_id: str = Form(...),
    user_seq: str = Form(...),
    images: List[UploadFile] = File([]),
    background_tasks: BackgroundTasks = None
):
    print("=== /upload 엔드포인트 진입 ===")
    print(f"folderName: {folderName}, cam_seq: {cam_seq}")
    print(f"user_id: {user_id}, user_seq: {user_seq}, user_rtext: {user_rtext}")

    # • 업로드된 파일을 "public" 디렉토리에 저장
    os.makedirs("public", exist_ok=True)
    for idx, img in enumerate(images):
        content = await img.read()
        file_path = os.path.join("public", img.filename)
        with open(file_path, "wb") as f:
            f.write(content)
        print(f"[upload] 파일 저장됨: {file_path}")

    # • user_rtext가 있는 경우 heavy 작업은 백그라운드에서 실행
    if user_rtext:
        background_tasks.add_task(background_process, user_rtext, folderName, cam_seq, user_id, user_seq)
        # - 요청 수신 시 바로 200 응답 반환 (heavy 작업은 백그라운드에서 진행)
        return {
            "status": "accepted",
            "message": "@@@@님 안녕하십니까? 여기는 0번 GPU 입니다."
        }
    else:
        return {
            "status": "ok",
            "message": "번역/이미지 생성 요청 없음",
            "cam_seq": cam_seq
        }

@app.get("/health")
def health_check():
    return {"status": "ok"}

if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=12345, reload=False)
