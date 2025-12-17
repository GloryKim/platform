// 21_threads.rs
// 스레드 생성과 join 예제입니다.

use std::thread;
use std::time::Duration;

fn main() {
    let handle1 = thread::spawn(|| {
        for i in 1..=5 {
            println!("스레드 1: {}", i);
            thread::sleep(Duration::from_millis(100));
        }
    });

    let handle2 = thread::spawn(|| {
        for i in 1..=5 {
            println!("스레드 2: {}", i);
            thread::sleep(Duration::from_millis(100));
        }
    });

    // join을 호출하여 스레드가 끝날 때까지 기다립니다.
    handle1.join().unwrap();
    handle2.join().unwrap();

    println!("메인 스레드 종료");
}


