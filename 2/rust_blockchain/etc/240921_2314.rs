/*
Block 구조체: 블록의 기본 요소를 정의
Blockchain 구조체: 블록의 체인을 관리
SHA-256 해싱: 블록의 무결성을 위해 사용
네트워킹: TCP 소켓을 사용하여 노드 간 통신을 구현

블록 구조체: 블록의 속성들을 정의

index: 블록의 인덱스.
timestamp: 블록 생성 시간.
data: 블록에 저장된 데이터.
prev_hash: 이전 블록의 해시.
hash: 현재 블록의 해시.
해시 계산 함수: 블록의 속성을 이용해 SHA-256 해시를 계산

블록 생성 함수: 새로운 블록을 생성

제네시스 블록: 블록체인의 첫 번째 블록을 생성

네트워킹 부분:

start_server: TCP 서버를 시작하여 다른 노드로부터 블록체인을 수신
handle_client: 클라이언트로부터 받은 블록체인을 처리
broadcast_chain: 다른 노드에 현재 블록체인을 전송
메인 함수:

사용자 입력을 받아 새로운 블록을 생성하거나, 블록체인을 조회하거나, 다른 노드에 블록체인을 전송
서버는 별도의 스레드에서 실행
*/


// 필요한 외부 라이브러리 및 모듈을 불러옴
use chrono::prelude::*; // 시간 관련 기능을 사용하기 위해 chrono 라이브러리의 prelude 모듈을 불러옴
use serde::{Deserialize, Serialize}; // 구조체를 JSON으로 직렬화/역직렬화하기 위한 serde 라이브러리
use sha2::{Digest, Sha256}; // SHA-256 해시 함수 사용을 위한 라이브러리
use std::io::{Read, Write}; // TCP 네트워크 통신에서 데이터 읽고 쓰기 위한 표준 입출력 기능
use std::net::{TcpListener, TcpStream}; // TCP 통신을 위한 라이브러리, TcpListener로 서버를 생성하고 TcpStream으로 클라이언트와 통신
use std::sync::{Arc, Mutex}; // 다중 스레드 환경에서 데이터 공유를 위해 사용되는 Arc(Atomic Reference Counted), Mutex(상호 배제 잠금)
use std::thread; // 멀티스레드 프로그래밍을 위한 thread 모듈

// 블록 구조체 정의
// 블록체인의 핵심 단위인 블록을 정의함
#[derive(Serialize, Deserialize, Debug, Clone)] // 블록 구조체가 Serialize, Deserialize, Debug, Clone 트레이트를 자동으로 구현하도록 설정
struct Block {
    index: u32, // 블록의 고유 번호
    timestamp: i64, // 블록 생성 시간 (UNIX 타임스탬프 형식)
    data: String, // 블록에 저장되는 데이터
    prev_hash: String, // 이전 블록의 해시 값
    hash: String, // 현재 블록의 해시 값 (데이터 무결성을 보장)
}

// 블록의 해시를 계산하는 함수
// 인덱스, 타임스탬프, 데이터, 이전 블록의 해시를 입력으로 받아 SHA-256 해시 값을 계산
fn calculate_hash(index: u32, timestamp: i64, data: &str, prev_hash: &str) -> String {
    let input = format!("{}{}{}{}", index, timestamp, data, prev_hash); // 입력 값들을 문자열로 결합
    let mut hasher = Sha256::new(); // SHA-256 해시 계산기를 생성
    hasher.update(input.as_bytes()); // 결합된 문자열을 바이트 배열로 변환하여 해시 계산에 사용
    format!("{:x}", hasher.finalize()) // 최종 해시 값을 16진수 문자열로 반환
}

// 새로운 블록을 생성하는 함수
// 블록 번호, 데이터, 이전 해시 값을 받아 새로운 블록을 생성하고 반환
fn create_block(index: u32, data: String, prev_hash: String) -> Block {
    let timestamp = Utc::now().timestamp(); // 현재 시간을 타임스탬프(초 단위)로 가져옴
    let hash = calculate_hash(index, timestamp, &data, &prev_hash); // 입력 값을 사용하여 블록의 해시 계산
    Block {
        index, // 블록 번호
        timestamp, // 블록 생성 시간
        data, // 블록에 저장할 데이터
        prev_hash, // 이전 블록의 해시 값
        hash, // 현재 블록의 해시 값
    }
}

// 제네시스 블록 생성 함수
// 블록체인의 첫 번째 블록을 고정된 데이터로 생성
fn genesis_block() -> Block {
    create_block(0, "Genesis Block".to_string(), "0".to_string()) // 인덱스는 0, 데이터는 "Genesis Block", 이전 해시는 "0"으로 설정
}

