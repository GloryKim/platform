# rust+Blockchain

- 240921_2248 : 작업 증명, 트랜잭션, 디지털 서명 등 기능이 미포함

- 240921_2250_glory : 실행 명령어 -> **mac@macui-MacBookPro rust_blockchain % cargo run**

- 241029_2354 : 신규기능 추가, 웹서버 작동 코드 구현 완료 (4번 기능)

- 241030_0000 : glory.rs에 옵션 기능 추가, 단 중복 1->2->2->1 입력 시 thread '<unnamed>' panicked at src/glory.rs:46:58: Failed to bind to port 8080: Os { code: 48, kind: AddrInUse, message: "Address already in use" } note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace 오류 발생

- 241030_0019 : glory.rs에 웹서버 온오프 기능 구현 완료 (몽키테스트 완료함)

- 241101_1004_glory : rust 프로젝트에 [dependencies] colored = "2.0" 추가

- 250107_1814_glory : 폴더 병합