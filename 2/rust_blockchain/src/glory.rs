use std::net::TcpListener;
use std::io::{Read, Write};
use std::thread;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Arc;
use lazy_static::lazy_static;
use std::io::stdin;

lazy_static! { //241029_2358_glory : lazy_static = "1.4" 기능을 추가하려면 glory/2/rust_blockchain/Cargo.toml 에 추가해야함
    static ref RUNNING: Arc<AtomicBool> = Arc::new(AtomicBool::new(false));
}

pub fn control_web_service() {
    loop {
        println!("1. Start Web Server");
        println!("2. Stop Web Server");
        println!("Choose an option:");

        let mut choice = String::new();
        stdin().read_line(&mut choice).unwrap();

        match choice.trim() {
            "1" => {
                start_web_service();
            }
            "2" => {
                stop_web_service();
            }
            _ => {
                println!("Invalid selection. Please try again.");
            }
        }
    }
}

fn start_web_service() {
    if RUNNING.load(Ordering::SeqCst) {
        println!("Web service is already running.");
        return;
    }

    let running = Arc::clone(&RUNNING);
    running.store(true, Ordering::SeqCst);

    thread::spawn(move || {
        let listener = TcpListener::bind("0.0.0.0:8080").expect("Failed to bind to port 8080");
        println!("Web service started on port 8080.");

        for stream in listener.incoming() {
            if !running.load(Ordering::SeqCst) {
                println!("Web service stopped.");
                break;
            }

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
    });
}

fn stop_web_service() {
    if RUNNING.load(Ordering::SeqCst) {
        RUNNING.store(false, Ordering::SeqCst);
        println!("Stopping the web service...");
    } else {
        println!("Web service is not running.");
    }
}