// 클라이언트로부터 데이터를 수신하는 함수
// 클라이언트로부터 블록체인을 받아와 현재 블록체인과 비교하고, 더 긴 체인으로 교체
fn handle_client(stream: TcpStream, blockchain: Arc<Mutex<Vec<Block>>>) {
    let mut stream = stream; // 클라이언트와의 스트림을 mutable로 가져옴
    let mut buffer = [0; 512]; // 데이터를 읽어올 버퍼(512바이트 크기)를 선언

    // 클라이언트로부터 데이터를 읽음
    match stream.read(&mut buffer) {
        Ok(_) => {
            let msg = String::from_utf8_lossy(&buffer[..]); // 받은 데이터를 UTF-8 문자열로 변환
            // 받은 데이터를 블록체인(블록 벡터)으로 역직렬화 시도
            if let Ok(received_chain) = serde_json::from_str::<Vec<Block>>(&msg) {
                let mut chain = blockchain.lock().unwrap(); // 현재 블록체인을 잠금(Mutex로 보호)
                // 받은 체인의 길이가 현재 체인보다 길면 체인을 업데이트
                if received_chain.len() > chain.len() {
                    *chain = received_chain;
                    println!("블록체인이 업데이트되었습니다.");
                }
            }
        }
        Err(e) => println!("클라이언트 처리 중 오류 발생: {}", e), // 데이터 수신 중 오류 발생 시 메시지 출력
    }
}

// 서버를 시작하는 함수
// 특정 포트에서 클라이언트 연결을 대기하고, 새로운 연결이 들어올 때마다 스레드를 생성하여 처리
fn start_server(blockchain: Arc<Mutex<Vec<Block>>>) {
    let listener = TcpListener::bind("0.0.0.0:7878").expect("포트 바인딩 실패"); // 서버를 7878 포트에 바인딩
    println!("서버가 7878 포트에서 시작되었습니다.");

    // 들어오는 클라이언트 연결을 반복적으로 수신
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let chain = Arc::clone(&blockchain); // 각 클라이언트에서 블록체인을 공유하기 위해 Arc로 복제
                thread::spawn(move || { // 클라이언트 처리 작업을 별도의 스레드에서 실행
                    handle_client(stream, chain); // 클라이언트 요청 처리
                });
            }
            Err(e) => println!("연결 실패: {}", e), // 클라이언트 연결 실패 시 오류 메시지 출력
        }
    }
}

// 다른 노드에 블록체인을 전송하는 함수
// 피어의 주소를 받아 TCP 연결을 열고 블록체인을 JSON으로 직렬화하여 전송
fn broadcast_chain(blockchain: Arc<Mutex<Vec<Block>>>, peer: &str) {
    if let Ok(mut stream) = TcpStream::connect(peer) { // 피어와 TCP 연결을 시도
        let chain = blockchain.lock().unwrap(); // 현재 블록체인을 잠금
        let msg = serde_json::to_string(&*chain).unwrap(); // 블록체인을 JSON 문자열로 직렬화
        stream.write_all(msg.as_bytes()).unwrap(); // 직렬화된 데이터를 피어로 전송
        println!("{}로 블록체인을 전송했습니다.", peer); // 전송 완료 메시지 출력
    } else {
        println!("{}에 연결할 수 없습니다.", peer); // 피어 연결 실패 시 오류 메시지 출력
    }
}

// 메인 함수
// 서버를 시작하고, 블록을 생성하거나 블록체인을 전송하는 등 메인 로직을 처리
fn main() {
    let blockchain = Arc::new(Mutex::new(vec![genesis_block()])); // 제네시스 블록으로 블록체인 초기화

    // 서버 스레드 시작
    let chain_for_server = Arc::clone(&blockchain); // 서버에서 블록체인을 공유하기 위해 Arc로 복제
    thread::spawn(move || {
        start_server(chain_for_server); // 서버를 별도의 스레드에서 실행
    });

    // 메인 루프
    loop {
        // 사용자 인터페이스 출력
        println!("1. 새로운 블록 생성");
        println!("2. 블록체인 보기");
        println!("3. 블록체인 전송");
        println!("선택하세요: ");

        let mut choice = String::new(); // 사용자 입력을 받기 위한 변수
        std::io::stdin().read_line(&mut choice).unwrap(); // 콘솔에서 입력을 읽음

        // 입력된 값에 따라 작업을 처리
        match choice.trim() {
            // 새로운 블록 생성
            "1" => {
                println!("데이터를 입력하세요: ");
                let mut data = String::new();
                std::io::stdin().read_line(&mut data).unwrap(); // 사용자로부터 블록에 저장할 데이터를 입력받음

                let mut chain = blockchain.lock().unwrap(); // 블록체인을 잠금
                let prev_block = chain.last().unwrap(); // 마지막 블록을 가져옴
                let new_block = create_block(
                    prev_block.index + 1, // 새 블록의 인덱스는 이전 블록 인덱스보다 1 증가
                    data.trim().to_string(), // 입력받은 데이터를 사용
                    prev_block.hash.clone(), // 이전 블록의 해시 값을 사용
                );
                chain.push(new_block); // 새로 생성된 블록을 블록체인에 추가
                println!("새로운 블록이 추가되었습니다.");
            }
            // 블록체인 출력
            "2" => {
                let chain = blockchain.lock().unwrap(); // 블록체인을 잠금
                for block in chain.iter() { // 모든 블록을 순회하며 출력
                    println!("{:#?}", block); // 각 블록의 내용을 디버그 형식으로 출력
                }
            }
            // 블록체인 전송
            "3" => {
                println!("연결할 노드의 주소를 입력하세요 (예: 127.0.0.1:7878): ");
                let mut peer = String::new();
                std::io::stdin().read_line(&mut peer).unwrap(); // 피어의 주소를 입력받음
                broadcast_chain(Arc::clone(&blockchain), peer.trim()); // 입력받은 주소로 블록체인 전송
            }
            // 잘못된 선택 처리
            _ => {
                println!("잘못된 선택입니다.");
            }
        }
    }
}