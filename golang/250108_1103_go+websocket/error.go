/*
Go 서버 실행방법
	go.mod 파일 생성:
		go mod init websocket-server
		go get github.com/gorilla/websocket
	Go 서버 코드를 실행:
		go run main.go
*/

/*
:0.3844508198833808 z:0.8320290291567587]
2025/01/08 11:32:01 ID C 전송된 데이터: map[id:C x:0.6035690920458912 y:0.8522170883202221 z:5.432794584197854]
panic: concurrent write to websocket connection

goroutine 22 [running]:
github.com/gorilla/websocket.(*messageWriter).flushFrame(0x14000325710, 0x1, {0x0?, 0x1?, 0x14000167d88?})
        /Users/node/go/pkg/mod/github.com/gorilla/websocket@v1.5.3/conn.go:617 +0x460
github.com/gorilla/websocket.(*messageWriter).Close(0x0?)
        /Users/node/go/pkg/mod/github.com/gorilla/websocket@v1.5.3/conn.go:731 +0x48
github.com/gorilla/websocket.(*Conn).beginMessage(0x140000a0000, 0x14000196900, 0x1)
        /Users/node/go/pkg/mod/github.com/gorilla/websocket@v1.5.3/conn.go:480 +0x3c
github.com/gorilla/websocket.(*Conn).NextWriter(0x140000a0000, 0x1)
        /Users/node/go/pkg/mod/github.com/gorilla/websocket@v1.5.3/conn.go:520 +0x40
github.com/gorilla/websocket.(*Conn).WriteJSON(0x100ef80e0?, {0x100ef80e0, 0x140001968d0})
        /Users/node/go/pkg/mod/github.com/gorilla/websocket@v1.5.3/json.go:24 +0x2c
main.sendRandomData({0x100ec05b8, 0x1}, 0x140000a0000)
        /Users/node/_github/platform/golang/250108_1103_go+websocket/main.go:83 +0x294
main.handleConnections.func1({0x100ec05b8?, 0x0?})
        /Users/node/_github/platform/golang/250108_1103_go+websocket/main.go:60 +0x50
created by main.handleConnections in goroutine 35
        /Users/node/_github/platform/golang/250108_1103_go+websocket/main.go:58 +0x120
exit status 2
node@fasts 250108_1103_go+websocket % 

*/

/*

이 오류는 여러 고루틴에서 동일한 WebSocket 연결에 동시에 쓰기를 시도하기 때문에 발생함

gorilla/websocket은 WebSocket 연결에서의 동시 쓰기 작업을 허용하지 않으며, 이를 관리하려면 쓰기 작업에 대한 동기화가 필요함

원인 분석 panic: concurrent write to websocket connection

sendRandomData 함수가 여러 고루틴에서 WebSocket 연결(conn)에 쓰기를 시도.

gorilla/websocket은 하나의 WebSocket 연결에 대해 동시 쓰기를 허용하지 않음.

문제 위치 = err := conn.WriteJSON(data)

고루틴에서 conn.WriteJSON이 동시에 호출되면서 충돌 발생.

해결 방법 - WebSocket 연결에 쓰기를 할 때 뮤텍스를 사용하여 쓰기 작업을 직렬화해야 함

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

	// 각 ID에 대해 비동기 작업 생성
	for _, id := range ids {
		wg.Add(1)
		go func(id string) {
			defer wg.Done()
			sendRandomData(id, conn)
		}(id)
	}

	// WaitGroup이 완료되기를 대기
	wg.Wait()
}

func sendRandomData(id string, conn *websocket.Conn) {
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

		// 데이터 전송
		err := conn.WriteJSON(data)
		if err != nil {
			log.Printf("ID %s 데이터 전송 실패: %v", id, err)
			break
		}
		log.Printf("ID %s 전송된 데이터: %v", id, data)
	}
}