package main

import (
    "encoding/json"
    "fmt"
    "io/ioutil"
    "log"
    "net/http"
    "os"
    "time"
)

func main() {
    http.HandleFunc("/log", logHandler)

    log.Println("Starting server on :8081")
    if err := http.ListenAndServe(":8081", nil); err != nil {
        log.Fatalf("Failed to start server: %v", err)
    }
}

func logHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method != http.MethodPost {
        http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
        return
    }

    body, err := ioutil.ReadAll(r.Body)
    if err != nil {
        http.Error(w, "Error reading request body", http.StatusInternalServerError)
        return
    }
    defer r.Body.Close()

    var data interface{}
    if err := json.Unmarshal(body, &data); err != nil {
        http.Error(w, "Error unmarshaling JSON", http.StatusBadRequest)
        return
    }

    logToFile("received_data.log", data)

    fmt.Fprintf(w, "Data received and logged successfully")
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
