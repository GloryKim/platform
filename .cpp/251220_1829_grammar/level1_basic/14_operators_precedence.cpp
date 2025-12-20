/*
 * 1단계 예제 14: 연산자 우선순위
 * 
 * 연산자가 실행되는 순서를 결정하는 우선순위를 학습합니다.
 * 괄호를 사용하여 명확하게 표현하는 것이 좋습니다.
 */

#include <iostream>
using namespace std;

int main() {
    cout << "=== 연산자 우선순위 ===" << endl;
    
    // 산술 연산자 우선순위
    // *, /, % > +, -
    int result1 = 2 + 3 * 4;        // 3*4 먼저, 그 다음 +2 = 14
    int result2 = (2 + 3) * 4;      // 괄호 먼저, 5*4 = 20
    
    cout << "2 + 3 * 4 = " << result1 << endl;
    cout << "(2 + 3) * 4 = " << result2 << endl;
    
    // 비교 연산자와 논리 연산자
    // 비교 연산자 > 논리 연산자
    bool result3 = 5 > 3 && 2 < 4;  // (5>3) && (2<4) = true && true = true
    bool result4 = 5 > 3 || 2 > 4;  // (5>3) || (2>4) = true || false = true
    
    cout << "\n5 > 3 && 2 < 4 = " << result3 << endl;
    cout << "5 > 3 || 2 > 4 = " << result4 << endl;
    
    // 논리 연산자 우선순위: ! > && > ||
    bool result5 = !true || false && true;  // (!true) || (false && true) = false || false = false
    bool result6 = (!true || false) && true;  // (false || false) && true = false && true = false
    
    cout << "\n!true || false && true = " << result5 << endl;
    cout << "(!true || false) && true = " << result6 << endl;
    
    // 대입 연산자와 산술 연산자
    int a = 5;
    a += 3 * 2;                     // 3*2 먼저, 그 다음 +=6, a = 11
    cout << "\na = 5, a += 3 * 2 후: " << a << endl;
    
    // 증감 연산자와 산술 연산자
    int b = 5;
    int c = ++b * 2;                // ++b 먼저 (b=6), 그 다음 *2, c=12
    cout << "b = 5, c = ++b * 2: b=" << b << ", c=" << c << endl;
    
    int d = 5;
    int e = d++ * 2;                // d*2 먼저 (e=10), 그 다음 d++ (d=6)
    cout << "d = 5, e = d++ * 2: d=" << d << ", e=" << e << endl;
    
    // 복잡한 표현식
    int x = 10, y = 5, z = 3;
    int result7 = x + y * z - x / z;  // y*z, x/z 먼저, 그 다음 +, -
    // 계산: 10 + (5*3) - (10/3) = 10 + 15 - 3 = 22
    cout << "\n복잡한 표현식:" << endl;
    cout << "x + y * z - x / z = " << result7 << endl;
    
    // 괄호를 사용한 명확한 표현 (권장)
    int result8 = (x + y) * (z - x) / z;
    cout << "(x + y) * (z - x) / z = " << result8 << endl;
    
    // 조건 연산자 (삼항 연산자)
    int age = 20;
    string status = (age >= 18) ? "성인" : "미성년자";
    cout << "\n조건 연산자:" << endl;
    cout << "나이 " << age << "세: " << status << endl;
    
    // 우선순위 표 (주요 연산자)
    cout << "\n=== 주요 연산자 우선순위 (높은 순서) ===" << endl;
    cout << "1. () [] . ->" << endl;
    cout << "2. ! ~ ++ -- (단항)" << endl;
    cout << "3. * / %" << endl;
    cout << "4. + -" << endl;
    cout << "5. < <= > >=" << endl;
    cout << "6. == !=" << endl;
    cout << "7. &&" << endl;
    cout << "8. ||" << endl;
    cout << "9. ?: (조건 연산자)" << endl;
    cout << "10. = += -= *= /=" << endl;
    
    return 0;
}



