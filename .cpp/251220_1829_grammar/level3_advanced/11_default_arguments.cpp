/*
 * 3단계 예제 11: 기본 인수 (Default Arguments)
 * 
 * 함수 매개변수에 기본값을 지정할 수 있습니다.
 * 함수 호출 시 해당 인수를 생략할 수 있습니다.
 */

#include <iostream>
using namespace std;

// 기본 인수 사용
void greet(string name, string greeting = "안녕하세요") {
    cout << greeting << ", " << name << "님!" << endl;
}

// 여러 기본 인수
void printInfo(string name, int age = 0, string city = "서울") {
    cout << "이름: " << name;
    if (age > 0) {
        cout << ", 나이: " << age;
    }
    cout << ", 도시: " << city << endl;
}

// 계산 함수
double calculatePrice(double basePrice, double taxRate = 0.1, double discount = 0.0) {
    double price = basePrice * (1 - discount);
    return price * (1 + taxRate);
}

// 오버로딩과 기본 인수
int power(int base, int exponent = 2) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main() {
    // 기본 인수 사용
    cout << "=== 기본 인수 사용 ===" << endl;
    greet("홍길동");  // 기본 인사 사용
    greet("김철수", "반갑습니다");  // 커스텀 인사
    
    // 여러 기본 인수
    cout << "\n=== 여러 기본 인수 ===" << endl;
    printInfo("이영희");
    printInfo("박민수", 25);
    printInfo("최지영", 30, "부산");
    
    // 계산 함수
    cout << "\n=== 계산 함수 ===" << endl;
    double price1 = calculatePrice(100.0);
    cout << "기본 가격 (세율 10%): " << price1 << endl;
    
    double price2 = calculatePrice(100.0, 0.2);
    cout << "세율 20%: " << price2 << endl;
    
    double price3 = calculatePrice(100.0, 0.1, 0.1);
    cout << "세율 10%, 할인 10%: " << price3 << endl;
    
    // 제곱 함수
    cout << "\n=== 제곱 함수 ===" << endl;
    cout << "power(5): " << power(5) << " (기본 지수 2)" << endl;
    cout << "power(5, 3): " << power(5, 3) << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 기본 인수는 오른쪽부터 지정해야 함" << endl;
    cout << "2. 함수 선언과 정의 중 하나에만 기본값 지정" << endl;
    cout << "3. 헤더 파일의 선언에 기본값을 두는 것이 일반적" << endl;
    cout << "4. 기본 인수는 컴파일 타임에 결정됨" << endl;
    
    return 0;
}
