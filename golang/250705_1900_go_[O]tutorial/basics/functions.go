package main

import (
	"fmt"
	"math"
	"strings"
)

// Go 언어의 함수 정의와 사용에 대한 완전한 가이드
func main() {
	fmt.Println("🔧 Go 언어 함수 완전 가이드")
	fmt.Println("==========================")

	// 1. 기본 함수
	basicFunctions()
	
	// 2. 매개변수와 반환값
	parametersAndReturns()
	
	// 3. 가변 매개변수
	variadicFunctions()
	
	// 4. 다중 반환값
	multipleReturns()
	
	// 5. 익명 함수와 클로저
	anonymousFunctions()
	
	// 6. 함수 타입과 함수값
	functionTypes()
	
	// 7. 재귀 함수
	recursiveFunctions()
	
	// 8. 고차 함수
	higherOrderFunctions()
	
	// 9. 메서드 (구조체와 연결된 함수)
	methods()
	
	// 10. 함수의 장점과 특징
	functionFeatures()
}

// basicFunctions 함수는 기본적인 함수 정의와 사용법을 보여줍니다.
func basicFunctions() {
	fmt.Println("\n📝 1. 기본 함수")
	fmt.Println("---------------")

	// 함수 호출
	greet("Go")
	
	// 반환값이 있는 함수 호출
	result := add(5, 3)
	fmt.Printf("5 + 3 = %d\n", result)
	
	// 여러 함수 호출
	fmt.Printf("제곱: %d\n", square(4))
	fmt.Printf("팩토리얼: %d\n", factorial(5))
	fmt.Printf("최대값: %d\n", max(10, 20))
}

// greet 함수는 간단한 인사 함수입니다.
func greet(name string) {
	fmt.Printf("안녕하세요, %s!\n", name)
}

// add 함수는 두 정수를 더합니다.
func add(a, b int) int {
	return a + b
}

// square 함수는 숫자의 제곱을 반환합니다.
func square(x int) int {
	return x * x
}

// factorial 함수는 팩토리얼을 계산합니다.
func factorial(n int) int {
	if n <= 1 {
		return 1
	}
	return n * factorial(n-1)
}

// max 함수는 두 숫자 중 큰 값을 반환합니다.
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// parametersAndReturns 함수는 다양한 매개변수와 반환값 패턴을 보여줍니다.
func parametersAndReturns() {
	fmt.Println("\n📝 2. 매개변수와 반환값")
	fmt.Println("------------------------")

	// 다양한 타입의 매개변수
	fmt.Printf("문자열 연결: %s\n", concatenate("Hello", " ", "World"))
	fmt.Printf("평균: %.2f\n", average(1.5, 2.5, 3.5, 4.5))
	fmt.Printf("문자열 길이: %d\n", stringLength("Go Programming"))
	
	// 포인터 매개변수
	number := 42
	fmt.Printf("변경 전: %d\n", number)
	modifyValue(&number)
	fmt.Printf("변경 후: %d\n", number)
	
	// 배열과 슬라이스 매개변수
	numbers := []int{1, 2, 3, 4, 5}
	fmt.Printf("배열 합계: %d\n", sumSlice(numbers))
	
	// 맵 매개변수
	person := map[string]string{
		"name": "Alice",
		"city": "Seoul",
	}
	printMap(person)
}

// concatenate 함수는 여러 문자열을 연결합니다.
func concatenate(strs ...string) string {
	return strings.Join(strs, "")
}

// average 함수는 숫자들의 평균을 계산합니다.
func average(numbers ...float64) float64 {
	if len(numbers) == 0 {
		return 0
	}
	sum := 0.0
	for _, num := range numbers {
		sum += num
	}
	return sum / float64(len(numbers))
}

// stringLength 함수는 문자열의 길이를 반환합니다.
func stringLength(s string) int {
	return len(s)
}

// modifyValue 함수는 포인터를 통해 값을 수정합니다.
func modifyValue(ptr *int) {
	*ptr = 100
}

// sumSlice 함수는 슬라이스의 모든 요소를 더합니다.
func sumSlice(numbers []int) int {
	sum := 0
	for _, num := range numbers {
		sum += num
	}
	return sum
}

// printMap 함수는 맵의 내용을 출력합니다.
func printMap(m map[string]string) {
	fmt.Println("맵 내용:")
	for key, value := range m {
		fmt.Printf("  %s: %s\n", key, value)
	}
}

