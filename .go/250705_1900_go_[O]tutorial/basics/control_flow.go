package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Go 언어의 제어문 완전 가이드
func main() {
	fmt.Println("🔄 Go 언어 제어문 완전 가이드")
	fmt.Println("============================")

	// 1. if 문
	ifStatements()
	
	// 2. for 문
	forStatements()
	
	// 3. switch 문
	switchStatements()
	
	// 4. break와 continue
	breakAndContinue()
	
	// 5. goto 문 (권장하지 않지만 이해를 위해)
	gotoStatements()
	
	// 6. 실용적인 제어문 패턴
	practicalPatterns()
	
	// 7. 제어문의 특징과 장점
	controlFlowFeatures()
}

// ifStatements 함수는 if 문의 다양한 사용법을 보여줍니다.
func ifStatements() {
	fmt.Println("\n📝 1. if 문")
	fmt.Println("-----------")

	// 기본 if 문
	number := 42
	if number > 40 {
		fmt.Printf("%d은(는) 40보다 큽니다.\n", number)
	}

	// if-else 문
	age := 25
	if age >= 18 {
		fmt.Println("성인입니다.")
	} else {
		fmt.Println("미성년자입니다.")
	}

	// if-else if-else 문
	score := 85
	if score >= 90 {
		fmt.Println("A등급")
	} else if score >= 80 {
		fmt.Println("B등급")
	} else if score >= 70 {
		fmt.Println("C등급")
	} else {
		fmt.Println("D등급")
	}

	// if 문에서 변수 선언과 조건 검사 동시에
	if value := getRandomNumber(); value > 50 {
		fmt.Printf("랜덤 값 %d은(는) 50보다 큽니다.\n", value)
	} else {
		fmt.Printf("랜덤 값 %d은(는) 50 이하입니다.\n", value)
	}

	// 에러 처리 패턴
	if result, err := divideSafely(10, 2); err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("결과: %d\n", result)
	}

	// 중첩된 if 문
	user := "admin"
	password := "secret"
	if user == "admin" {
		if password == "secret" {
			fmt.Println("관리자 로그인 성공")
		} else {
			fmt.Println("비밀번호가 틀렸습니다")
		}
	} else {
		fmt.Println("사용자가 존재하지 않습니다")
	}

	// 조건부 변수 할당
	if name := getUserName(); name != "" {
		fmt.Printf("사용자: %s\n", name)
	} else {
		fmt.Println("사용자 이름이 없습니다")
	}
}

// forStatements 함수는 for 문의 다양한 사용법을 보여줍니다.
func forStatements() {
	fmt.Println("\n📝 2. for 문")
	fmt.Println("------------")

	// 기본 for 문 (C 스타일)
	fmt.Println("기본 for 문:")
	for i := 0; i < 5; i++ {
		fmt.Printf("%d ", i)
	}
	fmt.Println()

	// while 스타일 for 문
	fmt.Println("while 스타일 for 문:")
	counter := 0
	for counter < 5 {
		fmt.Printf("%d ", counter)
		counter++
	}
	fmt.Println()

	// 무한 루프
	fmt.Println("무한 루프 (5번만 실행):")
	count := 0
	for {
		fmt.Printf("%d ", count)
		count++
		if count >= 5 {
			break
		}
	}
	fmt.Println()

	// range를 사용한 for 문
	fmt.Println("range를 사용한 슬라이스 순회:")
	numbers := []int{1, 2, 3, 4, 5}
	for index, value := range numbers {
		fmt.Printf("인덱스 %d: 값 %d\n", index, value)
	}

	// 인덱스만 사용
	fmt.Println("인덱스만 사용:")
	for index := range numbers {
		fmt.Printf("인덱스 %d\n", index)
	}

	// 값만 사용 (인덱스 무시)
	fmt.Println("값만 사용:")
	for _, value := range numbers {
		fmt.Printf("값 %d\n", value)
	}

	// 맵 순회
	fmt.Println("맵 순회:")
	person := map[string]string{
		"name": "Alice",
		"city": "Seoul",
		"job":  "Engineer",
	}
	for key, value := range person {
		fmt.Printf("%s: %s\n", key, value)
	}

	// 문자열 순회 (룬 단위)
	fmt.Println("문자열 순회:")
	text := "안녕하세요"
	for index, char := range text {
		fmt.Printf("인덱스 %d: 문자 '%c' (코드: %d)\n", index, char, char)
	}

	// 중첩된 for 문
	fmt.Println("중첩된 for 문 (구구단 2단):")
	for i := 1; i <= 9; i++ {
		for j := 1; j <= 9; j++ {
			if j == 1 {
				fmt.Printf("%d단: ", i)
			}
			fmt.Printf("%d×%d=%d ", i, j, i*j)
			if j == 9 {
				fmt.Println()
			}
		}
		if i == 2 {
			break // 2단만 출력
		}
	}

	// 조건부 반복
	fmt.Println("조건부 반복:")
	randomNumbers := generateRandomNumbers(10)
	for i, num := range randomNumbers {
		if num%2 == 0 {
			fmt.Printf("짝수 %d (인덱스 %d)\n", num, i)
		}
	}
}

