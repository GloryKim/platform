package main

import "fmt"

func main() {
    var n int
    fmt.Scan(&n)

    for i := 1; i <= n; i++ {
        // 공백 출력
        for j := 1; j <= n-i; j++ {
            fmt.Print(" ")
        }
        // 별 출력
        for k := 1; k <= i; k++ {
            fmt.Print("*")
        }
        fmt.Println()
    }
}