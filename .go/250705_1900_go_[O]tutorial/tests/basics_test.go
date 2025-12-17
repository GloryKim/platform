package tests

import (
	"fmt"
	"os"
	"reflect"
	"strconv"
	"strings"
	"testing"
)

// ===== 변수 테스트 =====

func TestVariableTypes(t *testing.T) {
	// 정수형 테스트
	var intVar int = 42
	if intVar != 42 {
		t.Errorf("정수형 변수 테스트 실패: 기대값 42, 실제값 %d", intVar)
	}

	// 문자열 테스트
	var stringVar string = "Hello, Go!"
	if stringVar != "Hello, Go!" {
		t.Errorf("문자열 변수 테스트 실패: 기대값 'Hello, Go!', 실제값 '%s'", stringVar)
	}

	// 불린형 테스트
	var boolVar bool = true
	if !boolVar {
		t.Errorf("불린형 변수 테스트 실패: 기대값 true, 실제값 %t", boolVar)
	}

	// 실수형 테스트
	var floatVar float64 = 3.14
	if floatVar != 3.14 {
		t.Errorf("실수형 변수 테스트 실패: 기대값 3.14, 실제값 %f", floatVar)
	}
}

func TestVariableDeclaration(t *testing.T) {
	// 짧은 변수 선언
	shortVar := "short declaration"
	if shortVar != "short declaration" {
		t.Errorf("짧은 변수 선언 테스트 실패: %s", shortVar)
	}

	// 다중 변수 선언
	var1, var2 := 1, "two"
	if var1 != 1 || var2 != "two" {
		t.Errorf("다중 변수 선언 테스트 실패: %d, %s", var1, var2)
	}

	// 타입 추론
	inferredVar := 42
	if reflect.TypeOf(inferredVar).Kind() != reflect.Int {
		t.Errorf("타입 추론 테스트 실패: 기대값 int, 실제값 %T", inferredVar)
	}
}

func TestTypeConversion(t *testing.T) {
	// 정수에서 실수로 변환
	intVal := 42
	floatVal := float64(intVal)
	if floatVal != 42.0 {
		t.Errorf("정수에서 실수 변환 테스트 실패: %f", floatVal)
	}

	// 실수에서 정수로 변환
	floatVal2 := 3.14
	intVal2 := int(floatVal2)
	if intVal2 != 3 {
		t.Errorf("실수에서 정수 변환 테스트 실패: %d", intVal2)
	}

	// 문자열에서 정수로 변환
	strVal := "123"
	intVal3, err := strconv.Atoi(strVal)
	if err != nil || intVal3 != 123 {
		t.Errorf("문자열에서 정수 변환 테스트 실패: %d, %v", intVal3, err)
	}

	// 정수에서 문자열로 변환
	intVal4 := 456
	strVal2 := strconv.Itoa(intVal4)
	if strVal2 != "456" {
		t.Errorf("정수에서 문자열 변환 테스트 실패: %s", strVal2)
	}
}

// ===== 함수 테스트 =====

// 테스트용 함수들
func add(a, b int) int {
	return a + b
}

func multiply(a, b int) int {
	return a * b
}

func greet(name string) string {
	return "Hello, " + name + "!"
}

func divide(a, b int) (int, error) {
	if b == 0 {
		return 0, &DivisionError{Message: "0으로 나눌 수 없습니다"}
	}
	return a / b, nil
}

type DivisionError struct {
	Message string
}

func (e *DivisionError) Error() string {
	return e.Message
}

func TestFunctions(t *testing.T) {
	// 기본 함수 테스트
	result := add(5, 3)
	if result != 8 {
		t.Errorf("덧셈 함수 테스트 실패: 기대값 8, 실제값 %d", result)
	}

	// 곱셈 함수 테스트
	result2 := multiply(4, 6)
	if result2 != 24 {
		t.Errorf("곱셈 함수 테스트 실패: 기대값 24, 실제값 %d", result2)
	}

	// 문자열 함수 테스트
	greeting := greet("Go")
	expected := "Hello, Go!"
	if greeting != expected {
		t.Errorf("인사 함수 테스트 실패: 기대값 '%s', 실제값 '%s'", expected, greeting)
	}
}

