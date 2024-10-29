use std::net::TcpListener;
use std::io::{Read, Write};
use std::thread;

// 웹 서비스를 실행하는 함수
pub fn run_web_service() {
    let listener = TcpListener::bind("0.0.0.0:8080").expect("Failed to bind to port 8080");
    println!("Web service started on port 8080.");

    for stream in listener.incoming() {
        match stream {
            Ok(mut stream) => {
                thread::spawn(move || {
                    let mut buffer = [0; 512];
                    stream.read(&mut buffer).unwrap();

                    let response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from the web service!";
                    stream.write_all(response.as_bytes()).unwrap();
                    println!("Responded to client request.");
                });
            }
            Err(e) => println!("Failed to accept client connection: {}", e),
        }
    }
}
