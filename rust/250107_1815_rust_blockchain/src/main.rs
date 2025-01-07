mod glory; //241029_2350_glory : glory.rs를 상속받기 위한 구문

use chrono::prelude::*;
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::sync::{Arc, Mutex};
use std::thread;
use std::io::stdin;

// 블록 구조체 정의
#[derive(Serialize, Deserialize, Debug, Clone)]
struct Block {
    index: u32,
    timestamp: i64,
    data: String,
    prev_hash: String,
    hash: String,
}

// 블록의 해시를 계산하는 함수
fn calculate_hash(index: u32, timestamp: i64, data: &str, prev_hash: &str) -> String {
    let input = format!("{}{}{}{}", index, timestamp, data, prev_hash);
    let mut hasher = Sha256::new();
    hasher.update(input.as_bytes());
    format!("{:x}", hasher.finalize())
}

// 새로운 블록을 생성하는 함수
fn create_block(index: u32, data: String, prev_hash: String) -> Block {
    let timestamp = Utc::now().timestamp();
    let hash = calculate_hash(index, timestamp, &data, &prev_hash);
    Block {
        index,
        timestamp,
        data,
        prev_hash,
        hash,
    }
}

// 제네시스 블록 생성
fn genesis_block() -> Block {
    create_block(0, "Genesis Block".to_string(), "0".to_string())
}

// 클라이언트로부터 데이터를 수신하는 함수
fn handle_client(stream: TcpStream, blockchain: Arc<Mutex<Vec<Block>>>) {
    let mut stream = stream;
    let mut buffer = [0; 512];

    match stream.read(&mut buffer) {
        Ok(_) => {
            let msg = String::from_utf8_lossy(&buffer[..]);
            if let Ok(received_chain) = serde_json::from_str::<Vec<Block>>(&msg) {
                let mut chain = blockchain.lock().unwrap();
                if received_chain.len() > chain.len() {
                    *chain = received_chain;
                    println!("Blockchain updated.");
                }
            }
        }
        Err(e) => println!("Error handling client: {}", e),
    }
}

// 서버를 시작하는 함수
fn start_server(blockchain: Arc<Mutex<Vec<Block>>>) {
    let listener = TcpListener::bind("0.0.0.0:7878").expect("Failed to bind port");
    println!("Server started on port 7878.");

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let chain = Arc::clone(&blockchain);
                thread::spawn(move || {
                    handle_client(stream, chain);
                });
            }
            Err(e) => println!("Connection failed: {}", e),
        }
    }
}

// 다른 노드에 블록체인을 전송하는 함수
fn broadcast_chain(blockchain: Arc<Mutex<Vec<Block>>>, peer: &str) {
    if let Ok(mut stream) = TcpStream::connect(peer) {
        let chain = blockchain.lock().unwrap();
        let msg = serde_json::to_string(&*chain).unwrap();
        stream.write_all(msg.as_bytes()).unwrap();
        println!("Blockchain sent to {}.", peer);
    } else {
        println!("Could not connect to {}.", peer);
    }
}

fn main() {
    let blockchain = Arc::new(Mutex::new(vec![genesis_block()]));

    // 서버 스레드 시작
    let chain_for_server = Arc::clone(&blockchain);
    thread::spawn(move || {
        start_server(chain_for_server);
    });

    loop {
        println!("1. Create new block");
        println!("2. View blockchain");
        println!("3. Send blockchain");
        println!("4. Web service control");
        println!("Choose an option:");

        let mut choice = String::new();
        stdin().read_line(&mut choice).unwrap();

        match choice.trim() {
            "1" => {
                println!("Enter data:");
                let mut data = String::new();
                stdin().read_line(&mut data).unwrap();

                let mut chain = blockchain.lock().unwrap();
                let prev_block = chain.last().unwrap();
                let new_block = create_block(
                    prev_block.index + 1,
                    data.trim().to_string(),
                    prev_block.hash.clone(),
                );
                chain.push(new_block);
                println!("New block added.");
            }
            "2" => {
                let chain = blockchain.lock().unwrap();
                for block in chain.iter() {
                    println!("{:#?}", block);
                }
            }
            "3" => {
                println!("Enter the address of the node to connect (e.g., 127.0.0.1:7878):");
                let mut peer = String::new();
                stdin().read_line(&mut peer).unwrap();
                broadcast_chain(Arc::clone(&blockchain), peer.trim());
            }
            "4" => {
                glory::control_web_service();//241029_2350_glory : glory.rs에 있는 run_web_service를 구동
            }
            _ => {
                println!("Invalid selection. Please try again.");
            }
        }
    }
}
