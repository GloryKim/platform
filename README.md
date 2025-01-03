# Copyright (C) 2024 GloryKim (glory@keti.re.kr)

## 1. Node.JS(u.javascript)
    - 240921_2230 : NodeJS기반 메인서버, WebRTC 서버 이식 + 해당 서버에 각종 로그를 남길 예정이며, 추후에는 메인 서버를 별도로 구축할 계획에 있음
    - 240921_0139 : go측에서 45만개의 xyz 배열을 1초에 한번씩 보내는 걸 소화 (app.use(bodyParser.json({ limit: '100mb' }));) 기능으로 해결
    - 240928_2344 : nestjs에게 이미지 전달 하는 프로젝트 구현완료 axios 활용
    - 241005_1313 : run_in_executor 기능이 반영된 fastapi 서버에 이미지를 보내기 위한 교신 기능 추가
    - 241007_1727 : 다른망으로 텍스트 데이터 송수신 하는 기능 구현
    - 241010_0911 : fastapi 서버에 포인트클라우드 데이터 수신 후 시각화 표현 완료 -> 해상도 이슈가 살짝 있을 수는 있는데 최소 1초 주기로 해야할 것으로 사료 됨 (가끔 버벅이기도 함, 크롬 뷰어 시스템 내용 검토 필요) + 클라우드 포인트 수를 저감을 해도 랜더링을 처음부터 끝까지 다시 거니깐 이러한 이슈가 있는 것 같음. 크롬 화면에서 데이터를 잘 받는다고 뜨지만, 시각화가 지연되는 이유는 다양한 요소들이 영향을 미칠 수 있음. 특히, 실시간 데이터 전송에서는 데이터 전송 속도, Three.js에서의 렌더링 성능, 그리고 브라우저의 렌더링 최적화 문제 등이 있을 수 있음.
    - 241022_1111 : nestJS에서 비동기로 오는 신호를 대기하다가 출력하는 구문 구현 완료
    - 241022_1138 : express 5.0 전환


## 2. Blockchain+Platform(u.rust)
    - 240921_2248 : 작업 증명, 트랜잭션, 디지털 서명 등 기능이 미포함
    - 241029_2354 : 신규기능 추가, 웹서버 작동 코드 구현 완료 (4번 기능)
    - 241030_0000 : glory.rs에 옵션 기능 추가, 단 중복 1->2->2->1 입력 시 thread '<unnamed>' panicked at src/glory.rs:46:58: Failed to bind to port 8080: Os { code: 48, kind: AddrInUse, message: "Address already in use" } note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace 오류 발생
    - 241030_0019 : glory.rs에 웹서버 온오프 기능 구현 완료 (몽키테스트 완료함)
    - 241101_1004 : glory.rs에 터미널 꾸미는 기능 추가 colored = "2.0"

## 3. SendRequest(u.golang)
    - 240921_2303 : node 서버에 무차별로 연락을 보내는 코드
    - 240921_0139 : node로 45만개의 xyz 배열을 1초에 한번씩 보내는 기능 구현 반영 (post)
    - 241102_1216 : 터미널 모드 기능 추가, 색상정보 추가, 기존기능과 이원화로 두고 현재는 단순한 print만 나오도록 세팅을 했는데, 추후에 기능 부여 예정

## 4. Nest.JS+Next.JS(u.typescript)
    - 240928_2343 : main.ts, app.controller.ts, image.service.ts, image.controller.ts, app.module.ts 4개 수정
    - 240928_2344 : nodejs에게 이미지 전달 받는 프로젝트 구현완료 axios 활용
    - 241022_1111 : nodejs에게 비동기로 일정확률로 신호를 보내는 기능 구현
    - 241022_1454 : type 정하는 구문 추구 완료
    - 250103_1532 : typescript프로젝트 (Nestjs + Nextjs) 병합

## 5. FastAPI(u.python)
    - 241005_1313 : fastapi 서버 구축 후 nodejs서버와 이미지 데이터 주고받을때 이미지 처리가 완료되고나서 응답을 위한 run_in_executor 교신 기능 추가(실행 방법은 readme.md 필수)
    - 241010_0911 : fastapi 서버에 포인트클라우드 데이터 랜덤 생성 후 nodejs 서버(https://localhost:10873/pointscloud)에 보내는 구문 추가 (0.5초 주기로 비동기로 쏘기)

## 6. iOS(u.swift)
    - 250103_1504 : swift 폴더 생성 및 폴더명 정리
    - 250103_1542 : swift 파일 내용 백업


---

## Next Step
1. Node-forever log save 기능을 통해 log 정리
2. Node-기존 js 서버 일부 요소 반영
3. Node-실시간 통신: WebSocket, SSE, SignalR, socketIO
4. Node-고성능 데이터 스트리밍: gRPC, Kafka, MQTT
5. Node-메시징 시스템: AMQP, Redis Pub/Sub
6. Node-여러개 요청 동시 처리
7. Node-json 정보에 ""가 들어가면 예외처리
8. Go-Rust와 터미널 통신 기능 구현
9. Rust-Go와 터미널 통신 기능 구현