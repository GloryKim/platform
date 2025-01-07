// sub.go
/*
sub.go 코드 설명:
IMU 데이터 구조체 정의: ImuData 구조체를 정의하여 수신할 IMU 데이터 형식을 지정합니다.
HTTP 핸들러 함수 정의: imuHandler 함수는 /glory 경로로 들어오는 HTTP POST 요청을 처리합니다. 요청 본문을 ImuData 구조체로 디코딩하고, 수신된 데이터를 로그로 기록합니다.
HTTP 서버 시작: http.HandleFunc를 사용하여 /glory 경로에 대한 요청을 imuHandler 함수로 처리하도록 설정한 후, 로컬호스트의 8081 포트에서 HTTP 서버를 시작합니다.
*/
package main

import (
    "encoding/json" // JSON 인코딩 및 디코딩을 위한 패키지
    "fmt"           // 표준 입출력 포맷팅 패키지
    "log"           // 로깅을 위한 패키지
    "net/http"      // HTTP 통신을 위한 패키지
)

// ImuData 구조체는 수신할 IMU 데이터의 형식을 정의합니다.
type ImuData struct {
    Orientation struct { // IMU의 오리엔테이션 데이터를 포함합니다.
        X float64 `json:"x"` // x축 데이터
        Y float64 `json:"y"` // y축 데이터
        Z float64 `json:"z"` // z축 데이터
        W float64 `json:"w"` // w축 데이터
    } `json:"orientation"`
    // 추가적인 IMU 데이터를 여기에 추가할 수 있습니다.
}

// imuHandler 함수는 /glory 경로로 들어오는 HTTP POST 요청을 처리합니다.
func imuHandler(w http.ResponseWriter, r *http.Request) {
    // 요청 메서드가 POST가 아니면 오류를 반환합니다.
    if r.Method != http.MethodPost {
        http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
        return
    }

    // 요청 본문을 디코딩하여 ImuData 구조체에 저장합니다.
    var imuData ImuData
    decoder := json.NewDecoder(r.Body)
    if err := decoder.Decode(&imuData); err != nil {
        http.Error(w, "Bad request", http.StatusBadRequest) // 디코딩 오류를 반환합니다.
        return
    }

    // 수신한 IMU 데이터를 로그로 기록합니다.
    log.Printf("Received IMU data: %+v\n", imuData)
    // 응답으로 IMU 데이터가 수신되었음을 알립니다.
    fmt.Fprintf(w, "IMU data received")
}

func main() {
    // /glory 경로로 들어오는 요청을 imuHandler로 처리하도록 설정합니다.
    http.HandleFunc("/glory", imuHandler)

    // HTTP 서버를 시작합니다.
    log.Println("Starting server on :8081") // 서버 시작을 로그로 기록합니다.
    if err := http.ListenAndServe(":8081", nil); err != nil {
        log.Fatalf("Failed to start server: %v", err) // 서버 시작 오류를 로그로 기록하고 종료합니다.
    }
}
