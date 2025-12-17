package main

import (
	"fmt"
)

// ===== Go 1.18+ 제네릭(Generics) 기본 예제 =====

// 1. 제네릭 함수: 타입 파라미터 사용
func PrintSlice[T any](s []T) {
	fmt.Println("[제네릭 함수] 슬라이스 내용:")
	for i, v := range s {
		fmt.Printf("  %d: %v\n", i, v)
	}
}

// 2. 제네릭 타입: Stack 예제
type Stack[T any] struct {
	items []T
}

func (s *Stack[T]) Push(item T) {
	s.items = append(s.items, item)
}

func (s *Stack[T]) Pop() (T, bool) {
	if len(s.items) == 0 {
		var zero T
		return zero, false
	}
	item := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return item, true
}

// 3. 타입 제약(Constraints) 예제
// comparable: ==, != 연산이 가능한 타입만 허용
func IndexOf[T comparable](s []T, target T) int {
	for i, v := range s {
		if v == target {
			return i
		}
	}
	return -1
}

// 4. 여러 타입 제약 (interface)
type Adder[T any] interface {
	Add(a, b T) T
}

type IntAdder struct{}
func (IntAdder) Add(a, b int) int { return a + b }

type FloatAdder struct{}
func (FloatAdder) Add(a, b float64) float64 { return a + b }

func Sum[T any, A Adder[T]](a A, x, y T) T {
	return a.Add(x, y)
}

// ===== 제네릭 예제 실행 =====
func RunGenericsExamples() {
	fmt.Println("=== Go 제네릭(Generics) 예제 ===")

	// 1. 제네릭 함수
	PrintSlice([]int{1, 2, 3, 4})
	PrintSlice([]string{"go", "lang", "generic"})

	// 2. 제네릭 타입 (Stack)
	intStack := Stack[int]{}
	intStack.Push(10)
	intStack.Push(20)
	val, ok := intStack.Pop()
	fmt.Printf("[Stack] Pop: %d, ok=%t\n", val, ok)

	strStack := Stack[string]{}
	strStack.Push("hello")
	strStack.Push("world")
	val2, ok2 := strStack.Pop()
	fmt.Printf("[Stack] Pop: %s, ok=%t\n", val2, ok2)

	// 3. 타입 제약 (comparable)
	idx := IndexOf([]string{"a", "b", "c"}, "b")
	fmt.Printf("[IndexOf] 'b'의 인덱스: %d\n", idx)

	// 4. 여러 타입 제약 (Adder 인터페이스)
	intAdder := IntAdder{}
	floatAdder := FloatAdder{}
	fmt.Printf("[Sum] int: %d\n", Sum(intAdder, 3, 5))
	fmt.Printf("[Sum] float64: %.2f\n", Sum(floatAdder, 1.5, 2.7))
}

// ===== main 함수에서 호출 예시 =====
// func main() {
// 	RunGenericsExamples()
// } 