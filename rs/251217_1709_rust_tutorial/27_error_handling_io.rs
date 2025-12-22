// 27_error_handling_io.rs
// 파일 입출력과 ? 연산자를 이용한 에러 전파 예제입니다.

use std::fs::File;
use std::io::{self, Read, Write};

fn write_and_read() -> io::Result<()> {
    let filename = "example.txt";

    // 파일에 쓰기
    let mut file = File::create(filename)?;
    file.write_all(b"Hello, file!")?;

    // 다시 열어서 읽기
    let mut file = File::open(filename)?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;

    println!("읽은 내용: {}", contents);
    Ok(())
}

fn main() {
    if let Err(e) = write_and_read() {
        println!("에러 발생: {}", e);
    }
}


