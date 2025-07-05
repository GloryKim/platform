package main

import (
	"fmt"
	//"math/cmplx"
	"reflect"
)

// Go 언어의 변수 선언과 타입에 대한 완전한 가이드
func main() {
	fmt.Println("🔤 Go 언어 변수와 타입 완전 가이드")
	fmt.Println("==================================")

	// 1. 기본 타입들
	basicTypes()
	
	// 2. 변수 선언 방법들
	variableDeclarations()
	
	// 3. 타입 변환
	typeConversions()
	
	// 4. 상수
	constants()
	
	// 5. 타입 추론
	typeInference()
	
	// 6. 복합 타입
	complexTypes()
	
	// 7. 타입 검사
	typeChecking()
}

// basicTypes 함수는 Go의 모든 기본 타입을 보여줍니다.
func basicTypes() {
	fmt.Println("\n📝 1. 기본 타입들")
	fmt.Println("----------------")

	// 정수 타입들
	var int8Val int8 = 127                    // 8비트 정수 (-128 ~ 127)
	var int16Val int16 = 32767                // 16비트 정수 (-32768 ~ 32767)
	var int32Val int32 = 2147483647           // 32비트 정수
	var int64Val int64 = 9223372036854775807  // 64비트 정수
	var intVal int = 42                       // 플랫폼에 따라 32비트 또는 64비트

	// 부호 없는 정수 타입들
	var uint8Val uint8 = 255                  // 8비트 부호 없는 정수 (0 ~ 255)
	var uint16Val uint16 = 65535              // 16비트 부호 없는 정수
	var uint32Val uint32 = 4294967295         // 32비트 부호 없는 정수
	var uint64Val uint64 = 18446744073709551615 // 64비트 부호 없는 정수
	var uintVal uint = 42                     // 플랫폼에 따라 32비트 또는 64비트

	// 부동소수점 타입들
	var float32Val float32 = 3.14             // 32비트 부동소수점
	var float64Val float64 = 3.14159265359    // 64비트 부동소수점

	// 복소수 타입들
	var complex64Val complex64 = 3 + 4i       // 64비트 복소수
	var complex128Val complex128 = 3.14 + 2.71i // 128비트 복소수

	// 불린 타입
	var boolVal bool = true                   // true 또는 false

	// 문자열 타입
	var stringVal string = "Hello, Go!"       // UTF-8 인코딩된 문자열

	// 바이트 타입 (uint8의 별칭)
	var byteVal byte = 65                     // 0 ~ 255

	// 룬 타입 (int32의 별칭, 유니코드 코드포인트)
	var runeVal rune = '한'                    // 유니코드 문자

	fmt.Printf("정수 타입들:\n")
	fmt.Printf("  int8: %d, int16: %d, int32: %d, int64: %d, int: %d\n", 
		int8Val, int16Val, int32Val, int64Val, intVal)
	
	fmt.Printf("부호 없는 정수 타입들:\n")
	fmt.Printf("  uint8: %d, uint16: %d, uint32: %d, uint64: %d, uint: %d\n", 
		uint8Val, uint16Val, uint32Val, uint64Val, uintVal)
	
	fmt.Printf("부동소수점 타입들:\n")
	fmt.Printf("  float32: %f, float64: %.10f\n", float32Val, float64Val)
	
	fmt.Printf("복소수 타입들:\n")
	fmt.Printf("  complex64: %v, complex128: %v\n", complex64Val, complex128Val)
	
	fmt.Printf("기타 타입들:\n")
	fmt.Printf("  bool: %t, string: %s, byte: %d, rune: %c\n", 
		boolVal, stringVal, byteVal, runeVal)
}

