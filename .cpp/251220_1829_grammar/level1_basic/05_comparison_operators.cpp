/*
 * 1단계 예제 5: 비교 연산자
 * 
 * 두 값을 비교하는 연산자들을 학습합니다.
 * 결과는 항상 true(1) 또는 false(0)입니다.
 */

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 5, c = 10;
    
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl << endl;
    
    // 비교 연산자들
    cout << "a == b: " << (a == b) << endl;    // 같음 (0, false)
    cout << "a != b: " << (a != b) << endl;    // 다름 (1, true)
    cout << "a < b: " << (a < b) << endl;      // 작음 (0, false)
    cout << "a > b: " << (a > b) << endl;      // 큼 (1, true)
    cout << "a <= c: " << (a <= c) << endl;    // 작거나 같음 (1, true)
    cout << "a >= b: " << (a >= b) << endl;    // 크거나 같음 (1, true)
    
    // 문자 비교
    char ch1 = 'A', ch2 = 'B';
    cout << "\n문자 비교:" << endl;
    cout << "'A' < 'B': " << (ch1 < ch2) << endl;  // ASCII 값 비교 (1, true)
    cout << "'A' == 'A': " << (ch1 == 'A') << endl;  // (1, true)
    
    // 실수 비교 (주의: 부동소수점 오차)
    double x = 0.1 + 0.2;
    double y = 0.3;
    cout << "\n실수 비교 (주의):" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    cout << "x == y: " << (x == y) << endl;    // 부동소수점 오차로 인해 0일 수 있음
    cout << "x - y = " << (x - y) << endl;
    
    // 문자열 비교 (string 클래스 사용)
    string str1 = "apple", str2 = "banana", str3 = "apple";
    cout << "\n문자열 비교:" << endl;
    cout << "str1 == str3: " << (str1 == str3) << endl;  // (1, true)
    cout << "str1 < str2: " << (str1 < str2) << endl;    // 사전순 비교 (1, true)
    
    // 논리 연산자와 함께 사용
    int age = 20;
    cout << "\n조건 확인:" << endl;
    cout << "age >= 18 && age < 65: " << (age >= 18 && age < 65) << endl;
    cout << "age < 18 || age >= 65: " << (age < 18 || age >= 65) << endl;
    
    return 0;
}
