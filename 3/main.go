package main

import (
    "crypto/tls"
    "fmt"
    "net/http"
    "sync"
    "time"
    "math/rand" //240922_0118_glory : rand한 값들을 보내기 위해서 해당 내용 작성
    "encoding/json" //240922_0120_glory : json 취급
    "bytes"

)



//240922_0119_glory : 해당 작업은 (x,y,z) 값을 보내기 위해서 xyz 구조를 설정함
type XYZ struct {
    X int `json:"x"`
    Y int `json:"y"`
    Z int `json:"z"`
}







func sendRequest(wg *sync.WaitGroup, url string, data []XYZ) { //240922_0121_glory : data []XYZ를 활용하기 위하여 해당 구문 추가
    defer wg.Done()

    // TLS 인증서 검증을 비활성화
    tr := &http.Transport{
        TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
    }
    client := &http.Client{Transport: tr}





    //240922_0122_glory : json 마샬링
    jsonData, err := json.Marshal(data)
    if err != nil {
        fmt.Println("Error marshalling JSON:", err)
        return
    }

    req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsonData))//240922_0140_glory : Post 방식으로 변경
    if err != nil {
        fmt.Println("Error creating request:", err)
        return
    }
    req.Header.Set("Content-Type", "application/json")

    _, err = client.Do(req)
    if err != nil {
        fmt.Println("Error sending request:", err)
        return
    }
    fmt.Println("Request sent successfully")
    //끝




    /*
    _, err := client.Get(url)
    if err != nil {
        fmt.Println("Error sending request:", err)
        return
    }
    fmt.Println("Request sent successfully")
    */
}









func generateRandomXYZ(count int) []XYZ {
    data := make([]XYZ, count)
    for i := 0; i < count; i++ {
        data[i] = XYZ{
            X: rand.Intn(256), // 0 ~ 255 범위의 값
            Y: rand.Intn(256),
            Z: rand.Intn(256),
        }
    }
    return data
}









func main() {
    url := "https://localhost:10873/api/test" // 대상 서버 URL
    numRequests := 100                        // 요청을 보낼 횟수 1이면 1번만
    numData := 450000                         // 전송할 데이터 개수 (45만개)

    var wg sync.WaitGroup
    wg.Add(numRequests)

    for i := 0; i < numRequests; i++ {
        data := generateRandomXYZ(numData)
        go sendRequest(&wg, url, data) //240922_0126_glory : data도 같이 던져주기
        time.Sleep(1 * time.Millisecond) // 요청 사이의 간격 설정 (필요시 조정 가능)
    }

    wg.Wait()
    fmt.Println("All requests completed")
}
