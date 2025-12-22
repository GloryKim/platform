// 22_mpsc_channel.rs
// mpsc 채널을 이용한 스레드 간 메시지 전송 예제입니다.

use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        let messages = vec!["하나", "둘", "셋"];
        for msg in messages {
            println!("보냄: {}", msg);
            tx.send(msg.to_string()).unwrap();
            thread::sleep(Duration::from_millis(100));
        }
    });

    // 수신 측: 이터레이터처럼 사용 가능
    for received in rx {
        println!("받음: {}", received);
    }

    println!("채널 예제 종료");
}


