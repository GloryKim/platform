use std::net::TcpListener;
use std::io::{Read, Write};
use std::thread;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Arc;
// [신규] mpsc 채널 추가: 서버 스레드의 종료 상태를 메인 스레드에 전달하기 위한 통신 채널
use std::sync::mpsc;
use lazy_static::lazy_static;
use std::io::stdin;
// [신규] Duration 추가: 스레드 sleep 및 타임아웃을 위한 시간 관리 기능
use std::time::Duration;

// [변경없음] RUNNING 전역 변수 정의
lazy_static! {
    static ref RUNNING: Arc<AtomicBool> = Arc::new(AtomicBool::new(false));
}

pub fn control_web_service() {
    // [신규] 서버 스레드와 메인 스레드 간의 통신을 위한 채널 생성
    let (tx, rx) = mpsc::channel();
    // [신규] 서버 스레드 핸들을 저장하기 위한 변수 추가
    let mut server_thread = None;

    loop {
        println!("1. Start Web Server");
        println!("2. Stop Web Server");
        // [신규] 프로그램 종료 옵션 추가
        println!("3. Exit");
        println!("Choose an option:");

        let mut choice = String::new();
        stdin().read_line(&mut choice).unwrap();

        match choice.trim() {
            "1" => {
                // [변경] 서버 시작 로직을 더 안전하게 수정
                if !RUNNING.load(Ordering::SeqCst) {
                    // [신규] 서버 스레드 시작 시 핸들을 저장
                    server_thread = Some(start_web_service(tx.clone()));
                } else {
                    println!("Web service is already running.");
                }
            }
            // [변경] 2번 또는 다른 키 입력 시에도 서버 종료 처리
            "2" | _ => {
                stop_web_service();
                // [신규] 기존 서버 스레드가 있다면 정리
                if let Some(thread) = server_thread.take() {
                    // [신규] 서버 스레드의 종료 신호를 최대 2초간 대기
                    let _ = rx.recv_timeout(Duration::from_secs(2));
                    // [신규] 스레드가 완전히 종료될 때까지 대기
                    thread.join().unwrap();
                    println!("Web server stopped and port released.");
                } else {
                    println!("Web service is not running.");
                }
            }
            // [신규] 프로그램 종료 옵션 처리
            "3" => {
                stop_web_service();
                if let Some(thread) = server_thread.take() {
                    let _ = rx.recv_timeout(Duration::from_secs(2));
                    thread.join().unwrap();
                }
                println!("Exiting program...");
                break;
            }
        }
    }
}

// [변경] 서버 시작 함수가 이제 스레드 핸들을 반환하도록 수정
fn start_web_service(tx: mpsc::Sender<()>) -> thread::JoinHandle<()> {
    RUNNING.store(true, Ordering::SeqCst);
    let running = Arc::clone(&RUNNING);

    // [변경] 스레드 생성 부분을 수정하여 더 안전하게 처리
    thread::spawn(move || {
        // [변경] TcpListener 생성을 실패할 수 있는 상황 처리 추가
        let listener = match TcpListener::bind("0.0.0.0:8080") {
            Ok(l) => {
                println!("Web service started on port 8080.");
                l
            }
            Err(e) => {
                println!("Failed to bind to port 8080: {}", e);
                running.store(false, Ordering::SeqCst);
                // [신규] 바인딩 실패 시 종료 신호 전송
                let _ = tx.send(());
                return;
            }
        };

        // [신규] 리스너를 논블로킹 모드로 설정하여 즉시 종료 가능하게 함
        listener.set_nonblocking(true).expect("Failed to set non-blocking");

        // [변경] 서버 루프를 수정하여 더 반응성 있게 처리
        while running.load(Ordering::SeqCst) {
            match listener.accept() {
                Ok((mut stream, _)) => {
                    thread::spawn(move || {
                        let mut buffer = [0; 512];
                        // [변경] 클라이언트 요청 처리를 더 안전하게 수정
                        if let Ok(_) = stream.read(&mut buffer) {
                            let response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from the web service!";
                            let _ = stream.write_all(response.as_bytes());
                            println!("Responded to client request.");
                        }
                    });
                }
                // [신규] 논블로킹 모드에서의 대기 처리
                Err(ref e) if e.kind() == std::io::ErrorKind::WouldBlock => {
                    // 연결이 없을 때는 잠시 대기
                    thread::sleep(Duration::from_millis(100));
                    continue;
                }
                Err(e) => {
                    println!("Failed to accept client connection: {}", e);
                }
            }
        }

        // [신규] 서버 종료 시 메인 스레드에 알림
        let _ = tx.send(());
        println!("Server thread terminated.");
    })
}

// [변경] 서버 종료 함수는 단순화됨
fn stop_web_service() {
    if RUNNING.load(Ordering::SeqCst) {
        RUNNING.store(false, Ordering::SeqCst);
        println!("Stopping the web service...");
    }
}