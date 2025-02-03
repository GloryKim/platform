package main

import "fmt"

func compareNumbers(a int, b int) string {
    if a > b {
        return ">"
    } else if a < b {
        return "<"
    } else {
        return "=="
    }
}

func main() {
    var a, b int
    fmt.Scan(&a, &b)
    
    result := compareNumbers(a, b)
    fmt.Println(result)
}