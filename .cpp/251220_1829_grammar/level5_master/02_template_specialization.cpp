/*
 * 5단계 예제 2: 템플릿 특수화
 * 
 * 템플릿 특수화는 특정 타입에 대해 다른 구현을 제공합니다.
 * 특수한 경우를 처리할 때 유용합니다.
 */

#include <iostream>
#include <cstring>
using namespace std;

// 기본 템플릿
template<typename T>
bool isEqual(T a, T b) {
    return a == b;
}

// 포인터 특수화
template<typename T>
bool isEqual(T* a, T* b) {
    return *a == *b;
}

// 완전 특수화 (const char*)
template<>
bool isEqual<const char*>(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

// 클래스 템플릿 특수화
template<typename T>
class TypeInfo {
public:
    static string getName() {
        return "Unknown";
    }
};

// int 특수화
template<>
class TypeInfo<int> {
public:
    static string getName() {
        return "int";
    }
};

// double 특수화
template<>
class TypeInfo<double> {
public:
    static string getName() {
        return "double";
    }
};

int main() {
    // 기본 템플릿 사용
    cout << "=== 기본 템플릿 사용 ===" << endl;
    cout << "isEqual(5, 5): " << isEqual(5, 5) << endl;
    cout << "isEqual(5, 3): " << isEqual(5, 3) << endl;
    
    // 포인터 특수화
    cout << "\n=== 포인터 특수화 ===" << endl;
    int a = 10, b = 10;
    cout << "isEqual(&a, &b): " << isEqual(&a, &b) << endl;
    
    // 문자열 특수화
    cout << "\n=== 문자열 특수화 ===" << endl;
    const char* str1 = "Hello";
    const char* str2 = "Hello";
    cout << "isEqual(str1, str2): " << isEqual(str1, str2) << endl;
    
    // 클래스 특수화
    cout << "\n=== 클래스 특수화 ===" << endl;
    cout << "TypeInfo<int>::getName(): " << TypeInfo<int>::getName() << endl;
    cout << "TypeInfo<double>::getName(): " << TypeInfo<double>::getName() << endl;
    cout << "TypeInfo<string>::getName(): " << TypeInfo<string>::getName() << endl;
    
    return 0;
}
