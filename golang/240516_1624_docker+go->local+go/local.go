package main

import (
    "fmt"
    "io/ioutil"
    "net/http"
)

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
    http.HandleFunc("/receive", receiveHandler)
    fmt.Println("Server is listening on port 8080...")
    http.ListenAndServe(":8080", nil)
}
