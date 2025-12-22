/*
 * 5단계 예제 8: 타입 특성
 * 
 * 타입 특성은 컴파일 타임에 타입의 속성을 조사하고 수정합니다.
 * 템플릿 메타프로그래밍에 유용합니다.
 */

#include <iostream>
#include <type_traits>
using namespace std;

// 타입 특성 사용
template<typename T>
void checkType() {
    cout << "is_integral: " << is_integral<T>::value << endl;
    cout << "is_floating_point: " << is_floating_point<T>::value << endl;
    cout << "is_pointer: " << is_pointer<T>::value << endl;
    cout << "is_reference: " << is_reference<T>::value << endl;
}

// 조건부 컴파일
template<typename T>
void process(T value) {
    if constexpr (is_integral<T>::value) {
        cout << "정수 타입: " << value << endl;
    } else if constexpr (is_floating_point<T>::value) {
        cout << "실수 타입: " << value << endl;
    } else {
        cout << "기타 타입: " << value << endl;
    }
}

// 타입 변환
template<typename T>
void removeReference() {
    using Type = typename remove_reference<T>::type;
    cout << "원본: " << typeid(T).name() << endl;
    cout << "참조 제거: " << typeid(Type).name() << endl;
}

int main() {
    // 타입 특성 확인
    cout << "=== 타입 특성 확인 ===" << endl;
    cout << "int:" << endl;
    checkType<int>();
    
    cout << "\ndouble:" << endl;
    checkType<double>();
    
    // 조건부 처리
    cout << "\n=== 조건부 처리 ===" << endl;
    process(42);
    process(3.14);
    process("Hello");
    
    // 타입 변환
    cout << "\n=== 타입 변환 ===" << endl;
    removeReference<int&>();
    removeReference<int&&>();
    
    return 0;
}