// variableDeclarations 함수는 다양한 변수 선언 방법을 보여줍니다.
func variableDeclarations() {
	fmt.Println("\n📝 2. 변수 선언 방법들")
	fmt.Println("----------------------")

	// 방법 1: var 키워드로 명시적 선언
	var name string = "Go"
	var age int = 25
	var isStudent bool = true

	// 방법 2: 타입 추론 (:= 연산자 사용)
	language := "Go"
	version := 1.21
	isAwesome := true

	// 방법 3: 여러 변수 동시 선언
	var (
		firstName = "John"
		lastName  = "Doe"
		email     = "john@example.com"
	)

	// 방법 4: 여러 변수 동시 선언 (타입 추론)
	city, country := "Seoul", "Korea"
	year, month, day := 2024, 1, 15

	// 방법 5: 제로값으로 초기화
	var defaultInt int        // 0
	var defaultFloat float64  // 0.0
	var defaultString string  // ""
	var defaultBool bool      // false
	var defaultPointer *int   // nil

	fmt.Printf("명시적 선언: name=%s, age=%d, isStudent=%t\n", name, age, isStudent)
	fmt.Printf("타입 추론: language=%s, version=%.2f, isAwesome=%t\n", language, version, isAwesome)
	fmt.Printf("여러 변수: firstName=%s, lastName=%s, email=%s\n", firstName, lastName, email)
	fmt.Printf("여러 변수 (타입 추론): city=%s, country=%s\n", city, country)
	fmt.Printf("날짜: year=%d, month=%d, day=%d\n", year, month, day)
	
	fmt.Printf("제로값들:\n")
	fmt.Printf("  int: %d, float64: %f, string: '%s', bool: %t, pointer: %v\n",
		defaultInt, defaultFloat, defaultString, defaultBool, defaultPointer)
}

// typeConversions 함수는 타입 변환 방법을 보여줍니다.
func typeConversions() {
	fmt.Println("\n📝 3. 타입 변환")
	fmt.Println("---------------")

	// Go에서는 명시적 타입 변환이 필요합니다 (암시적 변환 없음)
	
	// 정수 간 변환
	var int32Val int32 = 42
	var int64Val int64 = int64(int32Val)
	var intVal int = int(int32Val)
	
	// 부동소수점 변환
	var float32Val float32 = 3.14
	var float64Val float64 = float64(float32Val)
	var intFromFloat int = int(float64Val) // 소수점 버림
	
	// 문자열과 숫자 변환
	var number int = 42
	var numberString string = fmt.Sprintf("%d", number) // 숫자를 문자열로
	
	// 문자와 숫자 변환
	var char rune = 'A'
	var charCode int = int(char)
	var codeToChar rune = rune(65)
	
	fmt.Printf("정수 변환: int32=%d → int64=%d, int=%d\n", int32Val, int64Val, intVal)
	fmt.Printf("부동소수점 변환: float32=%.2f → float64=%.2f → int=%d\n", 
		float32Val, float64Val, intFromFloat)
	fmt.Printf("문자열 변환: int=%d → string='%s'\n", number, numberString)
	fmt.Printf("문자 변환: char='%c' → code=%d, code=%d → char='%c'\n", 
		char, charCode, 65, codeToChar)
}

// constants 함수는 상수 선언과 사용법을 보여줍니다.
func constants() {
	fmt.Println("\n📝 4. 상수")
	fmt.Println("----------")

	// 상수는 const 키워드로 선언합니다
	const pi = 3.14159
	const e = 2.71828
	const (
		Sunday    = 0
		Monday    = 1
		Tuesday   = 2
		Wednesday = 3
		Thursday  = 4
		Friday    = 5
		Saturday  = 6
	)
	
	// iota를 사용한 열거형
	const (
		Red   = iota // 0
		Green        // 1
		Blue         // 2
	)
	
	// iota를 건너뛰기
	const (
		_  = iota // 0 (사용하지 않음)
		KB = 1 << (10 * iota) // 1024
		MB = 1 << (10 * iota) // 1048576
		GB = 1 << (10 * iota) // 1073741824
	)
	
	fmt.Printf("수학 상수: pi=%.5f, e=%.5f\n", pi, e)
	fmt.Printf("요일: Sunday=%d, Monday=%d, Tuesday=%d\n", Sunday, Monday, Tuesday)
	fmt.Printf("색상: Red=%d, Green=%d, Blue=%d\n", Red, Green, Blue)
	fmt.Printf("바이트 단위: KB=%d, MB=%d, GB=%d\n", KB, MB, GB)
}

