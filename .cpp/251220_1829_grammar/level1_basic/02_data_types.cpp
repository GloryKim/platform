/*
 * 1단계 예제 2: 기본 자료형
 * 
 * C++의 기본 자료형들을 학습합니다.
 * 각 자료형은 저장할 수 있는 데이터의 종류와 크기가 다릅니다.
 */

#include <iostream>
#include <limits>
using namespace std;

int main() {
    // 정수형
    char c = 'A';                    // 문자형 (1바이트, -128 ~ 127)
    short s = 32767;                 // 짧은 정수 (2바이트)
    int i = 2147483647;              // 정수 (4바이트, 가장 많이 사용)
    long l = 2147483647L;            // 긴 정수 (4바이트 이상)
    long long ll = 9223372036854775807LL;  // 매우 긴 정수 (8바이트)
    
    // 부호 없는 정수형
    unsigned int ui = 4294967295U;   // 부호 없는 정수 (0 이상)
    unsigned char uc = 255;          // 부호 없는 문자
    
    // 실수형
    float f = 3.14f;                 // 단정밀도 실수 (4바이트)
    double d = 3.141592653589793;    // 배정밀도 실수 (8바이트, 가장 많이 사용)
    long double ld = 3.141592653589793238L;  // 확장 정밀도 실수
    
    // 불리언형
    bool b1 = true;                  // 참
    bool b2 = false;                 // 거짓
    
    // 출력
    cout << "문자: " << c << endl;
    cout << "정수: " << i << endl;
    cout << "실수: " << d << endl;
    cout << "불리언: " << b1 << " " << b2 << endl;
    
    // sizeof 연산자로 크기 확인
    cout << "\n자료형 크기:" << endl;
    cout << "char: " << sizeof(char) << " 바이트" << endl;
    cout << "int: " << sizeof(int) << " 바이트" << endl;
    cout << "double: " << sizeof(double) << " 바이트" << endl;
    
    return 0;
}
