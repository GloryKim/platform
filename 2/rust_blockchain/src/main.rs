use chrono::prelude::*;
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::sync::{Arc, Mutex};
use std::thread;

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
                    println!("블록체인이 업데이트되었습니다.");
                }
            }
        }
        Err(e) => println!("클라이언트 처리 중 오류 발생: {}", e),
    }
}

// 서버를 시작하는 함수
fn start_server(blockchain: Arc<Mutex<Vec<Block>>>) {
    let listener = TcpListener::bind("0.0.0.0:7878").expect("포트 바인딩 실패");
    println!("서버가 7878 포트에서 시작되었습니다.");

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let chain = Arc::clone(&blockchain);
                thread::spawn(move || {
                    handle_client(stream, chain);
                });
            }
            Err(e) => println!("연결 실패: {}", e),
        }
    }
}

// 다른 노드에 블록체인을 전송하는 함수
fn broadcast_chain(blockchain: Arc<Mutex<Vec<Block>>>, peer: &str) {
    if let Ok(mut stream) = TcpStream::connect(peer) {
        let chain = blockchain.lock().unwrap();
        let msg = serde_json::to_string(&*chain).unwrap();
        stream.write_all(msg.as_bytes()).unwrap();
        println!("{}로 블록체인을 전송했습니다.", peer);
    } else {
        println!("{}에 연결할 수 없습니다.", peer);
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
        println!("1. 새로운 블록 생성");
        println!("2. 블록체인 보기");
        println!("3. 블록체인 전송");
        println!("선택하세요: ");

        let mut choice = String::new();
        std::io::stdin().read_line(&mut choice).unwrap();

        match choice.trim() {
            "1" => {
                println!("데이터를 입력하세요: ");
                let mut data = String::new();
                std::io::stdin().read_line(&mut data).unwrap();

                let mut chain = blockchain.lock().unwrap();
                let prev_block = chain.last().unwrap();
                let new_block = create_block(
                    prev_block.index + 1,
                    data.trim().to_string(),
                    prev_block.hash.clone(),
                );
                chain.push(new_block);
                println!("새로운 블록이 추가되었습니다.");
            }
            "2" => {
                let chain = blockchain.lock().unwrap();
                for block in chain.iter() {
                    println!("{:#?}", block);
                }
            }
            "3" => {
                println!("연결할 노드의 주소를 입력하세요 (예: 127.0.0.1:7878): ");
                let mut peer = String::new();
                std::io::stdin().read_line(&mut peer).unwrap();
                broadcast_chain(Arc::clone(&blockchain), peer.trim());
            }
            _ => {
                println!("잘못된 선택입니다.");
            }
        }
    }
}
