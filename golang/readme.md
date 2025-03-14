# golang

- 240514_2017 : rosbag play -l all.bag 파일을 실행시킬 때 발생하는 토픽들을 웹 통신으로 송수신 하는 코드 (대용량 라이다도 가능)

- 240516_0913 : docker compose로 실행하고 닫고 하는 방법

- 240516_1624 : docker 컨테이너 내 열린 go webserver에서 터미널로 텍스트 입력할때 local에 있는 go 웹서버 cmd 창에도 출력하기

- 240516_1634 : docker 프로젝트명 수정 및 양방향 기능도 구현

- 240516_1807 : 도커 내부끼리 go로 웹서버 열어서 한쪽에서는 topic들을 publish해주고 반대면에서는 subscribe해서 log로 저장하는 작업 수행

- 240921_2257 : 메인서버에 계속해서 트레픽을 부과할 client 서버 실행명령어 -> **mac@macui-MacBookPro 3 % go run main.go**

- 240921_2303 : node 서버에 무차별로 연락을 보내는 코드

- 240921_0139 : node로 45만개의 xyz 배열을 1초에 한번씩 보내는 기능 구현 반영 (post)

- 241102_1216 : 터미널 모드 기능 추가, 색상정보 추가, 기존기능과 이원화로 두고 현재는 단순한 print만 나오도록 세팅을 했는데, 추후에 기능 부여 예정

- 250107_1803 : 폴더 병합

- 250108_1150 : ws로 신호 5개를 비동기로 쏠때에 WebSocket 연결에 쓰기를 할 때 뮤텍스를 사용하여 쓰기 작업을 직렬화해야 함, 고루틴에서 동일한 WebSocket 연결에 동시에 쓰기를 시도하기 때문에 발생하는 오류를 막기 위함으로, gorilla/websocket은 WebSocket 연결에서의 동시 쓰기 작업을 허용하지 않으며, 이를 관리하려면 쓰기 작업에 대한 동기화가 필요함

- 250108_1512 : 다른 pc에서 들어오는 ws 신호를 받아서 print되게 하는 코드

- 250108_1634 : 다른 PC에서 들어오는 ws 신호를 받아서 bridge하게 지원하는 코드

- 250111_1302 : algorithm 프로젝트 생성 및 추후 계속 알고리즘 내용 갱신 예정, 업데이트 시, 250111_1303_create(update) : 1001 이런식으로 갱신 예정

- 250116_1019 : 1005 문제 해결 (250117_1149 : commit 규칙 재확인)

# 관심용어

- DoS (Denial of Service): 서비스 거부 공격으로, 네트워크나 서버에 과도한 트래픽을 보내 시스템이 정상적으로 작동하지 않도록 하는 공격.

- DDoS (Distributed Denial of Service): 분산 서비스 거부 공격으로, 여러 시스템에서 동시에 트래픽을 발생시켜 네트워크나 서버에 과중한 부하를 일으키는 공격.

- Traffic Congestion: 네트워크 트래픽이 많아져 네트워크 대역폭이 포화 상태에 이르러 데이터 전송 속도가 느려지거나 응답이 지연되는 상태.

- Overload: 서버나 네트워크 장치가 처리할 수 있는 용량을 초과하는 트래픽이 발생하여 성능 저하 또는 서비스 중단을 유발하는 상태.

- Throttling: 시스템이 처리할 수 있는 트래픽 양을 제한하여 과도한 부하를 방지하는 기법.

- Bottleneck: 시스템의 특정 부분이 성능 저하를 유발하는 지점으로, 네트워크 대역폭, CPU, 메모리, I/O 장치 등이 과부하되어 전체 성능이 저하되는 상황.

- Rate Limiting: 클라이언트나 특정 요청 유형에 대해 요청 속도를 제한하여 서버의 과부하를 방지하는 방법.

- Latency: 요청이 이루어진 시점부터 응답이 돌아오기까지의 지연 시간으로, 트래픽 과중 부하 시 지연 시간이 급격히 증가할 수 있음.

- Load Balancing: 여러 서버에 트래픽을 분산하여 부하를 고르게 분산시킴으로써 성능 저하를 방지하는 기법.

- Throughput: 단위 시간당 처리되는 데이터 양으로, 트래픽 부하가 과도할 때 시스템의 처리량이 감소할 수 있음.

- Queueing: 시스템에서 트래픽이나 요청이 순서대로 처리되기 위해 대기하는 상황으로, 부하가 심할 때 큐잉 시간이 길어질 수 있음.

