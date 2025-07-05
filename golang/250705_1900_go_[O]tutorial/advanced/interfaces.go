package advanced

import (
	"fmt"
	"math"
	"strconv"
	"time"
)

// ===== 인터페이스 기본 개념 =====

// Shape 인터페이스 - 도형의 기본 동작을 정의
type Shape interface {
	Area() float64
	Perimeter() float64
}

// Circle 구조체 - Shape 인터페이스를 구현
type Circle struct {
	Radius float64
}

// Circle의 Area 메서드 구현
func (c Circle) Area() float64 {
	return math.Pi * c.Radius * c.Radius
}

// Circle의 Perimeter 메서드 구현
func (c Circle) Perimeter() float64 {
	return 2 * math.Pi * c.Radius
}

// Rectangle 구조체 - Shape 인터페이스를 구현
type Rectangle struct {
	Width  float64
	Height float64
}

// Rectangle의 Area 메서드 구현
func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

// Rectangle의 Perimeter 메서드 구현
func (r Rectangle) Perimeter() float64 {
	return 2 * (r.Width + r.Height)
}

// Triangle 구조체 - Shape 인터페이스를 구현
type Triangle struct {
	A, B, C float64
}

// Triangle의 Area 메서드 구현 (헤론의 공식 사용)
func (t Triangle) Area() float64 {
	s := (t.A + t.B + t.C) / 2
	return math.Sqrt(s * (s - t.A) * (s - t.B) * (s - t.C))
}

// Triangle의 Perimeter 메서드 구현
func (t Triangle) Perimeter() float64 {
	return t.A + t.B + t.C
}

// ===== 빈 인터페이스 (Empty Interface) =====

// PrintAnything - 빈 인터페이스는 모든 타입을 받을 수 있음
func PrintAnything(v interface{}) {
	fmt.Printf("값: %v, 타입: %T\n", v, v)
}

// ===== 인터페이스 조합 (Interface Composition) =====

// Reader 인터페이스
type Reader interface {
	Read(p []byte) (n int, err error)
}

// Writer 인터페이스
type Writer interface {
	Write(p []byte) (n int, err error)
}

// Closer 인터페이스
type Closer interface {
	Close() error
}

// ReadWriter 인터페이스 - Reader와 Writer 조합
type ReadWriter interface {
	Reader
	Writer
}

// ReadWriteCloser 인터페이스 - Reader, Writer, Closer 조합
type ReadWriteCloser interface {
	Reader
	Writer
	Closer
}

// ===== 타입 단언 (Type Assertion) =====

// TypeAssertionExample - 타입 단언 예제
func TypeAssertionExample() {
	var i interface{} = "hello"
	
	// 안전한 타입 단언
	if str, ok := i.(string); ok {
		fmt.Printf("문자열: %s\n", str)
	} else {
		fmt.Println("문자열이 아님")
	}
	
	// 위험한 타입 단언 (패닉 발생 가능)
	// str := i.(string)
	
	// 여러 타입 체크
	switch v := i.(type) {
	case string:
		fmt.Printf("문자열: %s\n", v)
	case int:
		fmt.Printf("정수: %d\n", v)
	case float64:
		fmt.Printf("실수: %f\n", v)
	default:
		fmt.Printf("알 수 없는 타입: %T\n", v)
	}
}

// ===== 인터페이스 패턴들 =====

// Strategy 패턴 - 전략 패턴
type PaymentStrategy interface {
	Pay(amount float64) string
}

type CreditCardPayment struct{}
type CashPayment struct{}
type BankTransferPayment struct{}

func (c CreditCardPayment) Pay(amount float64) string {
	return fmt.Sprintf("신용카드로 %.2f원 결제", amount)
}

func (c CashPayment) Pay(amount float64) string {
	return fmt.Sprintf("현금으로 %.2f원 결제", amount)
}

func (c BankTransferPayment) Pay(amount float64) string {
	return fmt.Sprintf("계좌이체로 %.2f원 결제", amount)
}

type ShoppingCart struct {
	paymentStrategy PaymentStrategy
}

func (sc *ShoppingCart) SetPaymentStrategy(strategy PaymentStrategy) {
	sc.paymentStrategy = strategy
}

func (sc *ShoppingCart) Checkout(amount float64) string {
	return sc.paymentStrategy.Pay(amount)
}

// Factory 패턴 - 팩토리 패턴
type Animal interface {
	Speak() string
	Move() string
}

type Dog struct{}
type Cat struct{}
type Bird struct{}

func (d Dog) Speak() string { return "멍멍!" }
func (d Dog) Move() string  { return "뛰어다님" }

func (c Cat) Speak() string { return "야옹!" }
func (c Cat) Move() string  { return "살금살금 걸음" }

func (b Bird) Speak() string { return "짹짹!" }
func (b Bird) Move() string  { return "날아다님" }