// switchStatements 함수는 switch 문의 다양한 사용법을 보여줍니다.
func switchStatements() {
	fmt.Println("\n📝 3. switch 문")
	fmt.Println("---------------")

	// 기본 switch 문
	fmt.Println("기본 switch 문:")
	day := "Monday"
	switch day {
	case "Monday":
		fmt.Println("월요일 - 새로운 한 주의 시작")
	case "Tuesday":
		fmt.Println("화요일 - 일주일의 두 번째 날")
	case "Wednesday":
		fmt.Println("수요일 - 한 주의 중간")
	case "Thursday":
		fmt.Println("목요일 - 주말이 다가오는 날")
	case "Friday":
		fmt.Println("금요일 - TGIF!")
	case "Saturday", "Sunday":
		fmt.Println("주말 - 휴식의 시간")
	default:
		fmt.Println("알 수 없는 요일")
	}

	// switch 문에서 변수 선언
	fmt.Println("switch 문에서 변수 선언:")
	switch hour := time.Now().Hour(); {
	case hour < 12:
		fmt.Println("좋은 아침입니다!")
	case hour < 17:
		fmt.Println("좋은 오후입니다!")
	default:
		fmt.Println("좋은 저녁입니다!")
	}

	// 조건부 switch 문
	fmt.Println("조건부 switch 문:")
	score := 85
	switch {
	case score >= 90:
		fmt.Println("A등급")
	case score >= 80:
		fmt.Println("B등급")
	case score >= 70:
		fmt.Println("C등급")
	case score >= 60:
		fmt.Println("D등급")
	default:
		fmt.Println("F등급")
	}

	// 타입 switch 문
	fmt.Println("타입 switch 문:")
	printType(42)
	printType("hello")
	printType(3.14)
	printType(true)
	printType([]int{1, 2, 3})

	// fallthrough 사용
	fmt.Println("fallthrough 사용:")
	grade := "B"
	switch grade {
	case "A":
		fmt.Println("우수")
		fallthrough
	case "B":
		fmt.Println("양호")
		fallthrough
	case "C":
		fmt.Println("보통")
	default:
		fmt.Println("미흡")
	}

	// switch 문에서 함수 호출
	fmt.Println("switch 문에서 함수 호출:")
	switch getDayOfWeek() {
	case "Monday":
		fmt.Println("월요일 블루")
	case "Friday":
		fmt.Println("금요일 기분 좋음")
	default:
		fmt.Println("평범한 하루")
	}
}

// breakAndContinue 함수는 break와 continue의 사용법을 보여줍니다.
func breakAndContinue() {
	fmt.Println("\n📝 4. break와 continue")
	fmt.Println("----------------------")

	// break 사용
	fmt.Println("break 사용:")
	for i := 0; i < 10; i++ {
		if i == 5 {
			break // 5에서 루프 종료
		}
		fmt.Printf("%d ", i)
	}
	fmt.Println()

	// continue 사용
	fmt.Println("continue 사용:")
	for i := 0; i < 10; i++ {
		if i%2 == 0 {
			continue // 짝수는 건너뛰기
		}
		fmt.Printf("%d ", i)
	}
	fmt.Println()

	// 레이블이 있는 break
	fmt.Println("레이블이 있는 break:")
OuterLoop:
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if i == 1 && j == 1 {
				break OuterLoop // 외부 루프 종료
			}
			fmt.Printf("(%d,%d) ", i, j)
		}
	}
	fmt.Println()

	// 레이블이 있는 continue
	fmt.Println("레이블이 있는 continue:")
OuterLoop2:
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if i == 1 {
				continue OuterLoop2 // 외부 루프의 다음 반복으로
			}
			fmt.Printf("(%d,%d) ", i, j)
		}
	}
	fmt.Println()

	// switch 문에서 break
	fmt.Println("switch 문에서 break:")
	for i := 0; i < 5; i++ {
		switch i {
		case 0, 1:
			fmt.Printf("case %d\n", i)
		case 2:
			fmt.Printf("case %d에서 break\n", i)
			break
		default:
			fmt.Printf("default case %d\n", i)
		}
	}
}

// gotoStatements 함수는 goto 문의 사용법을 보여줍니다 (권장하지 않음).
func gotoStatements() {
	fmt.Println("\n📝 5. goto 문 (권장하지 않음)")
	fmt.Println("------------------------------")

	// goto 문 사용 (에러 처리 패턴)
	fmt.Println("goto 문을 사용한 에러 처리:")
	if err := step1(); err != nil {
		goto cleanup
	}
	if err := step2(); err != nil {
		goto cleanup
	}
	if err := step3(); err != nil {
		goto cleanup
	}
	fmt.Println("모든 단계 성공")
	return

cleanup:
	fmt.Println("정리 작업 수행")
	fmt.Println("에러 발생으로 종료")

	// goto 문을 사용한 루프 (권장하지 않음)
	fmt.Println("goto 문을 사용한 루프:")
	i := 0
loop:
	if i < 5 {
		fmt.Printf("%d ", i)
		i++
		goto loop
	}
	fmt.Println()
}