func TestFunctionWithError(t *testing.T) {
	// 정상적인 나눗셈
	result, err := divide(10, 2)
	if err != nil {
		t.Errorf("나눗셈 함수 테스트 실패: 예상치 못한 에러 %v", err)
	}
	if result != 5 {
		t.Errorf("나눗셈 함수 테스트 실패: 기대값 5, 실제값 %d", result)
	}

	// 0으로 나누기
	_, err = divide(10, 0)
	if err == nil {
		t.Error("0으로 나누기 테스트 실패: 에러가 발생해야 합니다")
	}
	if err.Error() != "0으로 나눌 수 없습니다" {
		t.Errorf("에러 메시지 테스트 실패: 기대값 '0으로 나눌 수 없습니다', 실제값 '%s'", err.Error())
	}
}

// ===== 제어문 테스트 =====

func TestIfStatement(t *testing.T) {
	// if 문 테스트
	value := 10
	var result string

	if value > 5 {
		result = "큰 수"
	} else {
		result = "작은 수"
	}

	if result != "큰 수" {
		t.Errorf("if 문 테스트 실패: 기대값 '큰 수', 실제값 '%s'", result)
	}

	// if-else if-else 테스트
	value2 := 3
	var result2 string

	if value2 > 10 {
		result2 = "매우 큰 수"
	} else if value2 > 5 {
		result2 = "큰 수"
	} else {
		result2 = "작은 수"
	}

	if result2 != "작은 수" {
		t.Errorf("if-else if-else 테스트 실패: 기대값 '작은 수', 실제값 '%s'", result2)
	}
}

func TestForLoop(t *testing.T) {
	// 기본 for 루프
	sum := 0
	for i := 1; i <= 5; i++ {
		sum += i
	}
	if sum != 15 {
		t.Errorf("기본 for 루프 테스트 실패: 기대값 15, 실제값 %d", sum)
	}

	// while 스타일 for 루프
	count := 0
	for count < 3 {
		count++
	}
	if count != 3 {
		t.Errorf("while 스타일 for 루프 테스트 실패: 기대값 3, 실제값 %d", count)
	}

	// range를 사용한 for 루프
	numbers := []int{1, 2, 3, 4, 5}
	sum2 := 0
	for _, num := range numbers {
		sum2 += num
	}
	if sum2 != 15 {
		t.Errorf("range for 루프 테스트 실패: 기대값 15, 실제값 %d", sum2)
	}
}

func TestSwitchStatement(t *testing.T) {
	// 기본 switch 문
	day := "월요일"
	var result string

	switch day {
	case "월요일":
		result = "월요일"
	case "화요일":
		result = "화요일"
	default:
		result = "기타"
	}

	if result != "월요일" {
		t.Errorf("기본 switch 문 테스트 실패: 기대값 '월요일', 실제값 '%s'", result)
	}

	// 표현식이 있는 switch 문
	value := 5
	var result2 string

	switch {
	case value < 0:
		result2 = "음수"
	case value == 0:
		result2 = "영"
	case value > 0:
		result2 = "양수"
	}

	if result2 != "양수" {
		t.Errorf("표현식 switch 문 테스트 실패: 기대값 '양수', 실제값 '%s'", result2)
	}
}

// ===== 배열과 슬라이스 테스트 =====

func TestArrays(t *testing.T) {
	// 배열 선언과 초기화
	var arr [5]int
	arr[0] = 1
	arr[1] = 2
	arr[2] = 3
	arr[3] = 4
	arr[4] = 5

	// 배열 길이 테스트
	if len(arr) != 5 {
		t.Errorf("배열 길이 테스트 실패: 기대값 5, 실제값 %d", len(arr))
	}

	// 배열 요소 접근 테스트
	if arr[0] != 1 || arr[4] != 5 {
		t.Errorf("배열 요소 접근 테스트 실패")
	}

	// 배열 리터럴
	arr2 := [3]string{"apple", "banana", "cherry"}
	if len(arr2) != 3 {
		t.Errorf("배열 리터럴 테스트 실패: 기대값 3, 실제값 %d", len(arr2))
	}
}