// variadicFunctions 함수는 가변 매개변수 함수를 보여줍니다.
func variadicFunctions() {
	fmt.Println("\n📝 3. 가변 매개변수")
	fmt.Println("-------------------")

	// 가변 매개변수 함수 호출
	fmt.Printf("합계: %d\n", sum(1, 2, 3, 4, 5))
	fmt.Printf("합계: %d\n", sum(10, 20))
	fmt.Printf("합계: %d\n", sum()) // 빈 인수
	
	// 슬라이스 확장
	numbers := []int{1, 2, 3, 4, 5}
	fmt.Printf("슬라이스 합계: %d\n", sum(numbers...))
	
	// 여러 타입의 가변 매개변수
	printInfo("Alice", 25, "Seoul", "Engineer")
}

// sum 함수는 가변 개수의 정수를 받아 합계를 반환합니다.
func sum(numbers ...int) int {
	total := 0
	for _, num := range numbers {
		total += num
	}
	return total
}

// printInfo 함수는 다양한 정보를 출력합니다.
func printInfo(info ...interface{}) {
	fmt.Println("정보:")
	for i, item := range info {
		fmt.Printf("  %d: %v (%T)\n", i, item, item)
	}
}

// multipleReturns 함수는 다중 반환값을 보여줍니다.
func multipleReturns() {
	fmt.Println("\n📝 4. 다중 반환값")
	fmt.Println("------------------")

	// 기본 다중 반환
	quotient, remainder := divide(17, 5)
	fmt.Printf("17 ÷ 5 = %d (나머지: %d)\n", quotient, remainder)
	
	// 에러 처리와 함께
	result, err := safeDivide(10, 2)
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("결과: %d\n", result)
	}
	
	result, err = safeDivide(10, 0)
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("결과: %d\n", result)
	}
	
	// 구조체 반환
	person := createPerson("Bob", 30)
	fmt.Printf("사람: %+v\n", person)
	
	// 여러 값 반환 (이름 지정)
	min, max := findMinMax([]int{3, 1, 4, 1, 5, 9, 2, 6})
	fmt.Printf("최소값: %d, 최대값: %d\n", min, max)
}

// divide 함수는 나눗셈의 몫과 나머지를 반환합니다.
func divide(a, b int) (int, int) {
	return a / b, a % b
}

// safeDivide 함수는 안전한 나눗셈을 수행합니다.
func safeDivide(a, b int) (int, error) {
	if b == 0 {
		return 0, fmt.Errorf("0으로 나눌 수 없습니다")
	}
	return a / b, nil
}

// Person 구조체 정의
type Person struct {
	Name string
	Age  int
}

// createPerson 함수는 Person 구조체를 생성합니다.
func createPerson(name string, age int) Person {
	return Person{Name: name, Age: age}
}

// findMinMax 함수는 슬라이스에서 최소값과 최대값을 찾습니다.
func findMinMax(numbers []int) (min, max int) {
	if len(numbers) == 0 {
		return 0, 0
	}
	
	min = numbers[0]
	max = numbers[0]
	
	for _, num := range numbers {
		if num < min {
			min = num
		}
		if num > max {
			max = num
		}
	}
	return
}

// anonymousFunctions 함수는 익명 함수와 클로저를 보여줍니다.
func anonymousFunctions() {
	fmt.Println("\n📝 5. 익명 함수와 클로저")
	fmt.Println("-------------------------")

	// 즉시 실행되는 익명 함수
	func() {
		fmt.Println("즉시 실행되는 익명 함수")
	}()
	
	// 변수에 할당된 익명 함수
	square := func(x int) int {
		return x * x
	}
	fmt.Printf("제곱 함수: %d\n", square(5))
	
	// 클로저 예제
	counter := createCounter()
	fmt.Printf("카운터: %d\n", counter()) // 1
	fmt.Printf("카운터: %d\n", counter()) // 2
	fmt.Printf("카운터: %d\n", counter()) // 3
	
	// 다른 카운터 인스턴스
	counter2 := createCounter()
	fmt.Printf("카운터2: %d\n", counter2()) // 1
	
	// 클로저를 사용한 함수 팩토리
	multiplier := createMultiplier(3)
	fmt.Printf("3배 함수: %d\n", multiplier(5)) // 15
	
	// 클로저를 사용한 상태 관리
	bankAccount := createBankAccount(1000)
	fmt.Printf("잔액: %d\n", bankAccount("balance")) // 1000
	bankAccount("deposit", 500)
	fmt.Printf("잔액: %d\n", bankAccount("balance")) // 1500
	bankAccount("withdraw", 200)
	fmt.Printf("잔액: %d\n", bankAccount("balance")) // 1300
}

// createCounter 함수는 카운터 클로저를 반환합니다.
func createCounter() func() int {
	count := 0
	return func() int {
		count++
		return count
	}
}

// createMultiplier 함수는 곱셈 클로저를 반환합니다.
func createMultiplier(factor int) func(int) int {
	return func(x int) int {
		return x * factor
	}
}

