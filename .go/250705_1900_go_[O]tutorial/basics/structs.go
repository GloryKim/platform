package main

import (
	"fmt"
	"time"
)

// Go 언어의 구조체(Struct) 완전 가이드
func main() {
	fmt.Println("🏗️ Go 언어 구조체(Struct) 완전 가이드")
	fmt.Println("===================================")

	// 1. 구조체 기본 사용법
	basicStructs()
	
	// 2. 구조체 필드와 태그
	structFields()
	
	// 3. 구조체 메서드
	structMethods()
	
	// 4. 구조체 임베딩
	structEmbedding()
	
	// 5. 구조체 포인터
	structPointers()
	
	// 6. 구조체의 특징과 장점
	structFeatures()
}

// basicStructs 함수는 구조체의 기본 사용법을 보여줍니다.
func basicStructs() {
	fmt.Println("\n📝 1. 구조체 기본 사용법")
	fmt.Println("------------------------")

	// 구조체 정의
	type Person struct {
		Name string
		Age  int
		City string
	}

	// 구조체 인스턴스 생성 방법들
	var person1 Person                    // 제로값으로 초기화
	person2 := Person{"Alice", 25, "Seoul"} // 위치 기반 초기화
	person3 := Person{                    // 필드명 기반 초기화
		Name: "Bob",
		Age:  30,
		City: "Busan",
	}
	person4 := Person{Name: "Charlie"}    // 일부 필드만 초기화

	fmt.Printf("person1: %+v\n", person1)
	fmt.Printf("person2: %+v\n", person2)
	fmt.Printf("person3: %+v\n", person3)
	fmt.Printf("person4: %+v\n", person4)

	// 구조체 필드 접근과 수정
	fmt.Println("\n구조체 필드 접근과 수정:")
	person := Person{Name: "David", Age: 35, City: "Incheon"}
	fmt.Printf("원본: %+v\n", person)

	// 필드 읽기
	fmt.Printf("이름: %s\n", person.Name)
	fmt.Printf("나이: %d\n", person.Age)
	fmt.Printf("도시: %s\n", person.City)

	// 필드 수정
	person.Age = 36
	person.City = "Daejeon"
	fmt.Printf("수정 후: %+v\n", person)

	// 구조체 비교
	fmt.Println("\n구조체 비교:")
	p1 := Person{Name: "Alice", Age: 25, City: "Seoul"}
	p2 := Person{Name: "Alice", Age: 25, City: "Seoul"}
	p3 := Person{Name: "Bob", Age: 30, City: "Busan"}

	fmt.Printf("p1 == p2: %t\n", p1 == p2)
	fmt.Printf("p1 == p3: %t\n", p1 == p3)

	// 구조체를 함수에 전달 (값 복사)
	fmt.Println("\n구조체를 함수에 전달:")
	modifyPerson(p1)
	fmt.Printf("원본 구조체 (변경되지 않음): %+v\n", p1)

	// 구조체를 포인터로 전달
	modifyPersonByPointer(&p1)
	fmt.Printf("포인터로 수정된 구조체: %+v\n", p1)

	// 익명 구조체
	fmt.Println("\n익명 구조체:")
	anonymous := struct {
		ID   int
		Name string
	}{
		ID:   1,
		Name: "Anonymous",
	}
	fmt.Printf("익명 구조체: %+v\n", anonymous)
}

