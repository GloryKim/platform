package main

import "fmt"

func main() {
    var n int
    fmt.Scan(&n)

    for i := 1; i <= 9; i++ {
        fmt.Printf("%d * %d = %d\n", n, i, n*i)
    }
}