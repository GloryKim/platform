package main

import (
	"fmt"
)

// ===== defer, panic, recover 예제 =====

// 1. defer: 함수 종료 시점에 실행되는 코드
func DeferExample() {
	fmt.Println("[defer 예제] 함수 시작")
	defer fmt.Println("[defer 예제] 함수 종료 직전 실행 (defer)")
	fmt.Println("[defer 예제] 함수 본문 실행 중...")
}

// 2. panic: 런타임 에러 발생시키기
func PanicExample() {
	fmt.Println("[panic 예제] 패닉 발생 전")
	panic("문제가 발생했습니다!")
	// 아래 코드는 실행되지 않음
	// fmt.Println("[panic 예제] 패닉 발생 후")
}

// 3. recover: 패닉 복구
func RecoverExample() {
	fmt.Println("[recover 예제] 시작")
	defer func() {
		if r := recover(); r != nil {
			fmt.Printf("[recover 예제] 패닉 복구: %v\n", r)
		}
	}()
	fmt.Println("[recover 예제] 패닉 발생 전")
	panic("recover로 복구되는 패닉!")
	// 아래 코드는 실행되지 않음
	// fmt.Println("[recover 예제] 패닉 발생 후")
}

// 4. defer와 리소스 해제 패턴
func ResourceDeferExample() {
	fmt.Println("[리소스 해제 패턴] 파일 열기 (가정)")
	defer fmt.Println("[리소스 해제 패턴] 파일 닫기 (defer)")
	fmt.Println("[리소스 해제 패턴] 파일 읽기/쓰기 작업")
}

// ===== 예제 실행 함수 =====
func RunDeferPanicExamples() {
	fmt.Println("=== Go defer/panic/recover 예제 ===")
	DeferExample()
	fmt.Println()
	// panic 예제는 주석 처리 (실행 시 프로그램 종료)
	// PanicExample()
	// fmt.Println()
	RecoverExample()
	fmt.Println()
	ResourceDeferExample()
}

// ===== main 함수에서 호출 예시 =====
// func main() {
// 	RunDeferPanicExamples()
// } 