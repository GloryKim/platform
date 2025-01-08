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
	"fmt"
	"log"
	"net/http"

	"github.com/gorilla/websocket"
)

// 외부 서버에서 받은 메시지를 클라이언트(브라우저)로 중계하기 위한 구조
var upgrader = websocket.Upgrader{
	// WebSocket CORS 우회
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

var (
	clients = make(map[*websocket.Conn]bool) // 연결된 모든 브라우저 클라이언트
)

// main: 외부 서버(192.168.0.14:3000) 연결 + 내부 ws 서버(:9999) 구동
func main() {
	// 1) 외부(192.168.0.14:3000)에 Dial
	externalConn, _, err := websocket.DefaultDialer.Dial("ws://192.168.0.14:3000", nil)
	if err != nil {
		log.Fatal("dial error:", err)
	}
	defer externalConn.Close()
	log.Println("Connected to external WS:", "ws://192.168.0.14:3000")

	// 외부 WS 수신 → 내부 클라이언트에게 브로드캐스트
	go func() {
		for {
			// 외부 서버에서 메시지 읽기
			_, msg, readErr := externalConn.ReadMessage()
			if readErr != nil {
				log.Println("read error from external:", readErr)
				break
			}
			fmt.Printf("Received from external: %s\n", msg)

			// 연결된 모든 클라이언트에게 전송
			for conn := range clients {
				writeErr := conn.WriteMessage(websocket.TextMessage, msg)
				if writeErr != nil {
					log.Println("broadcast error:", writeErr)
					conn.Close()
					delete(clients, conn)
				}
			}
		}
	}()

	// 2) 내부 WebSocket 서버 (localhost:9999/ws) 구동
	http.HandleFunc("/ws", handleLocalWS)

	log.Println("Local WS server started on ws://localhost:9999/ws")
	if err := http.ListenAndServe(":9999", nil); err != nil {
		log.Fatal("ListenAndServe error:", err)
	}
}

// handleLocalWS: 브라우저 클라이언트(Next.js) 연결 담당
func handleLocalWS(w http.ResponseWriter, r *http.Request) {
	conn, err := upgrader.Upgrade(w, r, nil) // HTTP → WebSocket 업그레이드
	if err != nil {
		log.Println("upgrade error:", err)
		return
	}
	clients[conn] = true
	log.Println("New local client connected:", conn.RemoteAddr())
}