// createBankAccount 함수는 은행 계좌 클로저를 반환합니다.
func createBankAccount(initialBalance int) func(string, ...int) int {
	balance := initialBalance
	return func(action string, amounts ...int) int {
		switch action {
		case "deposit":
			if len(amounts) > 0 {
				balance += amounts[0]
			}
		case "withdraw":
			if len(amounts) > 0 && balance >= amounts[0] {
				balance -= amounts[0]
			}
		}
		return balance
	}
}

// functionTypes 함수는 함수 타입과 함수값을 보여줍니다.
func functionTypes() {
	fmt.Println("\n📝 6. 함수 타입과 함수값")
	fmt.Println("-------------------------")

	// 함수 타입 정의
	type MathFunc func(int, int) int
	
	// 함수값 할당
	var addFunc MathFunc = add
	var multiplyFunc MathFunc = func(a, b int) int {
		return a * b
	}
	
	// 함수값 사용
	fmt.Printf("더하기: %d\n", addFunc(5, 3))
	fmt.Printf("곱하기: %d\n", multiplyFunc(5, 3))
	
	// 함수를 매개변수로 받는 함수
	result := applyOperation(10, 5, addFunc)
	fmt.Printf("연산 결과: %d\n", result)
	
	result = applyOperation(10, 5, multiplyFunc)
	fmt.Printf("연산 결과: %d\n", result)
	
	// 함수를 반환하는 함수
	operation := getOperation("add")
	fmt.Printf("동적 연산: %d\n", operation(8, 4))
	
	operation = getOperation("multiply")
	fmt.Printf("동적 연산: %d\n", operation(8, 4))
}

// applyOperation 함수는 함수를 매개변수로 받습니다.
func applyOperation(a, b int, op func(int, int) int) int {
	return op(a, b)
}

// getOperation 함수는 함수를 반환합니다.
func getOperation(op string) func(int, int) int {
	switch op {
	case "add":
		return add
	case "multiply":
		return func(a, b int) int {
			return a * b
		}
	default:
		return func(a, b int) int {
			return 0
		}
	}
}

// recursiveFunctions 함수는 재귀 함수를 보여줍니다.
func recursiveFunctions() {
	fmt.Println("\n📝 7. 재귀 함수")
	fmt.Println("---------------")

	// 팩토리얼 (이미 위에서 정의됨)
	fmt.Printf("팩토리얼(5): %d\n", factorial(5))
	
	// 피보나치 수열
	fmt.Printf("피보나치(10): %d\n", fibonacci(10))
	
	// 하노이 탑
	fmt.Println("하노이 탑 (3개 원반):")
	hanoi(3, "A", "C", "B")
	
	// 이진 탐색
	numbers := []int{1, 3, 5, 7, 9, 11, 13, 15}
	target := 7
	index := binarySearch(numbers, target, 0, len(numbers)-1)
	if index != -1 {
		fmt.Printf("%d을(를) 인덱스 %d에서 찾았습니다.\n", target, index)
	} else {
		fmt.Printf("%d을(를) 찾을 수 없습니다.\n", target)
	}
}

// fibonacci 함수는 피보나치 수열을 계산합니다.
func fibonacci(n int) int {
	if n <= 1 {
		return n
	}
	return fibonacci(n-1) + fibonacci(n-2)
}

// hanoi 함수는 하노이 탑 문제를 해결합니다.
func hanoi(n int, from, to, aux string) {
	if n == 1 {
		fmt.Printf("원반 1을 %s에서 %s로 이동\n", from, to)
		return
	}
	hanoi(n-1, from, aux, to)
	fmt.Printf("원반 %d을(를) %s에서 %s로 이동\n", n, from, to)
	hanoi(n-1, aux, to, from)
}

// binarySearch 함수는 이진 탐색을 수행합니다.
func binarySearch(arr []int, target, left, right int) int {
	if left > right {
		return -1
	}
	
	mid := (left + right) / 2
	if arr[mid] == target {
		return mid
	} else if arr[mid] > target {
		return binarySearch(arr, target, left, mid-1)
	} else {
		return binarySearch(arr, target, mid+1, right)
	}
}