// structFields 함수는 구조체 필드와 태그를 보여줍니다.
func structFields() {
	fmt.Println("\n📝 2. 구조체 필드와 태그")
	fmt.Println("------------------------")

	// 다양한 타입의 필드
	type ComplexStruct struct {
		// 기본 타입
		Name     string
		Age      int
		Height   float64
		IsActive bool

		// 배열과 슬라이스
		Tags     []string
		Scores   [5]int

		// 맵
		Metadata map[string]string

		// 포인터
		Next     *ComplexStruct

		// 함수 타입
		Handler  func(string) error

		// 인터페이스
		Logger   interface{}

		// 채널
		Channel  chan int

		// 구조체 태그
		JSONName string `json:"name" validate:"required"`
		XMLName  string `xml:"name" db:"user_name"`
		DBField  int    `db:"id" json:"user_id" validate:"min=1"`
	}

	// 구조체 태그 사용 예제
	fmt.Println("구조체 태그 예제:")
	user := ComplexStruct{
		Name:     "Alice",
		Age:      25,
		JSONName: "alice_user",
		XMLName:  "alice_xml",
		DBField:  123,
	}
	fmt.Printf("사용자: %+v\n", user)

	// 중첩된 구조체
	fmt.Println("\n중첩된 구조체:")
	type Address struct {
		Street  string
		City    string
		Country string
		ZipCode string
	}

	type Employee struct {
		ID      int
		Name    string
		Address Address // 중첩된 구조체
		Manager *Employee // 자기 참조
	}

	// 중첩된 구조체 초기화
	employee := Employee{
		ID:   1,
		Name: "John",
		Address: Address{
			Street:  "123 Main St",
			City:    "Seoul",
			Country: "Korea",
			ZipCode: "12345",
		},
	}
	fmt.Printf("직원: %+v\n", employee)

	// 중첩된 필드 접근
	fmt.Printf("직원 주소: %s, %s, %s\n", 
		employee.Address.Street, 
		employee.Address.City, 
		employee.Address.Country)
}

// structMethods 함수는 구조체 메서드를 보여줍니다.
func structMethods() {
	fmt.Println("\n📝 3. 구조체 메서드")
	fmt.Println("-------------------")

	// 기본 메서드
	type Rectangle struct {
		Width  float64
		Height float64
	}

	// 값 리시버 메서드
	rect := Rectangle{Width: 5.0, Height: 3.0}
	fmt.Printf("사각형: %+v\n", rect)
	fmt.Printf("면적: %.2f\n", rect.Area())
	fmt.Printf("둘레: %.2f\n", rect.Perimeter())

	// 포인터 리시버 메서드
	rect.Scale(2.0)
	fmt.Printf("확대 후: %+v\n", rect)

	// 메서드 체이닝
	rect2 := Rectangle{Width: 2.0, Height: 3.0}
	rect2.Scale(2.0).Scale(1.5)
	fmt.Printf("체이닝 후: %+v\n", rect2)

	// 인터페이스 구현
	fmt.Println("\n인터페이스 구현:")
	shapes := []Shape{rect, rect2}
	for i, shape := range shapes {
		fmt.Printf("도형 %d - 면적: %.2f, 둘레: %.2f\n", 
			i+1, shape.Area(), shape.Perimeter())
	}

	// 메서드 오버로딩 (Go에서는 지원하지 않음)
	fmt.Println("\n메서드 오버로딩 (Go에서는 지원하지 않음):")
	calculator := Calculator{}
	fmt.Printf("정수 덧셈: %d\n", calculator.Add(5, 3))
	fmt.Printf("실수 덧셈: %.2f\n", calculator.AddFloat(5.5, 3.3))
	fmt.Printf("문자열 연결: %s\n", calculator.AddString("Hello", "World"))

	// 메서드와 함수의 차이점
	fmt.Println("\n메서드와 함수의 차이점:")
	point := Point{X: 3, Y: 4}
	fmt.Printf("점: %+v\n", point)
	fmt.Printf("거리 (함수): %.2f\n", Distance(point, Point{X: 0, Y: 0}))
	fmt.Printf("거리 (메서드): %.2f\n", point.Distance(Point{X: 0, Y: 0}))
}