// AnimalFactory - 동물 팩토리
func AnimalFactory(animalType string) Animal {
	switch animalType {
	case "dog":
		return Dog{}
	case "cat":
		return Cat{}
	case "bird":
		return Bird{}
	default:
		return nil
	}
}

// Observer 패턴 - 옵저버 패턴
type Observer interface {
	Update(message string)
}

type Subject interface {
	Attach(observer Observer)
	Detach(observer Observer)
	Notify(message string)
}

type NewsAgency struct {
	observers []Observer
}

func (na *NewsAgency) Attach(observer Observer) {
	na.observers = append(na.observers, observer)
}

func (na *NewsAgency) Detach(observer Observer) {
	for i, obs := range na.observers {
		if obs == observer {
			na.observers = append(na.observers[:i], na.observers[i+1:]...)
			break
		}
	}
}

func (na *NewsAgency) Notify(message string) {
	for _, observer := range na.observers {
		observer.Update(message)
	}
}

type NewsChannel struct {
	name string
}

func (nc NewsChannel) Update(message string) {
	fmt.Printf("[%s] 뉴스: %s\n", nc.name, message)
}

// Adapter 패턴 - 어댑터 패턴
type OldSystem interface {
	OldMethod() string
}

type NewSystem interface {
	NewMethod() string
}

type LegacySystem struct{}

func (ls LegacySystem) OldMethod() string {
	return "구식 시스템 메서드"
}

type SystemAdapter struct {
	oldSystem OldSystem
}

func (sa SystemAdapter) NewMethod() string {
	oldResult := sa.oldSystem.OldMethod()
	return fmt.Sprintf("어댑터를 통한 새로운 메서드: %s", oldResult)
}

// Decorator 패턴 - 데코레이터 패턴
type Coffee interface {
	Cost() float64
	Description() string
}

type SimpleCoffee struct{}

func (sc SimpleCoffee) Cost() float64 {
	return 2.0
}

func (sc SimpleCoffee) Description() string {
	return "기본 커피"
}

type MilkDecorator struct {
	coffee Coffee
}

func (md MilkDecorator) Cost() float64 {
	return md.coffee.Cost() + 0.5
}

func (md MilkDecorator) Description() string {
	return md.coffee.Description() + ", 우유 추가"
}

type SugarDecorator struct {
	coffee Coffee
}

func (sd SugarDecorator) Cost() float64 {
	return sd.coffee.Cost() + 0.2
}

func (sd SugarDecorator) Description() string {
	return sd.coffee.Description() + ", 설탕 추가"
}

// ===== 인터페이스 기능들 =====

// InterfaceFeatures - 인터페이스의 다양한 기능들
func InterfaceFeatures() {
	fmt.Println("\n=== 인터페이스 기능들 ===")
	
	// 1. 기본 인터페이스 사용
	fmt.Println("\n1. 기본 인터페이스 사용:")
	shapes := []Shape{
		Circle{Radius: 5},
		Rectangle{Width: 4, Height: 6},
		Triangle{A: 3, B: 4, C: 5},
	}
	
	for i, shape := range shapes {
		fmt.Printf("도형 %d: 넓이=%.2f, 둘레=%.2f\n", 
			i+1, shape.Area(), shape.Perimeter())
	}
	
	// 2. 빈 인터페이스
	fmt.Println("\n2. 빈 인터페이스:")
	PrintAnything(42)
	PrintAnything("hello")
	PrintAnything(3.14)
	PrintAnything(true)
	
	// 3. 타입 단언
	fmt.Println("\n3. 타입 단언:")
	TypeAssertionExample()
	
	// 4. Strategy 패턴
	fmt.Println("\n4. Strategy 패턴:")
	cart := &ShoppingCart{}
	
	strategies := []PaymentStrategy{
		CreditCardPayment{},
		CashPayment{},
		BankTransferPayment{},
	}
	
	for _, strategy := range strategies {
		cart.SetPaymentStrategy(strategy)
		fmt.Println(cart.Checkout(10000))
	}
	
	// 5. Factory 패턴
	fmt.Println("\n5. Factory 패턴:")
	animals := []string{"dog", "cat", "bird"}
	for _, animalType := range animals {
		animal := AnimalFactory(animalType)
		if animal != nil {
			fmt.Printf("%s: %s, %s\n", 
				animalType, animal.Speak(), animal.Move())
		}
	}
	
	// 6. Observer 패턴
	fmt.Println("\n6. Observer 패턴:")
	newsAgency := &NewsAgency{}
	channel1 := NewsChannel{name: "KBS"}
	channel2 := NewsChannel{name: "MBC"}
	
	newsAgency.Attach(channel1)
	newsAgency.Attach(channel2)
	newsAgency.Notify("중요한 뉴스가 발생했습니다!")
	
	// 7. Adapter 패턴
	fmt.Println("\n7. Adapter 패턴:")
	legacy := LegacySystem{}
	adapter := SystemAdapter{oldSystem: legacy}
	fmt.Println(adapter.NewMethod())
	
	// 8. Decorator 패턴
	fmt.Println("\n8. Decorator 패턴:")
	coffee := SimpleCoffee{}
	fmt.Printf("기본: %s, 가격: %.2f\n", 
		coffee.Description(), coffee.Cost())
	
	milkCoffee := MilkDecorator{coffee: coffee}
	fmt.Printf("우유 추가: %s, 가격: %.2f\n", 
		milkCoffee.Description(), milkCoffee.Cost())
	
	sugarMilkCoffee := SugarDecorator{coffee: milkCoffee}
	fmt.Printf("설탕 추가: %s, 가격: %.2f\n", 
		sugarMilkCoffee.Description(), sugarMilkCoffee.Cost())
}

