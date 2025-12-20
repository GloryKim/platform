/*
 * 3단계 예제 1: 함수 기본
 * 
 * 함수를 정의하고 호출하는 기본 방법을 학습합니다.
 * 코드 재사용성과 모듈화를 위한 핵심 개념입니다.
 */

#include <iostream>
using namespace std;

// 함수 선언 (프로토타입)
int add(int a, int b);
void printMessage(string message);

// 함수 정의
int add(int a, int b) {
    return a + b;
}

void printMessage(string message) {
    cout << message << endl;
}

// 매개변수가 없는 함수
int getNumber() {
    return 42;
}

// 반환값이 없는 함수
void greet(string name) {
    cout << "안녕하세요, " << name << "님!" << endl;
}

// 기본값 매개변수
double calculatePrice(double basePrice, double taxRate = 0.1) {
    return basePrice * (1 + taxRate);
}

int main() {
    // 함수 호출
    cout << "=== 함수 호출 ===" << endl;
    int result = add(5, 3);
    cout << "5 + 3 = " << result << endl;
    
    printMessage("함수 호출 성공!");
    
    // 반환값 사용
    cout << "\n=== 반환값 사용 ===" << endl;
    int num = getNumber();
    cout << "숫자: " << num << endl;
    
    // 여러 함수 호출
    cout << "\n=== 여러 함수 호출 ===" << endl;
    greet("홍길동");
    greet("김철수");
    
    // 기본값 매개변수 사용
    cout << "\n=== 기본값 매개변수 사용 ===" << endl;
    double price1 = calculatePrice(100.0);  // 기본 세율 10% 사용
    double price2 = calculatePrice(100.0, 0.2);  // 세율 20% 지정
    
    cout << "기본 세율: " << price1 << endl;
    cout << "세율 20%: " << price2 << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 최대값 찾기
    int maxVal = max(10, 20);
    cout << "max(10, 20) = " << maxVal << endl;
    
    // 제곱 계산
    auto square = [](int x) { return x * x; };
    cout << "square(5) = " << square(5) << endl;
    
    return 0;
}


