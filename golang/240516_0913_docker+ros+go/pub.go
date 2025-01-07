// pub.go
/*
pub.go 코드 설명:
ROS 노드 생성: goroslib.NewNode를 사용하여 ROS 노드를 생성합니다. 이 노드는 ROS 마스터와 통신하고, 데이터 토픽을 구독하는 역할을 합니다.
ROS 구독자 생성: goroslib.NewSubscriber를 사용하여 /mavros/imu/data 토픽을 구독하고, IMU 데이터를 수신할 때마다 콜백 함수를 호출합니다.
HTTP 서버 시작: 별도의 고루틴을 사용하여 HTTP 서버를 시작합니다. 이 서버는 기본적으로 로컬호스트의 8080 포트에서 실행됩니다.
IMU 데이터 전송: 수신된 IMU 데이터를 sendIMUData 함수를 통해 다른 HTTP 서버로 전송합니다.
*/

package main

import (
    "bytes"          // HTTP 요청 본문을 구성하는 데 필요한 패키지
    "encoding/json"  // 데이터를 JSON으로 인코딩 및 디코딩하는 패키지
    "fmt"            // 표준 입출력 포맷팅 패키지
    "log"            // 로깅을 위한 패키지
    "net/http"       // HTTP 통신을 위한 패키지

    "github.com/aler9/goroslib"                  // ROS 기능을 제공하는 패키지
    "github.com/aler9/goroslib/pkg/msgs/sensor_msgs" // ROS 메시지 형식을 정의하는 패키지
)

// sendIMUData 함수는 IMU 데이터를 HTTP POST 요청으로 전송합니다.
func sendIMUData(data sensor_msgs.Imu) {
    // 데이터를 JSON 형식으로 마샬링(직렬화)합니다.
    jsonData, err := json.Marshal(data)
    if err != nil {
        log.Printf("Error marshaling data: %v", err) // 마샬링 오류를 로그로 기록합니다.
        return
    }

    // HTTP POST 요청을 통해 데이터를 전송합니다.
    resp, err := http.Post("http://sub-container:8081/glory", "application/json", bytes.NewBuffer(jsonData))
    if err != nil {
        log.Printf("Error sending data: %v", err) // 전송 오류를 로그로 기록합니다.
        return
    }
    defer resp.Body.Close() // 응답 본문을 닫습니다.

    // 응답 상태 코드를 확인합니다.
    if resp.StatusCode != http.StatusOK {
        log.Printf("Received non-OK response: %v", resp.Status) // 비정상 응답 상태를 로그로 기록합니다.
    }
}

func main() {
    // ROS 노드를 생성합니다.
    node, err := goroslib.NewNode(goroslib.NodeConf{
        Name:          "go_listener",          // 노드 이름
        MasterAddress: "localhost:11311",      // ROS 마스터 주소
    })
    if err != nil {
        log.Fatal(err) // 노드 생성 오류를 로그로 기록하고 종료합니다.
    }
    defer node.Close() // 노드를 종료 시 닫습니다.

    // ROS 구독자를 생성합니다.
    sub, err := goroslib.NewSubscriber(goroslib.SubscriberConf{
        Node:  node,                  // 생성된 노드
        Topic: "/mavros/imu/data",    // 구독할 토픽 이름
        Callback: func(msg *sensor_msgs.Imu) { // 메시지를 수신했을 때 호출되는 콜백 함수
            fmt.Printf("Received IMU data: %+v\n", msg) // 수신된 IMU 데이터를 출력합니다.
            sendIMUData(*msg) // IMU 데이터를 HTTP로 전송합니다.
        },
    })
    if err != nil {
        log.Fatal(err) // 구독자 생성 오류를 로그로 기록하고 종료합니다.
    }
    defer sub.Close() // 구독자를 종료 시 닫습니다.

    // 웹 서버를 시작합니다.
    go func() {
        http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
            fmt.Fprintf(w, "ROS listener running. Check terminal for /mavros/imu/data topic data.")
            // 웹 서버의 루트 경로로 요청이 들어오면 메시지를 출력합니다.
        })

        log.Println("Starting server on :8080") // 서버 시작을 로그로 기록합니다.
        if err := http.ListenAndServe(":8080", nil); err != nil {
            log.Fatalf("Failed to start server: %v", err) // 서버 시작 오류를 로그로 기록하고 종료합니다.
        }
    }()

    // 프로그램을 계속 실행 상태로 유지합니다.
    select {}
}


/*
프로그램 간의 연결 및 원리 설명
ROS 노드와 구독자 설정 (pub.go):

pub.go 프로그램은 ROS 노드를 생성하고 /mavros/imu/data 토픽을 구독합니다. 이 토픽은 IMU 데이터를 포함합니다.
구독자가 IMU 데이터를 수신하면, 콜백 함수가 호출되어 데이터를 sendIMUData 함수로 전달합니다.
IMU 데이터 전송 (pub.go):

sendIMUData 함수는 수신된 IMU 데이터를 JSON으로 변환하고, HTTP POST 요청을 통해 sub.go 프로그램이 실행하는 서버(http://localhost:8081/glory)로 전송합니다.
HTTP 서버 설정 및 데이터 수신 (sub.go):

sub.go 프로그램은 /glory 경로로 들어오는 HTTP POST 요청을 처리하기 위해 HTTP 서버를 설정합니다.
imuHandler 함수는 수신된 요청의 본문을 ImuData 구조체로 디코딩하고, 로그로 기록합니다. 요청이 성공적으로 처리되었음을 클라이언트에게 응답으로 알립니다.
전체 동작 원리
pub.go 프로그램은 ROS를 통해 IMU 데이터를 수신하고, 이를 HTTP POST 요청으로 sub.go 프로그램으로 전송합니다.
sub.go 프로그램은 이 HTTP POST 요청을 받아 데이터를 디코딩하고 로그로 기록합니다.
이를 통해 두 프로그램은 ROS와 HTTP를 통해 IMU 데이터를 수집하고 처리하는 시스템을 구성합니다.
*/