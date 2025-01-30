package main

import (
    "fmt"
)

func main() {
    var word string
    var position int
    
    // 단어 입력 받기
    fmt.Scan(&word)
    
    // 위치 입력 받기
    fmt.Scan(&position)
    
    // position-1을 사용하는 이유는 Go의 문자열 인덱스가 0부터 시작하기 때문입니다
    // 문제에서는 1부터 시작하는 위치를 요구합니다
    fmt.Printf("%c", word[position-1])
}