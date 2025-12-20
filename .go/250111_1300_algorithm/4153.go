//https://www.acmicpc.net/problem/4153

package main

import (
	"fmt"
)

func main() {
	var a, b, c int

	for {
		fmt.Scanln(&a, &b, &c)
		if a == 0 && b == 0 && c == 0 {
			break
		}

		// 가장 긴 변을 찾아서 피타고라스 정리 검증
		a2, b2, c2 := a*a, b*b, c*c
		if a2+b2 == c2 || a2+c2 == b2 || b2+c2 == a2 {
			fmt.Println("right")
		} else {
			fmt.Println("wrong")
		}
	}
}

/*
//https://www.acmicpc.net/problem/4153

package main

import (
	"fmt" // 표준 입출력을 위한 패키지
)

func pythagoras1(a int, b int) int {
	return a*a+b*b
}

func pythagoras2(a int, c int) int {
	return a*a+c*c
}

func pythagoras3(b int, c int) int {
	return c*c+b*b
}

func main() {

	//입력 a, b, c 선언
	var a = 1
	var b = 0
	var c = 0
	//결과값을 순차적으로 출력할 배열
	var results []string
	//결과값 배열 출력

	//0, 0, 0 입력 시 종료
	for a != 0 || b != 0 || c != 0 {
		fmt.Scanln(&a, &b, &c)
		if a == 0 && b == 0 && c == 0 {
			for _, result := range results {
				fmt.Println(result)
			}
			break;
		} else {
			glory := pythagoras1(a, b) // pythagoras 함수 호출
			glory2 := pythagoras2(a, c) // pythagoras 함수 호출
			glory3 := pythagoras3(b, c) // pythagoras 함수 호출
			if glory == c*c || glory2 == b*b || glory3 == a*a {
				// right wrong 결과값 출력될 순서 결과값 배열에 저장
				results = append(results, "right")
			} else {
				results = append(results, "wrong")
			}
		}
	}
}
*/