// higherOrderFunctions 함수는 고차 함수를 보여줍니다.
func higherOrderFunctions() {
	fmt.Println("\n📝 8. 고차 함수")
	fmt.Println("----------------")

	numbers := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	
	// map 함수 (각 요소에 함수 적용)
	squares := mapInts(numbers, func(x int) int {
		return x * x
	})
	fmt.Printf("제곱: %v\n", squares)
	
	// filter 함수 (조건에 맞는 요소만 선택)
	evens := filterInts(numbers, func(x int) bool {
		return x%2 == 0
	})
	fmt.Printf("짝수: %v\n", evens)
	
	// reduce 함수 (요소들을 하나로 축약)
	sum := reduceInts(numbers, 0, func(acc, x int) int {
		return acc + x
	})
	fmt.Printf("합계: %d\n", sum)
	
	// 체이닝
	result := reduceInts(
		filterInts(
			mapInts(numbers, func(x int) int { return x * 2 }),
			func(x int) bool { return x > 10 },
		),
		0,
		func(acc, x int) int { return acc + x },
	)
	fmt.Printf("체이닝 결과: %d\n", result)
}

// mapInts 함수는 슬라이스의 각 요소에 함수를 적용합니다.
func mapInts(numbers []int, fn func(int) int) []int {
	result := make([]int, len(numbers))
	for i, num := range numbers {
		result[i] = fn(num)
	}
	return result
}

// filterInts 함수는 조건에 맞는 요소만 선택합니다.
func filterInts(numbers []int, fn func(int) bool) []int {
	var result []int
	for _, num := range numbers {
		if fn(num) {
			result = append(result, num)
		}
	}
	return result
}

// reduceInts 함수는 요소들을 하나로 축약합니다.
func reduceInts(numbers []int, initial int, fn func(int, int) int) int {
	result := initial
	for _, num := range numbers {
		result = fn(result, num)
	}
	return result
}

// methods 함수는 구조체와 연결된 메서드를 보여줍니다.
func methods() {
	fmt.Println("\n📝 9. 메서드")
	fmt.Println("------------")

	// Circle 구조체와 메서드
	circle := Circle{Radius: 5.0}
	fmt.Printf("원의 면적: %.2f\n", circle.Area())
	fmt.Printf("원의 둘레: %.2f\n", circle.Perimeter())
	
	// 포인터 리시버 메서드
	circle.Scale(2.0)
	fmt.Printf("확대 후 반지름: %.2f\n", circle.Radius)
	
	// Rectangle 구조체와 메서드
	rect := Rectangle{Width: 4.0, Height: 6.0}
	fmt.Printf("사각형의 면적: %.2f\n", rect.Area())
	fmt.Printf("사각형의 둘레: %.2f\n", rect.Perimeter())
	
	// 인터페이스 사용
	shapes := []Shape{circle, rect}
	for i, shape := range shapes {
		fmt.Printf("도형 %d - 면적: %.2f, 둘레: %.2f\n", 
			i+1, shape.Area(), shape.Perimeter())
	}
}

// Circle 구조체 정의
type Circle struct {
	Radius float64
}

// Area 메서드는 원의 면적을 계산합니다.
func (c Circle) Area() float64 {
	return math.Pi * c.Radius * c.Radius
}

// Perimeter 메서드는 원의 둘레를 계산합니다.
func (c Circle) Perimeter() float64 {
	return 2 * math.Pi * c.Radius
}

// Scale 메서드는 원을 확대/축소합니다 (포인터 리시버).
func (c *Circle) Scale(factor float64) {
	c.Radius *= factor
}

// Rectangle 구조체 정의
type Rectangle struct {
	Width  float64
	Height float64
}

// Area 메서드는 사각형의 면적을 계산합니다.
func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

// Perimeter 메서드는 사각형의 둘레를 계산합니다.
func (r Rectangle) Perimeter() float64 {
	return 2 * (r.Width + r.Height)
}

// Shape 인터페이스 정의
type Shape interface {
	Area() float64
	Perimeter() float64
}

// functionFeatures 함수는 Go 함수의 특징을 설명합니다.
func functionFeatures() {
	fmt.Println("\n📝 10. 함수의 특징")
	fmt.Println("------------------")

	fmt.Println("✅ Go 함수의 주요 특징:")
	fmt.Println("  1. 일급 함수: 함수를 변수에 할당하고 매개변수로 전달 가능")
	fmt.Println("  2. 클로저: 함수가 자신이 선언된 환경의 변수를 캡처 가능")
	fmt.Println("  3. 다중 반환값: 여러 값을 동시에 반환 가능")
	fmt.Println("  4. 가변 매개변수: 개수가 정해지지 않은 매개변수 지원")
	fmt.Println("  5. 명명된 반환값: 반환값에 이름을 지정 가능")
	fmt.Println("  6. 익명 함수: 이름 없는 함수 정의 가능")
	fmt.Println("  7. 메서드: 구조체와 연결된 함수")
	fmt.Println("  8. 함수 타입: 함수를 타입으로 사용 가능")
	fmt.Println("  9. 재귀: 자기 자신을 호출하는 함수")
	fmt.Println("  10. 고차 함수: 함수를 매개변수로 받거나 반환하는 함수")
} 