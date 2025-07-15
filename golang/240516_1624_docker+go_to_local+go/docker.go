package main

import (
    "bytes"
    "fmt"
    "net/http"
    "os"
)

func main() {
    for {
        // 예를 들어, 입력 텍스트를 사용자가 콘솔에서 입력한다고 가정
        var input string
        fmt.Print("Enter text: ")
        fmt.Scanln(&input)

        // POST 요청을 통해 localhost 서버로 텍스트 전송
        resp, err := http.Post("http://host.docker.internal:8080/receive", "text/plain", bytes.NewBufferString(input))
        if err != nil {
            fmt.Println("Error:", err)
            os.Exit(1)
        }
        defer resp.Body.Close()

        // 응답 확인
        if resp.StatusCode == http.StatusOK {
            fmt.Println("Text sent successfully!")
        } else {
            fmt.Println("Failed to send text.")
        }
    }
}