// structEmbedding 함수는 구조체 임베딩을 보여줍니다.
func structEmbedding() {
	fmt.Println("\n📝 4. 구조체 임베딩")
	fmt.Println("-------------------")

	// 기본 임베딩
	fmt.Println("기본 임베딩:")
	type Animal struct {
		Name string
		Age  int
	}

	func (a Animal) Speak() string {
		return fmt.Sprintf("%s가 소리를 냅니다", a.Name)
	}

	type Dog struct {
		Animal      // 임베딩 (상속과 유사)
		Breed string
	}

	dog := Dog{
		Animal: Animal{Name: "멍멍이", Age: 3},
		Breed:  "진돗개",
	}

	fmt.Printf("강아지: %+v\n", dog)
	fmt.Printf("강아지 소리: %s\n", dog.Speak())
	fmt.Printf("강아지 이름: %s\n", dog.Name) // 임베딩된 필드 직접 접근

	// 메서드 오버라이딩
	fmt.Println("\n메서드 오버라이딩:")
	func (d Dog) Speak() string {
		return fmt.Sprintf("%s가 멍멍 짖습니다", d.Name)
	}

	fmt.Printf("오버라이딩된 소리: %s\n", dog.Speak())

	// 다중 임베딩
	fmt.Println("\n다중 임베딩:")
	type Walker interface {
		Walk() string
	}

	type Swimmer interface {
		Swim() string
	}

	type Bird struct {
		Animal
		WingSpan float64
	}

	func (b Bird) Walk() string {
		return fmt.Sprintf("%s가 걸어갑니다", b.Name)
	}

	func (b Bird) Swim() string {
		return fmt.Sprintf("%s가 수영합니다", b.Name)
	}

	func (b Bird) Fly() string {
		return fmt.Sprintf("%s가 날아갑니다", b.Name)
	}

	bird := Bird{
		Animal:   Animal{Name: "참새", Age: 1},
		WingSpan: 20.5,
	}

	fmt.Printf("새: %+v\n", bird)
	fmt.Printf("새 걷기: %s\n", bird.Walk())
	fmt.Printf("새 수영: %s\n", bird.Swim())
	fmt.Printf("새 비행: %s\n", bird.Fly())

	// 임베딩과 인터페이스
	fmt.Println("\n임베딩과 인터페이스:")
	var walker Walker = bird
	var swimmer Swimmer = bird

	fmt.Printf("Walker 인터페이스: %s\n", walker.Walk())
	fmt.Printf("Swimmer 인터페이스: %s\n", swimmer.Swim())

	// 임베딩 충돌 해결
	fmt.Println("\n임베딩 충돌 해결:")
	type A struct {
		Name string
	}

	type B struct {
		Name string
	}

	type C struct {
		A
		B
	}

	c := C{
		A: A{Name: "A의 이름"},
		B: B{Name: "B의 이름"},
	}

	// 충돌하는 필드 접근
	fmt.Printf("A의 이름: %s\n", c.A.Name)
	fmt.Printf("B의 이름: %s\n", c.B.Name)
	// fmt.Printf("c.Name") // 컴파일 에러: 모호함
}

// structPointers 함수는 구조체 포인터를 보여줍니다.
func structPointers() {
	fmt.Println("\n📝 5. 구조체 포인터")
	fmt.Println("-------------------")

	// 포인터 생성 방법들
	type Student struct {
		Name string
		Age  int
		Grade int
	}

	// 방법 1: & 연산자
	student1 := Student{Name: "Alice", Age: 20, Grade: 85}
	ptr1 := &student1

	// 방법 2: new 함수
	ptr2 := new(Student)
	ptr2.Name = "Bob"
	ptr2.Age = 22
	ptr2.Grade = 90

	// 방법 3: 포인터 리터럴
	ptr3 := &Student{Name: "Charlie", Age: 21, Grade: 88}

	fmt.Printf("student1: %+v\n", student1)
	fmt.Printf("ptr1: %+v\n", *ptr1)
	fmt.Printf("ptr2: %+v\n", *ptr2)
	fmt.Printf("ptr3: %+v\n", *ptr3)

	// 포인터를 통한 필드 접근
	fmt.Println("\n포인터를 통한 필드 접근:")
	ptr1.Name = "Alice Updated"
	ptr1.Grade = 95
	fmt.Printf("수정 후 student1: %+v\n", student1)

	// nil 포인터
	fmt.Println("\nnil 포인터:")
	var nilPtr *Student
	fmt.Printf("nil 포인터: %v\n", nilPtr)
	
	// nil 포인터 접근 시 패닉
	// nilPtr.Name = "Test" // 런타임 패닉

	// 안전한 nil 포인터 처리
	if nilPtr != nil {
		nilPtr.Name = "Test"
	} else {
		fmt.Println("포인터가 nil입니다")
	}

	// 포인터 메서드
	fmt.Println("\n포인터 메서드:")
	account := &BankAccount{Balance: 1000}
	fmt.Printf("계좌: %+v\n", *account)
	
	account.Deposit(500)
	fmt.Printf("입금 후: %+v\n", *account)
	
	if err := account.Withdraw(2000); err != nil {
		fmt.Printf("출금 실패: %v\n", err)
	}
	
	if err := account.Withdraw(200); err == nil {
		fmt.Printf("출금 후: %+v\n", *account)
	}

	// 포인터 vs 값 리시버
	fmt.Println("\n포인터 vs 값 리시버:")
	counter1 := Counter{Value: 0}
	counter2 := &Counter{Value: 0}

	// 값 리시버 메서드
	counter1.Increment() // 복사본에 적용
	fmt.Printf("값 리시버: %+v\n", counter1)

	// 포인터 리시버 메서드
	counter2.Increment() // 원본에 적용
	fmt.Printf("포인터 리시버: %+v\n", *counter2)
}

