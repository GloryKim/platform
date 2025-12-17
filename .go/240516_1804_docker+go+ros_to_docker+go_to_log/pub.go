package main

import (
    "bytes"
    "encoding/json"
    "fmt"
    "log"
    "net/http"
    "os"
    "time"

    "github.com/aler9/goroslib"
    "github.com/aler9/goroslib/pkg/msgs/sensor_msgs"
    "github.com/aler9/goroslib/pkg/msgs/rosgraph_msgs"
)

func main() {
    // ROS 노드를 생성합니다.
    node, err := goroslib.NewNode(goroslib.NodeConf{
        Name:          "go_listener",
        MasterAddress: "localhost:11311",
    })
    if err != nil {
        log.Fatal(err)
    }
    defer node.Close()

    // ROS 구독자를 생성합니다.
    _, err = goroslib.NewSubscriber(goroslib.SubscriberConf{
        Node:  node,
        Topic: "/cam_image0",
        Callback: func(msg *sensor_msgs.Image) {
            logToFile("cam_image0.log", msg)
            sendToServer("http://localhost:8081/log", msg)
        },
    })
    if err != nil {
        log.Fatal(err)
    }

    _, err = goroslib.NewSubscriber(goroslib.SubscriberConf{
        Node:  node,
        Topic: "/cam_image1",
        Callback: func(msg *sensor_msgs.Image) {
            logToFile("cam_image1.log", msg)
            sendToServer("http://localhost:8081/log", msg)
        },
    })
    if err != nil {
        log.Fatal(err)
    }

    _, err = goroslib.NewSubscriber(goroslib.SubscriberConf{
        Node:  node,
        Topic: "/clock",
        Callback: func(msg *rosgraph_msgs.Clock) {
            logToFile("clock.log", msg)
            sendToServer("http://localhost:8081/log", msg)
        },
    })
    if err != nil {
        log.Fatal(err)
    }

    _, err = goroslib.NewSubscriber(goroslib.SubscriberConf{
        Node:  node,
        Topic: "/ir_img",
        Callback: func(msg *sensor_msgs.Image) {
            logToFile("ir_img.log", msg)
            sendToServer("http://localhost:8081/log", msg)
        },
    })
    if err != nil {
        log.Fatal(err)
    }

    // 웹 서버를 시작합니다.
    go func() {
        http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
            fmt.Fprintf(w, "ROS listener running. Check terminal for /cam_image0, /cam_image1, /clock, /ir_img topic data.")
        })

        log.Println("Starting server on :8080")
        if err := http.ListenAndServe(":8080", nil); err != nil {
            log.Fatalf("Failed to start server: %v", err)
        }
    }()

    // 프로그램을 계속 실행 상태로 유지합니다.
    select {}
}

func logToFile(filename string, msg interface{}) {
    f, err := os.OpenFile(filename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
    if err != nil {
        log.Println("Error opening file:", err)
        return
    }
    defer f.Close()

    _, err = f.WriteString(fmt.Sprintf("%v: %+v\n", time.Now(), msg))
    if err != nil {
        log.Println("Error writing to file:", err)
    }
}

func sendToServer(url string, data interface{}) {
    jsonData, err := json.Marshal(data)
    if err != nil {
        log.Printf("Error marshaling data: %v", err)
        return
    }

    resp, err := http.Post(url, "application/json", bytes.NewBuffer(jsonData))
    if err != nil {
        log.Printf("Error sending data: %v", err)
        return
    }
    defer resp.Body.Close()

    if resp.StatusCode != http.StatusOK {
        log.Printf("Received non-OK response: %v", resp.Status)
    }
}
