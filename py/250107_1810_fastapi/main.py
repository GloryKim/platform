import uvicorn
from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse
from PIL import Image
import io
import ssl
import asyncio
import os


#241009_1535_pointcloud 생성 및 전송하기 위해서 미리 세팅할 것들
import socket
import json
import numpy as np
import time
import httpx  # FastAPI에서 HTTP 요청을 위해 httpx 라이브러리 사용

# FastAPI 인스턴스를 생성
# FastAPI는 웹 API를 빠르고 쉽게 개발할 수 있게 해주는 Python 웹 프레임워크
app = FastAPI()



#241009_1708_glory : https://localhost:20873/pointscloud
#23만개의 랜덤한 포인트 클라우드 생성하는 함수
#241009_1805_glory : 당연한 말인데 포인트 클라우드 수가 적으면 훨씬더 빠르게 보낼 수 있는 것 같다. 
def generate_random_point_cloud(num_points=23000): #241009_1754_glory : 230000에서 1000으로 변경 계산을 쉽게하기 위해서 
#def generate_random_point_cloud(num_points=230000): #241009_1754_glory : 1000에서 230000으로 변경 계산을 쉽게하기 위해서 
    points = np.random.uniform(low=-500.0, high=500.0, size=(num_points, 3))
    #points = np.random.uniform(low=-1000.0, high=1000.0, size=(num_points, 3)) #241009_1743_glory : 원래 코드인데 가볍게 하기 위해서 수정함
    return points

# 포인트 클라우드를 Node.js 1번 서버로 전송하는 함수 (HTTP POST 요청)
async def send_point_cloud_data():
    while True:
        # 포인트 클라우드 생성 구문
        point_cloud = generate_random_point_cloud()
        
        # 포인트 클라우드를 JSON으로 변환
        data = {
            "type": "random_point_cloud",
            "point_count": len(point_cloud),
            "points": point_cloud.tolist()
        }

        try:
            # Node.js 서버로 POST 요청 보내기 (localhost:10873)
            async with httpx.AsyncClient(verify=False) as client:  # verify 대신 ssl 검증 비활성화 -> 추후 내용 검증 필요
                response = await client.post('https://localhost:10873/pointscloud', json=data)
                print(f"Sent point cloud: {response.status_code}, Response: {response.text}")
        except Exception as e:
            print(f"Error sending point cloud data: {str(e)}")

        # 1초 대기 후 다시 전송 = 1
        # 241009_1742_glory : 당연한 이야기인데, asyncio.sleep(0.1) 주기와 points = np.random.uniform(low=-100.0, high=100.0, size=(num_points, 3))를 숫자를 조정하면 더 빨리 보낼 수 있음
        await asyncio.sleep(0.1)


# 클라이언트에서 포인트 클라우드 요청을 처리하는 엔드포인트 (GET 요청 허용)
@app.get("/pointscloud")
async def get_pointscloud():
    try:
        # 포인트 클라우드 데이터를 Node.js 서버로 전송하는 비동기 작업 시작
        asyncio.create_task(send_point_cloud_data())
        return JSONResponse(content={"message": "Point Cloud Server started and sending data"}, status_code=200)
    
    except Exception as e:
        return JSONResponse(content={"message": f"Error starting server: {str(e)}"}, status_code=500)



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