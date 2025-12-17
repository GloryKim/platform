package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	// 입력 처리
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')

	// 문자열 앞뒤 공백 제거
	input = strings.TrimSpace(input)

	// 공백을 기준으로 문자열 분리
	words := strings.Fields(input)

	// 단어 개수 출력
	fmt.Println(len(words))
}
