/*
 * 5단계 예제 20: 메타프로그래밍
 * 
 * 템플릿 메타프로그래밍은 컴파일 타임에 계산을 수행합니다.
 * 복잡하지만 강력한 기능입니다.
 */

#include <iostream>
using namespace std;

// 컴파일 타임 팩토리얼
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

// 컴파일 타임 피보나치
template<int N>
struct Fibonacci {
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static const int value = 0;
};

template<>
struct Fibonacci<1> {
    static const int value = 1;
};

// 타입 리스트
template<typename... Types>
struct TypeList {};

// 타입 검사
template<typename T, typename U>
struct IsSame {
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T> {
    static const bool value = true;
};

int main() {
    // 컴파일 타임 팩토리얼
    cout << "=== 컴파일 타임 팩토리얼 ===" << endl;
    cout << "5! = " << Factorial<5>::value << endl;
    cout << "10! = " << Factorial<10>::value << endl;
    
    // 컴파일 타임 피보나치
    cout << "\n=== 컴파일 타임 피보나치 ===" << endl;
    cout << "fib(10) = " << Fibonacci<10>::value << endl;
    cout << "fib(20) = " << Fibonacci<20>::value << endl;
    
    // 타입 검사
    cout << "\n=== 타입 검사 ===" << endl;
    cout << "IsSame<int, int>::value = " << IsSame<int, int>::value << endl;
    cout << "IsSame<int, double>::value = " << IsSame<int, double>::value << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 컴파일 타임에 계산" << endl;
    cout << "2. 복잡한 템플릿 문법" << endl;
    cout << "3. 컴파일 시간 증가 가능" << endl;
    cout << "4. constexpr로 대체 가능한 경우 많음" << endl;
    
    return 0;
}