func TestSlices(t *testing.T) {
	// 슬라이스 생성
	slice := make([]int, 0, 5)
	
	// 슬라이스에 요소 추가
	slice = append(slice, 1, 2, 3, 4, 5)
	
	// 슬라이스 길이와 용량 테스트
	if len(slice) != 5 {
		t.Errorf("슬라이스 길이 테스트 실패: 기대값 5, 실제값 %d", len(slice))
	}
	
	if cap(slice) != 5 {
		t.Errorf("슬라이스 용량 테스트 실패: 기대값 5, 실제값 %d", cap(slice))
	}

	// 슬라이스 슬라이싱
	subSlice := slice[1:4]
	if len(subSlice) != 3 {
		t.Errorf("슬라이스 슬라이싱 테스트 실패: 기대값 3, 실제값 %d", len(subSlice))
	}

	// 슬라이스 복사
	slice2 := make([]int, len(slice))
	copy(slice2, slice)
	
	if !reflect.DeepEqual(slice, slice2) {
		t.Error("슬라이스 복사 테스트 실패")
	}
}

// ===== 맵 테스트 =====

func TestMaps(t *testing.T) {
	// 맵 생성
	m := make(map[string]int)
	
	// 맵에 키-값 쌍 추가
	m["apple"] = 1
	m["banana"] = 2
	m["cherry"] = 3

	// 맵 길이 테스트
	if len(m) != 3 {
		t.Errorf("맵 길이 테스트 실패: 기대값 3, 실제값 %d", len(m))
	}

	// 맵 값 접근 테스트
	if m["apple"] != 1 {
		t.Errorf("맵 값 접근 테스트 실패: 기대값 1, 실제값 %d", m["apple"])
	}

	// 맵 키 존재 확인
	value, exists := m["apple"]
	if !exists {
		t.Error("맵 키 존재 확인 테스트 실패: 키가 존재해야 합니다")
	}
	if value != 1 {
		t.Errorf("맵 키 존재 확인 테스트 실패: 기대값 1, 실제값 %d", value)
	}

	// 존재하지 않는 키
	_, exists = m["orange"]
	if exists {
		t.Error("존재하지 않는 키 테스트 실패: 키가 존재하지 않아야 합니다")
	}

	// 맵에서 키-값 쌍 삭제
	delete(m, "banana")
	if len(m) != 2 {
		t.Errorf("맵 삭제 테스트 실패: 기대값 2, 실제값 %d", len(m))
	}
}

// ===== 구조체 테스트 =====

// 테스트용 구조체
type Person struct {
	Name string
	Age  int
}

func (p Person) GetInfo() string {
	return p.Name + " (" + strconv.Itoa(p.Age) + "세)"
}

func (p *Person) Birthday() {
	p.Age++
}

type Employee struct {
	Person
	Salary int
	Title  string
}

func TestStructs(t *testing.T) {
	// 구조체 생성
	person := Person{Name: "김철수", Age: 25}
	
	// 구조체 필드 접근
	if person.Name != "김철수" {
		t.Errorf("구조체 필드 접근 테스트 실패: 기대값 '김철수', 실제값 '%s'", person.Name)
	}
	
	if person.Age != 25 {
		t.Errorf("구조체 필드 접근 테스트 실패: 기대값 25, 실제값 %d", person.Age)
	}

	// 구조체 메서드 테스트
	info := person.GetInfo()
	expected := "김철수 (25세)"
	if info != expected {
		t.Errorf("구조체 메서드 테스트 실패: 기대값 '%s', 실제값 '%s'", expected, info)
	}

	// 포인터 리시버 메서드 테스트
	person.Birthday()
	if person.Age != 26 {
		t.Errorf("포인터 리시버 메서드 테스트 실패: 기대값 26, 실제값 %d", person.Age)
	}
}

func TestStructEmbedding(t *testing.T) {
	// 구조체 임베딩
	employee := Employee{
		Person: Person{Name: "이영희", Age: 30},
		Salary: 50000,
		Title:  "개발자",
	}

	// 임베딩된 구조체의 필드 접근
	if employee.Name != "이영희" {
		t.Errorf("구조체 임베딩 테스트 실패: 기대값 '이영희', 실제값 '%s'", employee.Name)
	}

	// 임베딩된 구조체의 메서드 호출
	info := employee.GetInfo()
	expected := "이영희 (30세)"
	if info != expected {
		t.Errorf("임베딩된 구조체 메서드 테스트 실패: 기대값 '%s', 실제값 '%s'", expected, info)
	}

	// 자체 필드 접근
	if employee.Salary != 50000 {
		t.Errorf("구조체 자체 필드 테스트 실패: 기대값 50000, 실제값 %d", employee.Salary)
	}
}

