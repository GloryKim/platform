package main

import (
	"fmt" // 표준 입출력을 위한 패키지
)

func subtraction(a int, b int) int {
	return a - b
}

func main() {

	var a, b int
	fmt.Scanln(&a, &b)
	
	sum := subtraction(a, b) // subtraction 함수 호출
	fmt.Println(sum)
}