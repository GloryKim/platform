/*
 * 1단계 예제 15: 수학 함수
 * 
 * C++의 수학 함수들을 사용하는 방법을 학습합니다.
 * <cmath> 헤더를 포함해야 합니다.
 */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // 기본 수학 함수
    cout << fixed << setprecision(2);  // 소수점 2자리까지 출력
    
    cout << "=== 기본 수학 함수 ===" << endl;
    
    // 제곱근
    double num = 16.0;
    cout << "sqrt(" << num << ") = " << sqrt(num) << endl;
    
    // 거듭제곱
    double base = 2.0, exponent = 3.0;
    cout << "pow(" << base << ", " << exponent << ") = " 
         << pow(base, exponent) << endl;
    
    // 절댓값
    int neg = -10;
    double negDouble = -3.14;
    cout << "abs(" << neg << ") = " << abs(neg) << endl;
    cout << "fabs(" << negDouble << ") = " << fabs(negDouble) << endl;
    
    // 올림, 내림, 반올림
    double value = 3.7;
    cout << "\n올림, 내림, 반올림:" << endl;
    cout << "ceil(" << value << ") = " << ceil(value) << endl;    // 4
    cout << "floor(" << value << ") = " << floor(value) << endl;  // 3
    cout << "round(" << value << ") = " << round(value) << endl;  // 4
    
    value = 3.2;
    cout << "round(" << value << ") = " << round(value) << endl;  // 3
    
    // 삼각함수 (라디안 단위)
    cout << "\n=== 삼각함수 ===" << endl;
    double angle = M_PI / 4;  // 45도
    cout << "각도: 45도 (π/4 라디안)" << endl;
    cout << "sin(π/4) = " << sin(angle) << endl;
    cout << "cos(π/4) = " << cos(angle) << endl;
    cout << "tan(π/4) = " << tan(angle) << endl;
    
    // 역삼각함수
    double sinValue = sin(angle);
    cout << "\n역삼각함수:" << endl;
    cout << "asin(" << sinValue << ") = " << asin(sinValue) << " 라디안" << endl;
    cout << "acos(" << sinValue << ") = " << acos(sinValue) << " 라디안" << endl;
    cout << "atan(1) = " << atan(1) << " 라디안" << endl;
    
    // 로그 함수
    cout << "\n=== 로그 함수 ===" << endl;
    double logValue = 10.0;
    cout << "log(" << logValue << ") = " << log(logValue) << " (자연로그)" << endl;
    cout << "log10(" << logValue << ") = " << log10(logValue) << " (상용로그)" << endl;
    cout << "log2(" << logValue << ") = " << log2(logValue) << " (밑이 2인 로그)" << endl;
    
    // 지수 함수
    cout << "\n=== 지수 함수 ===" << endl;
    double expValue = 2.0;
    cout << "exp(" << expValue << ") = " << exp(expValue) << " (e^2)" << endl;
    
    // 최대값, 최소값
    cout << "\n=== 최대값, 최소값 ===" << endl;
    int a = 10, b = 20;
    cout << "max(" << a << ", " << b << ") = " << max(a, b) << endl;
    cout << "min(" << a << ", " << b << ") = " << min(a, b) << endl;
    
    // 상수
    cout << "\n=== 수학 상수 ===" << endl;
    cout << "M_PI = " << M_PI << " (π)" << endl;
    cout << "M_E = " << M_E << " (자연상수 e)" << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 원의 넓이 계산
    double radius = 5.0;
    double area = M_PI * pow(radius, 2);
    cout << "반지름 " << radius << "인 원의 넓이: " << area << endl;
    
    // 두 점 사이의 거리
    double x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    cout << "점 (" << x1 << ", " << y1 << ")과 (" << x2 << ", " << y2 
         << ") 사이의 거리: " << distance << endl;
    
    return 0;
}