// ===== 벤치마크 테스트 =====

func BenchmarkSliceAppend(b *testing.B) {
	for i := 0; i < b.N; i++ {
		slice := make([]int, 0)
		for j := 0; j < 1000; j++ {
			slice = append(slice, j)
		}
	}
}

func BenchmarkMapAccess(b *testing.B) {
	m := make(map[string]int)
	for i := 0; i < 1000; i++ {
		m[strconv.Itoa(i)] = i
	}
	
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = m["500"]
	}
}

// ===== 테이블 주도 테스트 =====

func TestAddFunction(t *testing.T) {
	tests := []struct {
		name     string
		a, b     int
		expected int
	}{
		{"양수 덧셈", 2, 3, 5},
		{"음수 덧셈", -2, -3, -5},
		{"0 포함", 0, 5, 5},
		{"큰 수", 1000, 2000, 3000},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := add(tt.a, tt.b)
			if result != tt.expected {
				t.Errorf("add(%d, %d) = %d; 기대값 %d", tt.a, tt.b, result, tt.expected)
			}
		})
	}
}

func TestGreetFunction(t *testing.T) {
	tests := []struct {
		name     string
		input    string
		expected string
	}{
		{"한국어 이름", "김철수", "Hello, 김철수!"},
		{"영어 이름", "John", "Hello, John!"},
		{"빈 문자열", "", "Hello, !"},
		{"특수문자", "!@#", "Hello, !@#!"},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := greet(tt.input)
			if result != tt.expected {
				t.Errorf("greet(%s) = %s; 기대값 %s", tt.input, result, tt.expected)
			}
		})
	}
}

// ===== 서브테스트 =====

func TestStringOperations(t *testing.T) {
	t.Run("문자열 연결", func(t *testing.T) {
		str1 := "Hello"
		str2 := "World"
		result := str1 + " " + str2
		if result != "Hello World" {
			t.Errorf("문자열 연결 테스트 실패: %s", result)
		}
	})

	t.Run("문자열 포함 확인", func(t *testing.T) {
		str := "Hello, Go!"
		if !strings.Contains(str, "Go") {
			t.Error("문자열 포함 확인 테스트 실패")
		}
		if strings.Contains(str, "Python") {
			t.Error("문자열 포함 확인 테스트 실패")
		}
	})

	t.Run("문자열 대소문자 변환", func(t *testing.T) {
		str := "Hello, Go!"
		upper := strings.ToUpper(str)
		lower := strings.ToLower(str)
		
		if upper != "HELLO, GO!" {
			t.Errorf("대문자 변환 테스트 실패: %s", upper)
		}
		if lower != "hello, go!" {
			t.Errorf("소문자 변환 테스트 실패: %s", lower)
		}
	})
}

// ===== 예제 테스트 =====

func ExampleAdd() {
	result := add(3, 4)
	fmt.Println(result)
	// Output: 7
}

func ExampleGreet() {
	greeting := greet("Go")
	fmt.Println(greeting)
	// Output: Hello, Go!
}

// ===== 테스트 헬퍼 함수 =====

func assertEqual(t *testing.T, expected, actual interface{}) {
	t.Helper()
	if !reflect.DeepEqual(expected, actual) {
		t.Errorf("기대값: %v, 실제값: %v", expected, actual)
	}
}

func assertTrue(t *testing.T, condition bool, message string) {
	t.Helper()
	if !condition {
		t.Error(message)
	}
}

func assertFalse(t *testing.T, condition bool, message string) {
	t.Helper()
	if condition {
		t.Error(message)
	}
}

// ===== 테스트 설정 =====

func TestMain(m *testing.M) {
	// 테스트 시작 전 설정
	setup()
	
	// 테스트 실행
	code := m.Run()
	
	// 테스트 종료 후 정리
	teardown()
	
	os.Exit(code)
}

func setup() {
	// 테스트 환경 설정
}

func teardown() {
	// 테스트 환경 정리
} 