// ===== 인터페이스 고급 기능 =====

// Stringer 인터페이스 구현
type Person struct {
	Name string
	Age  int
}

func (p Person) String() string {
	return fmt.Sprintf("%s (%d세)", p.Name, p.Age)
}

// Error 인터페이스 구현
type ValidationError struct {
	Field string
	Value string
}

func (ve ValidationError) Error() string {
	return fmt.Sprintf("필드 '%s'의 값 '%s'가 유효하지 않습니다", ve.Field, ve.Value)
}

// CustomError - 커스텀 에러 타입
type CustomError struct {
	Code    int
	Message string
	Time    time.Time
}

func (ce CustomError) Error() string {
	return fmt.Sprintf("[%d] %s (발생시간: %s)", 
		ce.Code, ce.Message, ce.Time.Format("2006-01-02 15:04:05"))
}

// ===== 인터페이스 성능 최적화 =====

// FastShape - 성능 최적화된 Shape 인터페이스
type FastShape interface {
	Area() float64
	Perimeter() float64
	Type() string
}

// FastCircle - 최적화된 Circle
type FastCircle struct {
	radius float64
	area   float64
	perimeter float64
}

func NewFastCircle(radius float64) FastCircle {
	area := math.Pi * radius * radius
	perimeter := 2 * math.Pi * radius
	return FastCircle{
		radius: radius,
		area: area,
		perimeter: perimeter,
	}
}

func (fc FastCircle) Area() float64 {
	return fc.area
}

func (fc FastCircle) Perimeter() float64 {
	return fc.perimeter
}

func (fc FastCircle) Type() string {
	return "Circle"
}

// ===== 인터페이스 테스트 헬퍼 =====

// ShapeTester - Shape 인터페이스 테스트 헬퍼
func ShapeTester(shape Shape, expectedArea, expectedPerimeter float64) bool {
	actualArea := shape.Area()
	actualPerimeter := shape.Perimeter()
	
	areaOK := math.Abs(actualArea-expectedArea) < 0.01
	perimeterOK := math.Abs(actualPerimeter-expectedPerimeter) < 0.01
	
	if areaOK && perimeterOK {
		fmt.Printf("✅ 테스트 통과: %T\n", shape)
		return true
	} else {
		fmt.Printf("❌ 테스트 실패: %T\n", shape)
		fmt.Printf("  예상: 넓이=%.2f, 둘레=%.2f\n", expectedArea, expectedPerimeter)
		fmt.Printf("  실제: 넓이=%.2f, 둘레=%.2f\n", actualArea, actualPerimeter)
		return false
	}
}

// RunInterfaceExamples - 모든 인터페이스 예제 실행
func RunInterfaceExamples() {
	fmt.Println("=== Go 인터페이스 예제 ===")
	
	// 기본 기능들 실행
	InterfaceFeatures()
	
	// Stringer 인터페이스 테스트
	fmt.Println("\n=== Stringer 인터페이스 ===")
	person := Person{Name: "김철수", Age: 25}
	fmt.Println(person) // String() 메서드 자동 호출
	
	// Error 인터페이스 테스트
	fmt.Println("\n=== Error 인터페이스 ===")
	validationErr := ValidationError{Field: "이메일", Value: "invalid-email"}
	fmt.Println(validationErr.Error())
	
	customErr := CustomError{
		Code:    404,
		Message: "페이지를 찾을 수 없습니다",
		Time:    time.Now(),
	}
	fmt.Println(customErr.Error())
	
	// 성능 최적화 테스트
	fmt.Println("\n=== 성능 최적화 ===")
	fastCircle := NewFastCircle(5)
	fmt.Printf("최적화된 원: 넓이=%.2f, 둘레=%.2f\n", 
		fastCircle.Area(), fastCircle.Perimeter())
	
	// Shape 테스트
	fmt.Println("\n=== Shape 테스트 ===")
	ShapeTester(Circle{Radius: 5}, 78.54, 31.42)
	ShapeTester(Rectangle{Width: 4, Height: 6}, 24.0, 20.0)
	ShapeTester(Triangle{A: 3, B: 4, C: 5}, 6.0, 12.0)
} 