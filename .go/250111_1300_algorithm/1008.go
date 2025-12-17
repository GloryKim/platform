package main

import (
	"fmt"
)

func main() {
	// 두 정수 A와 B 입력 받기
	var A, B float64
	fmt.Scan(&A, &B)

	// A / B 결과 출력 (소수점 이하 32자리까지)
	fmt.Printf("%.32f\n", A/B)
}