/*
 * 3단계 예제 10: 인라인 함수
 * 
 * 인라인 함수는 함수 호출 오버헤드를 줄이기 위해 컴파일러가 함수 코드를 직접 삽입합니다.
 * 작은 함수의 성능 최적화에 유용합니다.
 */

#include <iostream>
using namespace std;

// 인라인 함수 정의
inline int add(int a, int b) {
    return a + b;
}

inline int square(int x) {
    return x * x;
}

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

inline double calculateArea(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

// 매크로 vs 인라인 함수
#define MACRO_ADD(a, b) ((a) + (b))

inline int inlineAdd(int a, int b) {
    return a + b;
}

int main() {
    // 인라인 함수 사용
    cout << "=== 인라인 함수 사용 ===" << endl;
    int result1 = add(5, 3);
    cout << "add(5, 3) = " << result1 << endl;
    
    int result2 = square(5);
    cout << "square(5) = " << result2 << endl;
    
    int result3 = max(10, 20);
    cout << "max(10, 20) = " << result3 << endl;
    
    double area = calculateArea(5.0);
    cout << "반지름 5인 원의 넓이: " << area << endl;
    
    // 매크로 vs 인라인 함수
    cout << "\n=== 매크로 vs 인라인 함수 ===" << endl;
    int x = 5, y = 3;
    
    int macroResult = MACRO_ADD(x, y);
    int inlineResult = inlineAdd(x, y);
    
    cout << "매크로 결과: " << macroResult << endl;
    cout << "인라인 결과: " << inlineResult << endl;
    
    // 매크로의 문제점 (인라인 함수는 해결)
    cout << "\n=== 매크로의 문제점 ===" << endl;
    int a = 5, b = 3;
    // 매크로는 타입 안전성이 없음
    int macroAdd = MACRO_ADD(a, b);
    // 인라인 함수는 타입 안전
    int inlineAdd = inlineAdd(a, b);
    
    cout << "매크로: " << macroAdd << endl;
    cout << "인라인: " << inlineAdd << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 작은 유틸리티 함수들
    inline int abs(int x) {
        return (x < 0) ? -x : x;
    }
    
    inline bool isEven(int x) {
        return (x % 2 == 0);
    }
    
    cout << "abs(-10) = " << abs(-10) << endl;
    cout << "isEven(10) = " << isEven(10) << endl;
    cout << "isEven(7) = " << isEven(7) << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 인라인은 컴파일러에게 권장사항일 뿐 (무시될 수 있음)" << endl;
    cout << "2. 큰 함수는 인라인하지 않는 것이 좋음" << endl;
    cout << "3. 재귀 함수는 인라인되지 않음" << endl;
    cout << "4. 헤더 파일에 정의해야 함 (링크 오류 방지)" << endl;
    cout << "5. 매크로보다 타입 안전하고 디버깅이 쉬움" << endl;
    
    return 0;
}



