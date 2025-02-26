package main

import (
	"fmt"
)

func main() {
	var a, b int

	// 반복적으로 입력을 받는다
	for {
		// 두 정수 A와 B를 입력받는다
		fmt.Scan(&a, &b)

		// A와 B가 모두 0이면 종료
		if a == 0 && b == 0 {
			break
		}

		// A와 B의 합을 출력한다
		fmt.Println(a + b)
	}
}
