/*
 * 5단계 예제 12: std::function
 * 
 * std::function은 모든 호출 가능한 객체를 저장할 수 있습니다.
 * 함수 포인터, 람다, 함수 객체를 통일된 방식으로 다룹니다.
 */

#include <iostream>
#include <functional>
#include <vector>
using namespace std;

// 일반 함수
int add(int a, int b) {
    return a + b;
}

// 함수 객체
class Multiply {
public:
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    // 함수 포인터 저장
    cout << "=== 함수 포인터 저장 ===" << endl;
    function<int(int, int)> func1 = add;
    cout << "func1(5, 3) = " << func1(5, 3) << endl;
    
    // 람다 저장
    cout << "\n=== 람다 저장 ===" << endl;
    function<int(int, int)> func2 = [](int a, int b) { return a - b; };
    cout << "func2(5, 3) = " << func2(5, 3) << endl;
    
    // 함수 객체 저장
    cout << "\n=== 함수 객체 저장 ===" << endl;
    function<int(int, int)> func3 = Multiply();
    cout << "func3(5, 3) = " << func3(5, 3) << endl;
    
    // 함수 컨테이너
    cout << "\n=== 함수 컨테이너 ===" << endl;
    vector<function<int(int, int)>> operations = {
        add,
        [](int a, int b) { return a * b; },
        Multiply()
    };
    
    int a = 10, b = 5;
    for (size_t i = 0; i < operations.size(); i++) {
        cout << "연산 " << i << ": " << operations[i](a, b) << endl;
    }
    
    // 콜백 함수
    cout << "\n=== 콜백 함수 ===" << endl;
    function<void(int)> callback = [](int value) {
        cout << "콜백 호출: " << value << endl;
    };
    
    callback(42);
    callback(100);
    
    return 0;
}
