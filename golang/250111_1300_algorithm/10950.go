package main

import "fmt"

func main() {
    var t int
    fmt.Scan(&t)

    for i := 0; i < t; i++ {
        var a, b int
        fmt.Scan(&a, &b)
        fmt.Println(a + b)
    }
}