// practicalPatterns 함수는 실용적인 제어문 패턴을 보여줍니다.
func practicalPatterns() {
	fmt.Println("\n📝 6. 실용적인 제어문 패턴")
	fmt.Println("---------------------------")

	// 에러 처리 패턴
	fmt.Println("에러 처리 패턴:")
	if err := processData(); err != nil {
		fmt.Printf("데이터 처리 실패: %v\n", err)
		return
	}
	fmt.Println("데이터 처리 성공")

	// 조건부 초기화
	fmt.Println("조건부 초기화:")
	if config := loadConfig(); config != nil {
		fmt.Printf("설정 로드됨: %+v\n", config)
	} else {
		fmt.Println("기본 설정 사용")
	}

	// 반복문에서 조건 검사
	fmt.Println("반복문에서 조건 검사:")
	items := []string{"apple", "banana", "cherry", "date"}
	for i, item := range items {
		if item == "cherry" {
			fmt.Printf("체리를 인덱스 %d에서 찾았습니다\n", i)
			break
		}
	}

	// 중첩된 조건문 최적화
	fmt.Println("중첩된 조건문 최적화:")
	user := getUser()
	if user == nil {
		fmt.Println("사용자가 없습니다")
		return
	}
	if user.Age < 18 {
		fmt.Println("미성년자입니다")
		return
	}
	if user.Balance < 1000 {
		fmt.Println("잔액이 부족합니다")
		return
	}
	fmt.Println("모든 조건을 만족합니다")

	// switch 문을 사용한 명령어 처리
	fmt.Println("switch 문을 사용한 명령어 처리:")
	commands := []string{"start", "stop", "restart", "status"}
	for _, cmd := range commands {
		switch cmd {
		case "start":
			fmt.Println("서비스 시작")
		case "stop":
			fmt.Println("서비스 중지")
		case "restart":
			fmt.Println("서비스 재시작")
		case "status":
			fmt.Println("서비스 상태 확인")
		default:
			fmt.Printf("알 수 없는 명령어: %s\n", cmd)
		}
	}
}

// controlFlowFeatures 함수는 Go 제어문의 특징을 설명합니다.
func controlFlowFeatures() {
	fmt.Println("\n📝 7. 제어문의 특징과 장점")
	fmt.Println("---------------------------")

	fmt.Println("✅ Go 제어문의 주요 특징:")
	fmt.Println("  1. if 문에서 변수 선언과 조건 검사 동시 가능")
	fmt.Println("  2. for 문은 Go의 유일한 반복문 (while, do-while 없음)")
	fmt.Println("  3. range를 사용한 컬렉션 순회")
	fmt.Println("  4. switch 문에서 break 자동 (fallthrough 명시적)")
	fmt.Println("  5. 타입 switch로 런타임 타입 검사")
	fmt.Println("  6. 레이블을 사용한 중첩 루프 제어")
	fmt.Println("  7. goto 문 지원 (권장하지 않음)")
	fmt.Println("  8. 조건부 변수 할당과 함께 사용 가능")
	fmt.Println("  9. 에러 처리에 최적화된 패턴")
	fmt.Println("  10. 간결하고 읽기 쉬운 문법")
}

// 헬퍼 함수들

func getRandomNumber() int {
	rand.Seed(time.Now().UnixNano())
	return rand.Intn(100)
}

func divideSafely(a, b int) (int, error) {
	if b == 0 {
		return 0, fmt.Errorf("0으로 나눌 수 없습니다")
	}
	return a / b, nil
}

func getUserName() string {
	// 시뮬레이션
	return "Alice"
}

func generateRandomNumbers(count int) []int {
	rand.Seed(time.Now().UnixNano())
	numbers := make([]int, count)
	for i := 0; i < count; i++ {
		numbers[i] = rand.Intn(100)
	}
	return numbers
}

func printType(value interface{}) {
	switch v := value.(type) {
	case int:
		fmt.Printf("정수: %d\n", v)
	case string:
		fmt.Printf("문자열: %s\n", v)
	case float64:
		fmt.Printf("부동소수점: %f\n", v)
	case bool:
		fmt.Printf("불린: %t\n", v)
	default:
		fmt.Printf("기타 타입: %v\n", v)
	}
}

func getDayOfWeek() string {
	days := []string{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}
	rand.Seed(time.Now().UnixNano())
	return days[rand.Intn(len(days))]
}

// 에러 처리 시뮬레이션 함수들
func step1() error {
	return nil
}

func step2() error {
	return fmt.Errorf("step2 실패")
}

func step3() error {
	return nil
}

func processData() error {
	// 시뮬레이션
	return nil
}

// 설정 구조체
type Config struct {
	Host string
	Port int
}

func loadConfig() *Config {
	// 시뮬레이션
	return &Config{Host: "localhost", Port: 8080}
}

// 사용자 구조체
type User struct {
	Name    string
	Age     int
	Balance int
}

func getUser() *User {
	// 시뮬레이션
	return &User{Name: "Bob", Age: 25, Balance: 500}
} 