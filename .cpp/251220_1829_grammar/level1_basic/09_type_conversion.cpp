/*
 * 1단계 예제 9: 타입 변환 (Type Conversion)
 * 
 * 한 자료형을 다른 자료형으로 변환하는 방법을 학습합니다.
 * 암시적 변환과 명시적 변환이 있습니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 암시적 타입 변환 (자동 변환)
    cout << "=== 암시적 타입 변환 ===" << endl;
    
    int a = 10;
    double b = a;                   // int -> double (자동 변환)
    cout << "int a = " << a << " -> double b = " << b << endl;
    
    double x = 3.14;
    int y = x;                      // double -> int (소수점 버림)
    cout << "double x = " << x << " -> int y = " << y << endl;
    
    char ch = 'A';
    int ascii = ch;                 // char -> int (ASCII 값)
    cout << "char '" << ch << "' -> int " << ascii << endl;
    
    // 산술 연산에서의 자동 변환
    int num1 = 5;
    double num2 = 2.5;
    double result = num1 + num2;     // int가 double로 변환됨
    cout << "int + double = " << result << endl;
    
    // 명시적 타입 변환 (C 스타일 캐스팅)
    cout << "\n=== 명시적 타입 변환 (C 스타일) ===" << endl;
    
    double pi = 3.14159;
    int intPi = (int)pi;            // C 스타일 캐스팅
    cout << "double " << pi << " -> int " << intPi << endl;
    
    int value = 65;
    char character = (char)value;   // int -> char
    cout << "int " << value << " -> char '" << character << "'" << endl;
    
    // C++ 스타일 캐스팅
    cout << "\n=== C++ 스타일 캐스팅 ===" << endl;
    
    double d = 9.99;
    int i1 = static_cast<int>(d);   // static_cast (권장)
    cout << "static_cast<int>(" << d << ") = " << i1 << endl;
    
    // const_cast, dynamic_cast, reinterpret_cast는 고급 주제
    
    // 문자열과 숫자 간 변환
    cout << "\n=== 문자열 <-> 숫자 변환 ===" << endl;
    
    // 문자열 -> 숫자
    string str1 = "123";
    int num = stoi(str1);           // string to int
    cout << "stoi(\"" << str1 << "\") = " << num << endl;
    
    string str2 = "3.14";
    double dbl = stod(str2);        // string to double
    cout << "stod(\"" << str2 << "\") = " << dbl << endl;
    
    // 숫자 -> 문자열
    int val = 456;
    string str3 = to_string(val);   // int to string
    cout << "to_string(" << val << ") = \"" << str3 << "\"" << endl;
    
    double price = 99.99;
    string str4 = to_string(price);
    cout << "to_string(" << price << ") = \"" << str4 << "\"" << endl;
    
    // 나눗셈 주의사항
    cout << "\n=== 나눗셈 타입 변환 주의 ===" << endl;
    int x1 = 10, y1 = 3;
    cout << "10 / 3 = " << (x1 / y1) << " (정수 나눗셈)" << endl;
    cout << "10.0 / 3 = " << (10.0 / 3) << " (실수 나눗셈)" << endl;
    cout << "(double)10 / 3 = " << ((double)10 / 3) << " (명시적 변환)" << endl;
    
    return 0;
}
