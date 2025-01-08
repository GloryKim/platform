/*
Go 서버 실행방법
	go.mod 파일 생성:
		go mod init websocket-server
		go get github.com/gorilla/websocket
	Go 서버 코드를 실행:
		go run main.go
*/

package main

import (
	"log"
	"math/rand"
	"net/http"
	"sync"
	"time"

	"github.com/gorilla/websocket"
)

// WebSocket 업그레이더
var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

// ID 리스트
var ids = []string{"A", "B", "C", "D", "E"}

func main() {
	http.HandleFunc("/ws", handleConnections)

	// 서버 시작
	log.Println("WebSocket 서버 실행 중: localhost:11111")
	err := http.ListenAndServe(":11111", nil)
	if err != nil {
		log.Fatalf("서버 실행 실패: %v", err)
	}
}

func handleConnections(w http.ResponseWriter, r *http.Request) {
	// WebSocket 연결 업그레이드
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Printf("연결 업그레이드 실패: %v", err)
		return
	}
	defer conn.Close()

	// WaitGroup 사용하여 비동기 작업 관리
	var wg sync.WaitGroup
	var mu sync.Mutex // WebSocket 쓰기를 보호할 Mutex

	// 각 ID에 대해 비동기 작업 생성
	for _, id := range ids {
		wg.Add(1)
		go func(id string) {
			defer wg.Done()
			sendRandomData(id, conn, &mu)
		}(id)
	}

	// WaitGroup이 완료되기를 대기
	wg.Wait()
}

func sendRandomData(id string, conn *websocket.Conn, mu *sync.Mutex) {
	for {
		// 0.5초에서 1초 사이의 랜덤 대기 시간
		sleepTime := time.Duration(rand.Intn(500)+500) * time.Millisecond
		time.Sleep(sleepTime)

		// 랜덤 x, y, z 생성
		data := map[string]interface{}{
			"id": id,
			"x":  rand.Float64() * 10,
			"y":  rand.Float64() * 10,
			"z":  rand.Float64() * 10,
		}

		// Mutex를 사용하여 WebSocket 쓰기 보호
		mu.Lock()
		err := conn.WriteJSON(data)
		mu.Unlock()

		if err != nil {
			log.Printf("ID %s 데이터 전송 실패: %v", id, err)
			break
		}
		log.Printf("ID %s 전송된 데이터: %v", id, data)
	}
}