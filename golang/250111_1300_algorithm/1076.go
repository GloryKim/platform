package main

import (
	"fmt"
)

func main() {
	// 색상과 값 매핑
	colorMap := map[string]int{
		"black":  0,
		"brown":  1,
		"red":    2,
		"orange": 3,
		"yellow": 4,
		"green":  5,
		"blue":   6,
		"violet": 7,
		"grey":   8,
		"white":  9,
	}

	// 입력 받기
	var color1, color2, color3 string
	fmt.Scan(&color1)
	fmt.Scan(&color2)
	fmt.Scan(&color3)

	// 저항값 계산
	value := (colorMap[color1]*10 + colorMap[color2]) * intPow(10, colorMap[color3])

	// 결과 출력
	fmt.Println(value)
}

// intPow는 정수형 거듭제곱을 계산하는 함수
func intPow(base, exp int) int {
	result := 1
	for exp > 0 {
		if exp%2 == 1 {
			result *= base
		}
		base *= base
		exp /= 2
	}
	return result
}