import uvicorn
from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse
from PIL import Image
import io
import ssl
import asyncio
import os

# FastAPI 인스턴스를 생성
# FastAPI는 웹 API를 빠르고 쉽게 개발할 수 있게 해주는 Python 웹 프레임워크
app = FastAPI()

# 이미지 처리 함수 정의
def process_image(content, folder_name, cam_seq, user_id, user_seq):
    try:
        # 받은 이미지 데이터를 PIL Image 객체로 변환
        # io.BytesIO를 사용해 바이트 데이터를 파일처럼 사용 가능하도록 변환 후, PIL의 Image.open으로 이미지 열기
        image = Image.open(io.BytesIO(content))

        # 이미지 모드가 RGBA이면 RGB로 변환
        # RGBA 모드(알파 채널 포함)는 JPG 형식과 호환되지 않으므로, 변환 필요
        if image.mode == 'RGBA':
            image = image.convert('RGB')

        # 이미지 처리 (예: 크기 확인)
        # PIL 라이브러리를 사용하여 이미지의 너비와 높이를 가져옴
        width, height = image.size

        # 폴더 생성
        # os.makedirs를 사용해 폴더가 없을 경우 생성, exist_ok=True 옵션으로 이미 폴더가 있어도 오류 없이 진행
        os.makedirs(folder_name, exist_ok=True)

        # 파일명 생성
        # 카메라 순번, 사용자 ID, 사용자 순번을 기반으로 이미지 파일명 생성
        filename = f"{cam_seq}_{user_id}_{user_seq}.jpg"
        filepath = os.path.join(folder_name, filename)

        # 처리된 이미지 저장
        # 처리한 이미지를 JPEG 형식으로 지정한 경로에 저장
        image.save(filepath, format="JPEG")

        # 성공 메시지와 이미지 크기 반환
        return f"Image processed and saved as {filename}", f"{width}x{height}"
    except Exception as e:
        # 예외 발생 시, 오류 메시지 반환
        return f"Error processing image: {str(e)}", None

# /upload 경로에 대해 POST 요청 처리
@app.post("/upload")
async def receive_image(request: Request):
    # 요청에서 바디(body) 내용을 읽어 이미지 데이터로 가져옴
    # await를 사용해 비동기적으로 요청 본문을 처리하여 네트워크 I/O를 효율적으로 처리함
    content = await request.body()
    
    try:
        # 임시로 하드코딩된 값들 (실제로는 이 값들을 요청에서 받아와야 함)
        # 이 부분은 실제 애플리케이션에서 요청으로부터 데이터를 가져오는 방식으로 개선 필요
        folder_name = "received_images"
        cam_seq = "cam1"
        user_id = "user123"
        user_seq = "seq1"

        # 이미지 처리를 백그라운드에서 실행
        # asyncio.get_running_loop()를 사용해 현재 실행 중인 이벤트 루프를 가져옴
        # run_in_executor를 사용해 비동기식으로 CPU 바운드 작업(이미지 처리)을 실행
        # 241005_1309_glory : 작업 요청이 들어오면 요청 들어온 서버에게 바로 연락을 보내는데, 그렇개 하면 이미지 처리가 오래 걸릴경우 끝나지도 않았는데 응답을 보낼지 모르니 그 과정을 위해서 이벤트 루프를 만들어서 작업이 완료되고 나면 보내는 방법을 수행하는 것임
        loop = asyncio.get_running_loop()
        message, size = await loop.run_in_executor(None, process_image, content, folder_name, cam_seq, user_id, user_seq)

        # 이미지 처리가 성공적으로 완료된 경우 메시지와 이미지 크기 반환
        if size:
            return JSONResponse(content={
                "message": message,
                "size": size
            }, status_code=200)
        else:
            # 이미지 처리 중 오류 발생 시 오류 메시지 반환
            return JSONResponse(content={
                "message": message
            }, status_code=500)
    except Exception as e:
        # 예외 처리, 예외가 발생했을 경우 클라이언트에게 오류 메시지를 JSON 형태로 반환
        return JSONResponse(content={
            "message": f"Error receiving image: {str(e)}"
        }, status_code=500)

# 메인 스크립트에서 서버 실행
if __name__ == "__main__":
    # SSL 컨텍스트 생성 (보안된 HTTPS 연결을 위해 사용)
    # ssl.PROTOCOL_TLS_SERVER를 사용해 서버에서 사용하는 TLS 프로토콜을 지정
    ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    # SSL 인증서와 키 파일을 로드하여 보안된 연결 설정
    ssl_context.load_cert_chain('server.cert', 'server.key')
    
    # Uvicorn을 사용해 FastAPI 애플리케이션 실행
    # 'main:app'에서 'main'은 파일 이름, 'app'은 FastAPI 인스턴스 이름을 의미
    # SSL을 위한 키 파일과 인증서 파일을 지정하여 HTTPS를 지원하도록 설정
    uvicorn.run(
        "main:app",
        host="0.0.0.0",  # 모든 네트워크 인터페이스에서 접근 가능하도록 설정
        port=20873,        # 서버가 수신 대기할 포트 번호 설정
        ssl_keyfile="server.key",  # SSL 키 파일 경로
        ssl_certfile="server.cert"  # SSL 인증서 파일 경로
    )