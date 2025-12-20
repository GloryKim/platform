/*
 * 5단계 예제 6: 가변 인자 템플릿
 * 
 * 가변 인자 템플릿은 임의의 개수의 인수를 받을 수 있습니다.
 * 재귀와 패킷 확장을 사용합니다.
 */

#include <iostream>
using namespace std;

// 기본 경우
void print() {
    cout << endl;
}

// 가변 인자 템플릿
template<typename T, typename... Args>
void print(T first, Args... args) {
    cout << first << " ";
    print(args...);  // 재귀 호출
}

// 합계 계산
template<typename T>
T sum(T value) {
    return value;
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

// 최대값 찾기
template<typename T>
T maximum(T value) {
    return value;
}

template<typename T, typename... Args>
T maximum(T first, Args... args) {
    T rest = maximum(args...);
    return (first > rest) ? first : rest;
}

int main() {
    // 가변 인자 출력
    cout << "=== 가변 인자 출력 ===" << endl;
    print(1, 2, 3, 4, 5);
    print("Hello", "World", 42, 3.14);
    
    // 합계 계산
    cout << "\n=== 합계 계산 ===" << endl;
    cout << "sum(1, 2, 3, 4, 5) = " << sum(1, 2, 3, 4, 5) << endl;
    cout << "sum(10.5, 20.3, 30.2) = " << sum(10.5, 20.3, 30.2) << endl;
    
    // 최대값 찾기
    cout << "\n=== 최대값 찾기 ===" << endl;
    cout << "maximum(5, 2, 8, 1, 9) = " << maximum(5, 2, 8, 1, 9) << endl;
    cout << "maximum(3.14, 2.71, 1.41) = " << maximum(3.14, 2.71, 1.41) << endl;
    
    return 0;
}


