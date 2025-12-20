/*
 * 5단계 예제 13: std::bind
 * 
 * std::bind는 함수의 인수를 바인딩하여 새로운 함수 객체를 만듭니다.
 * 부분 적용과 인수 재배열에 유용합니다.
 */

#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

// 여러 매개변수 함수
int calculate(int a, int b, int c) {
    return a + b * c;
}

void printInfo(string name, int age, string city) {
    cout << "이름: " << name << ", 나이: " << age << ", 도시: " << city << endl;
}

int main() {
    // 인수 바인딩
    cout << "=== 인수 바인딩 ===" << endl;
    auto add10 = bind(calculate, 10, _1, _2);
    cout << "add10(5, 3) = " << add10(5, 3) << endl;
    
    // 인수 재배열
    cout << "\n=== 인수 재배열 ===" << endl;
    auto reversed = bind(printInfo, _3, _2, _1);
    reversed("서울", 25, "홍길동");
    
    // 부분 적용
    cout << "\n=== 부분 적용 ===" << endl;
    auto printWithAge = bind(printInfo, _1, 30, _2);
    printWithAge("김철수", "부산");
    
    // 멤버 함수 바인딩
    cout << "\n=== 멤버 함수 바인딩 ===" << endl;
    class Calculator {
    public:
        int multiply(int a, int b) {
            return a * b;
        }
    };
    
    Calculator calc;
    auto multiply = bind(&Calculator::multiply, &calc, _1, _2);
    cout << "multiply(5, 3) = " << multiply(5, 3) << endl;
    
    return 0;
}


