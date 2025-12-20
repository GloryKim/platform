/*
 * 5단계 예제 19: Concepts (C++20)
 * 
 * Concepts는 템플릿 매개변수에 대한 제약 조건을 정의합니다.
 * 더 나은 에러 메시지와 타입 안전성을 제공합니다.
 */

#include <iostream>
#include <concepts>
using namespace std;

// 기본 concept
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> same_as<T>;
};

// concept 사용
template<Addable T>
T add(T a, T b) {
    return a + b;
}

// 여러 제약 조건
template<typename T>
concept Numeric = integral<T> || floating_point<T>;

template<Numeric T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    // Addable concept 사용
    cout << "=== Addable concept ===" << endl;
    cout << "add(5, 3) = " << add(5, 3) << endl;
    cout << "add(3.14, 2.71) = " << add(3.14, 2.71) << endl;
    
    // Numeric concept 사용
    cout << "\n=== Numeric concept ===" << endl;
    cout << "multiply(5, 3) = " << multiply(5, 3) << endl;
    cout << "multiply(3.14, 2.0) = " << multiply(3.14, 2.0) << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. C++20 기능" << endl;
    cout << "2. 컴파일러 지원 필요" << endl;
    cout << "3. 더 나은 에러 메시지" << endl;
    cout << "4. 템플릿 제약 명확화" << endl;
    
    return 0;
}
