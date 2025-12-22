/*
 * 5단계 예제 5: 완벽한 전달
 * 
 * 완벽한 전달은 함수에 전달된 인수의 값을 변경하지 않고 전달합니다.
 * rvalue 참조와 보편 참조를 사용합니다.
 */

#include <iostream>
#include <utility>
using namespace std;

// 완벽한 전달을 위한 래퍼 함수
template<typename T>
void wrapper(T&& arg) {
    process(forward<T>(arg));  // 완벽한 전달
}

void process(int& x) {
    cout << "lvalue 참조: " << x << endl;
    x = 100;
}

void process(int&& x) {
    cout << "rvalue 참조: " << x << endl;
}

// 실제 사용 예제
template<typename T, typename... Args>
unique_ptr<T> make_unique_helper(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
}

class MyClass {
private:
    int value;

public:
    MyClass(int v) : value(v) {
        cout << "MyClass 생성: " << value << endl;
    }
};

int main() {
    // lvalue 전달
    cout << "=== lvalue 전달 ===" << endl;
    int x = 42;
    wrapper(x);  // lvalue 참조로 전달
    cout << "x = " << x << endl;
    
    // rvalue 전달
    cout << "\n=== rvalue 전달 ===" << endl;
    wrapper(100);  // rvalue 참조로 전달
    
    // make_unique 예제
    cout << "\n=== make_unique 예제 ===" << endl;
    auto obj = make_unique_helper<MyClass>(42);
    
    return 0;
}



