/*
 * 1단계 예제 4: 산술 연산자
 * 
 * C++의 기본 산술 연산자들을 학습합니다.
 * +, -, *, /, % (나머지)
 */

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;
    
    // 기본 산술 연산
    cout << "a = " << a << ", b = " << b << endl << endl;
    
    cout << "덧셈: a + b = " << (a + b) << endl;      // 13
    cout << "뺄셈: a - b = " << (a - b) << endl;      // 7
    cout << "곱셈: a * b = " << (a * b) << endl;      // 30
    cout << "나눗셈: a / b = " << (a / b) << endl;    // 3 (정수 나눗셈)
    cout << "나머지: a % b = " << (a % b) << endl;    // 1
    
    // 실수 나눗셈
    double x = 10.0, y = 3.0;
    cout << "\n실수 나눗셈: x / y = " << (x / y) << endl;  // 3.33333...
    
    // 복합 할당 연산자
    int num = 5;
    cout << "\n초기값: num = " << num << endl;
    
    num += 3;  // num = num + 3
    cout << "num += 3: " << num << endl;
    
    num -= 2;  // num = num - 2
    cout << "num -= 2: " << num << endl;
    
    num *= 2;  // num = num * 2
    cout << "num *= 2: " << num << endl;
    
    num /= 3;  // num = num / 3
    cout << "num /= 3: " << num << endl;
    
    num %= 2;  // num = num % 2
    cout << "num %= 2: " << num << endl;
    
    // 증감 연산자
    int count = 5;
    cout << "\n증감 연산자:" << endl;
    cout << "count = " << count << endl;
    cout << "++count = " << ++count << endl;    // 전위 증가 (6)
    cout << "count++ = " << count++ << endl;    // 후위 증가 (6 출력 후 7)
    cout << "count = " << count << endl;        // 7
    cout << "--count = " << --count << endl;    // 전위 감소 (6)
    cout << "count-- = " << count-- << endl;    // 후위 감소 (6 출력 후 5)
    cout << "count = " << count << endl;        // 5
    
    return 0;
}



