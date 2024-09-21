package main

import (
    "crypto/tls"
    "fmt"
    "net/http"
    "sync"
    "time"
)

func sendRequest(wg *sync.WaitGroup, url string) {
    defer wg.Done()

    // TLS 인증서 검증을 비활성화
    tr := &http.Transport{
        TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
    }
    client := &http.Client{Transport: tr}

    _, err := client.Get(url)
    if err != nil {
        fmt.Println("Error sending request:", err)
        return
    }
    fmt.Println("Request sent successfully")
}

func main() {
    url := "https://localhost:10873/api/test" // 대상 서버 URL
    numRequests := 1000              // 요청을 보낼 횟수

    var wg sync.WaitGroup
    wg.Add(numRequests)

    for i := 0; i < numRequests; i++ {
        go sendRequest(&wg, url)
        time.Sleep(10 * time.Millisecond) // 요청 사이의 간격 설정 (필요시 조정 가능)
    }

    wg.Wait()
    fmt.Println("All requests completed")
}
