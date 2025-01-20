package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	// 입력을 읽기 위한 스캐너 생성
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	T, _ := strconv.Atoi(scanner.Text()) // 테스트 케이스 개수

	// DP 배열 초기화
	maxN := 40
	zeroCount := make([]int, maxN+1)
	oneCount := make([]int, maxN+1)

	// 초기값 설정
	zeroCount[0] = 1
	oneCount[0] = 0
	zeroCount[1] = 0
	oneCount[1] = 1

	// DP로 zeroCount와 oneCount 계산
	for i := 2; i <= maxN; i++ {
		zeroCount[i] = zeroCount[i-1] + zeroCount[i-2]
		oneCount[i] = oneCount[i-1] + oneCount[i-2]
	}

	// 각 테스트 케이스 처리
	results := make([]string, T)
	for i := 0; i < T; i++ {
		scanner.Scan()
		N, _ := strconv.Atoi(scanner.Text())
		results[i] = fmt.Sprintf("%d %d", zeroCount[N], oneCount[N])
	}

	// 결과 출력
	for _, result := range results {
		fmt.Println(result)
	}
}