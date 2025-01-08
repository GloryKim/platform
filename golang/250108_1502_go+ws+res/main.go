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

	"github.com/gorilla/websocket"
)

func main() {
	// 접속할 WebSocket 주소 보내는쪽 ip를 써야함
	uri := "ws://192.168.0.1:3000"

	// Dialer를 통해 서버에 연결
	c, _, err := websocket.DefaultDialer.Dial(uri, nil)
	if err != nil {
		log.Fatal("dial error:", err)
	}
	defer c.Close()

	// 메시지 수신 무한 루프
	for {
		_, message, err := c.ReadMessage()
		if err != nil {
			log.Println("read error:", err)
			break
		}
		fmt.Printf("Received: %s\n", message)
	}
}
