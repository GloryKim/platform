//250711_1011_glory

/*
MediaMTX란?
- RTSP/RTMP 미디어 서버입니다. 실시간 스트리밍 프로토콜 지원하고, 경량화된 미디어 서버 솔루션입니다.

MediaMTX를 미리 설치하는 이유는
- RTSP 스트림을 받아서 여러 클라이언트에게 배포하는 미디어 서버 역할을 하기 위함입니다.
- FFmpeg로 변환한 스트림을 중앙 집중식으로 관리하고 다중 접속을 지원하기 위한 필수 인프라입니다.
*/

/*

설치방법

wget https://github.com/bluenviron/mediamtx/releases/download/v1.13.0/mediamtx_v1.13.0_linux_amd64.tar.gz

tar -xzf mediamtx_v1.13.0_linux_amd64.tar.gz

cd mediamtx

./mediamtx

*/

/*
graph LR
    A[IP 카메라] --> B[FFmpeg]
    B --> C[MediaMTX 서버]
    C --> D[웹 브라우저]
    C --> E[VLC 플레이어]
    C --> F[모바일 앱]
*/

const { spawn } = require('child_process');

// 250711_1011_glory : m사에서 만든 rtsp 신호 출처 스트림입니다.
const RTSP_INPUT = 'rtsp://admin:mobiltechtest!@192.168.1.100:554/H.265/media.smp'; //H.265부분을 H.264로 바꾸면 H264정보 나옴

// 250711_1012_glory : 목적지 (내부 RTSP 서버 또는 다른 서버 IP로 변경 가능)
const RTSP_OUTPUT = 'rtsp://localhost:8554/streamA';

const ffmpeg = spawn('ffmpeg', [
  '-rtsp_transport', 'tcp', //RTSP 전송 프로토콜을 TCP로 설정, UDP 대신 TCP 사용으로 안정성 향상
  '-i', RTSP_INPUT, //입력 소스 지정, RTSP 스트림 입력
 
  '-c:v', 'copy', // ← 재인코딩 없이 그대로 복사
  //'-c:v', 'libx264', // ← H.264로 변환
  //'-c:v', 'libx265',
  
  /*
  -vcodec을 쓸지 말지 선택에서 나는 생략하는 걸 선택
  //'-vcodec', 'libx265', // 비디오 코덱을 H.265로 설정
  //'-preset', 'ultrafast', // 인코딩 속도 최우선, 인코딩시에만 유효함으로 주석 조치
  //'-tune', 'zerolatency', //지연시간 최소화, 인코딩시에만 유효함으로 주석 조치
  */
  '-f', 'rtsp', //출력 형식을 RTSP로 설정
  RTSP_OUTPUT
]);

/*
h264 활용 경우 
    1. 실시간 스트리밍이 우선순위
    2. CPU 리소스가 제한적
    3. 호환성이 중요한 경우
    4. 빠른 처리가 필요한 경우
    5. 압축효율성 낮음
    6. cpu 사용량 낮음
    7. 호환성 범용적
    8. 파일크기 큼
    9. 인코딩속도 빠름

h265 활용경우
    1. 대역폭 절약이 중요한 경우
    2. 저장 공간이 제한적
    3. 고화질 유지가 중요한 경우
    4. H.265 지원 환경
    5. 압축효율성 높음 (약 50% 절약)
    6. cpu 사용량 높음
    7. 호환성 제한적
    8. 파일크기 작음
    9. 인코딩속도 느림
*/

ffmpeg.stderr.on('data', (data) => { // ffmpeg.stderr: FFmpeg 프로세스의 표준 오류(stderr) 스트림
  //.on('data', ...): stderr에서 데이터가 출력될 때마다 실행되는 이벤트 리스너
  console.log(`[FFmpeg] ${data}`); // console.log(\[FFmpeg] ${data}\): 받은 오류 메시지를 콘솔에 출력
});

ffmpeg.on('close', (code) => {
  console.log(`[FFmpeg 종료] 코드: ${code}`);
});

/*
250711_1016_glory :

다른 pc에서 

ffplay -rtsp_transport tcp rtsp://192.168.0.10:8554/streamA

이렇게 보아야한다.

ffplay rtsp://localhost:8554/streamA

이렇게 할 경우 UDP로 볼수도 있다.
*/