// typeInference 함수는 Go의 타입 추론 기능을 보여줍니다.
func typeInference() {
	fmt.Println("\n📝 5. 타입 추론")
	fmt.Println("---------------")

	// Go는 변수 선언 시 타입을 추론할 수 있습니다
	var i = 42        // int
	var f = 3.14      // float64
	var b = true      // bool
	var s = "hello"   // string
	var c = 3 + 4i    // complex128
	
	// := 연산자를 사용한 타입 추론
	j := 42           // int
	k := 3.14         // float64
	l := true         // bool
	m := "world"      // string
	n := 1 + 2i       // complex128
	
	fmt.Printf("var 키워드 타입 추론:\n")
	fmt.Printf("  i=%d (타입: %s)\n", i, reflect.TypeOf(i))
	fmt.Printf("  f=%.2f (타입: %s)\n", f, reflect.TypeOf(f))
	fmt.Printf("  b=%t (타입: %s)\n", b, reflect.TypeOf(b))
	fmt.Printf("  s='%s' (타입: %s)\n", s, reflect.TypeOf(s))
	fmt.Printf("  c=%v (타입: %s)\n", c, reflect.TypeOf(c))
	
	fmt.Printf("\n:= 연산자 타입 추론:\n")
	fmt.Printf("  j=%d (타입: %s)\n", j, reflect.TypeOf(j))
	fmt.Printf("  k=%.2f (타입: %s)\n", k, reflect.TypeOf(k))
	fmt.Printf("  l=%t (타입: %s)\n", l, reflect.TypeOf(l))
	fmt.Printf("  m='%s' (타입: %s)\n", m, reflect.TypeOf(m))
	fmt.Printf("  n=%v (타입: %s)\n", n, reflect.TypeOf(n))
}

// complexTypes 함수는 복합 타입들을 보여줍니다.
func complexTypes() {
	fmt.Println("\n📝 6. 복합 타입")
	fmt.Println("---------------")

	// 배열 (고정 크기)
	var arr [5]int = [5]int{1, 2, 3, 4, 5}
	var arr2 = [...]int{1, 2, 3, 4, 5} // 크기 자동 추론
	
	// 슬라이스 (동적 크기)
	var slice []int = []int{1, 2, 3, 4, 5}
	var slice2 = make([]int, 5, 10) // 길이 5, 용량 10
	
	// 맵 (해시맵)
	var m map[string]int = map[string]int{"a": 1, "b": 2, "c": 3}
	var m2 = make(map[string]int) // 250625_1310 : ./variables.go:261:6: declared and not used: m2
	
	// 구조체
	type Person struct {
		Name string
		Age  int
	}
	var person Person = Person{Name: "Alice", Age: 30}
	
	// 포인터
	var ptr *int = &person.Age
	
	// 함수 타입
	var fn func(int) int = func(x int) int { return x * 2 }
	
	// 채널
	var ch chan int = make(chan int, 5)
	
	fmt.Printf("배열: %v (크기: %d)\n", arr, len(arr))
	fmt.Printf("배열 (자동 크기): %v (크기: %d)\n", arr2, len(arr2))
	fmt.Printf("슬라이스: %v (길이: %d, 용량: %d)\n", slice, len(slice), cap(slice))
	fmt.Printf("슬라이스 (make): %v (길이: %d, 용량: %d)\n", slice2, len(slice2), cap(slice2))
	fmt.Printf("맵: %v\n", m)
	fmt.Printf("구조체: %+v\n", person)
	fmt.Printf("포인터: %v (가리키는 값: %d)\n", ptr, *ptr)
	fmt.Printf("함수: fn(5) = %d\n", fn(5))
	fmt.Printf("채널: %v\n", ch)
	fmt.Printf("복소수: %v (타입: %s)\n", m2, reflect.TypeOf(m2)) // 250625_1308 : 오류수정
}

// typeChecking 함수는 타입 검사 방법을 보여줍니다.
func typeChecking() {
	fmt.Println("\n📝 7. 타입 검사")
	fmt.Println("---------------")

	// reflect 패키지를 사용한 타입 검사
	var values = []interface{}{
		42,           // int
		3.14,         // float64
		"hello",      // string
		true,         // bool
		[]int{1, 2, 3}, // slice
		map[string]int{"a": 1}, // map
		func() {},    // function
		make(chan int), // channel
	}

	for i, v := range values {
		fmt.Printf("값 %d: %v (타입: %s, 종류: %s)\n", 
			i, v, reflect.TypeOf(v), reflect.TypeOf(v).Kind())
	}
	
	// 타입 단언 (Type Assertion)
	var interfaceVal interface{} = "hello"
	if str, ok := interfaceVal.(string); ok {
		fmt.Printf("타입 단언 성공: %s\n", str)
	} else {
		fmt.Println("타입 단언 실패")
	}
	
	// 타입 스위치
	switch v := interfaceVal.(type) {
	case int:
		fmt.Printf("정수: %d\n", v)
	case string:
		fmt.Printf("문자열: %s\n", v)
	case bool:
		fmt.Printf("불린: %t\n", v)
	default:
		fmt.Printf("기타 타입: %v\n", v)
	}
} 