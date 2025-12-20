/*
 * 5단계 예제 17: optional
 * 
 * optional은 값이 있을 수도 있고 없을 수도 있는 타입입니다.
 * null 포인터 대신 안전한 방법을 제공합니다.
 */

#include <iostream>
#include <optional>
#include <string>
using namespace std;

optional<int> divide(int a, int b) {
    if (b != 0) {
        return a / b;
    }
    return nullopt;  // 값 없음
}

optional<string> findName(int id) {
    if (id == 1) return "Alice";
    if (id == 2) return "Bob";
    return nullopt;
}

int main() {
    // optional 기본 사용
    cout << "=== optional 기본 사용 ===" << endl;
    optional<int> value1 = 42;
    optional<int> value2 = nullopt;
    
    if (value1.has_value()) {
        cout << "value1: " << value1.value() << endl;
    }
    
    if (value2.has_value()) {
        cout << "value2: " << value2.value() << endl;
    } else {
        cout << "value2는 값이 없습니다." << endl;
    }
    
    // 함수 반환값
    cout << "\n=== 함수 반환값 ===" << endl;
    auto result1 = divide(10, 2);
    if (result1) {
        cout << "10 / 2 = " << *result1 << endl;
    }
    
    auto result2 = divide(10, 0);
    if (!result2) {
        cout << "0으로 나눌 수 없습니다." << endl;
    }
    
    // 값 접근
    cout << "\n=== 값 접근 ===" << endl;
    optional<string> name = findName(1);
    if (name) {
        cout << "이름: " << name.value() << endl;
        cout << "또는: " << *name << endl;
    }
    
    // 기본값 제공
    cout << "\n=== 기본값 제공 ===" << endl;
    optional<int> opt = nullopt;
    int value = opt.value_or(0);
    cout << "값: " << value << endl;
    
    return 0;
}
