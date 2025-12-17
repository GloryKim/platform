package main

import (
    "bytes"
    "fmt"
    "io/ioutil"
    "net/http"
)

func sendText(text string) {
    resp, err := http.Post("http://localhost:8081/receive", "text/plain", bytes.NewBufferString(text))
    if err != nil {
        fmt.Println("Error:", err)
        return
    }
    defer resp.Body.Close()
    
    if resp.StatusCode == http.StatusOK {
        fmt.Println("Text sent successfully!")
    } else {
        fmt.Println("Failed to send text.")
    }
}

func receiveHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method == "POST" {
        body, err := ioutil.ReadAll(r.Body)
        if err != nil {
            http.Error(w, "Unable to read body", http.StatusBadRequest)
            return
        }
        defer r.Body.Close()

        fmt.Println("Received text:", string(body))
        w.WriteHeader(http.StatusOK)
    } else {
        http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
    }
}

func main() {
    go func() {
        http.HandleFunc("/receive", receiveHandler)
        fmt.Println("Local server is listening on port 8080...")
        http.ListenAndServe(":8080", nil)
    }()

    for {
        var input string
        fmt.Print("Enter text to send to container: ")
        fmt.Scanln(&input)
        sendText(input)
    }
}