// structFeatures 함수는 구조체의 특징을 설명합니다.
func structFeatures() {
	fmt.Println("\n📝 6. 구조체의 특징과 장점")
	fmt.Println("--------------------------")

	fmt.Println("✅ 구조체(Struct)의 주요 특징:")
	fmt.Println("  1. 사용자 정의 복합 타입")
	fmt.Println("  2. 값 타입 (기본적으로 복사됨)")
	fmt.Println("  3. 필드와 메서드를 가질 수 있음")
	fmt.Println("  4. 임베딩을 통한 상속과 유사한 기능")
	fmt.Println("  5. 태그를 통한 메타데이터 저장")
	fmt.Println("  6. 포인터를 통한 참조 전달 가능")
	fmt.Println("  7. 인터페이스 구현 가능")
	fmt.Println("  8. 비교 가능 (모든 필드가 비교 가능한 경우)")
	fmt.Println("  9. JSON/XML 직렬화 지원")
	fmt.Println("  10. 메모리 효율적")

	fmt.Println("\n✅ 구조체의 장점:")
	fmt.Println("  1. 데이터 캡슐화")
	fmt.Println("  2. 타입 안전성")
	fmt.Println("  3. 코드 재사용성")
	fmt.Println("  4. 명확한 데이터 구조")
	fmt.Println("  5. 메서드를 통한 동작 정의")
	fmt.Println("  6. 임베딩을 통한 코드 재사용")
	fmt.Println("  7. 인터페이스와의 조합")
	fmt.Println("  8. 메모리 효율성")

	fmt.Println("\n✅ 구조체의 사용 사례:")
	fmt.Println("  1. 데이터 모델링")
	fmt.Println("  2. API 요청/응답")
	fmt.Println("  3. 설정 관리")
	fmt.Println("  4. 도메인 객체")
	fmt.Println("  5. 값 객체")
	fmt.Println("  6. 서비스 객체")
	fmt.Println("  7. 리포지토리 패턴")
	fmt.Println("  8. 팩토리 패턴")
}

// 헬퍼 함수들

func modifyPerson(p Person) {
	p.Age = 100
	fmt.Printf("함수 내부 구조체: %+v\n", p)
}

func modifyPersonByPointer(p *Person) {
	p.Age = 100
	fmt.Printf("함수 내부 구조체 (포인터): %+v\n", *p)
}

// Person 구조체 정의
type Person struct {
	Name string
	Age  int
	City string
}

// 메서드 정의들

func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

func (r Rectangle) Perimeter() float64 {
	return 2 * (r.Width + r.Height)
}

func (r *Rectangle) Scale(factor float64) *Rectangle {
	r.Width *= factor
	r.Height *= factor
	return r
}

// Shape 인터페이스
type Shape interface {
	Area() float64
	Perimeter() float64
}

// Rectangle 구조체
type Rectangle struct {
	Width  float64
	Height float64
}

// Calculator 구조체
type Calculator struct{}

func (c Calculator) Add(a, b int) int {
	return a + b
}

func (c Calculator) AddFloat(a, b float64) float64 {
	return a + b
}

func (c Calculator) AddString(a, b string) string {
	return a + b
}

// Point 구조체
type Point struct {
	X, Y float64
}

func Distance(p1, p2 Point) float64 {
	dx := p1.X - p2.X
	dy := p1.Y - p2.Y
	return (dx*dx + dy*dy)
}

func (p Point) Distance(other Point) float64 {
	return Distance(p, other)
}

// BankAccount 구조체
type BankAccount struct {
	Balance float64
}

func (b *BankAccount) Deposit(amount float64) {
	b.Balance += amount
}

func (b *BankAccount) Withdraw(amount float64) error {
	if amount > b.Balance {
		return fmt.Errorf("잔액 부족")
	}
	b.Balance -= amount
	return nil
}

// Counter 구조체
type Counter struct {
	Value int
}

func (c Counter) Increment() {
	c.Value++
}

func (c *Counter) IncrementPointer() {
	c.Value++
} 