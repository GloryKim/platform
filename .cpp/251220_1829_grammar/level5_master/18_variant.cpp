/*
 * 5단계 예제 18: variant
 * 
 * variant는 타입 안전한 공용체입니다.
 * 여러 타입 중 하나를 저장할 수 있습니다.
 */

#include <iostream>
#include <variant>
#include <string>
using namespace std;

int main() {
    // variant 선언
    cout << "=== variant 선언 ===" << endl;
    variant<int, double, string> v;
    
    v = 42;
    cout << "int 값: " << get<int>(v) << endl;
    
    v = 3.14;
    cout << "double 값: " << get<double>(v) << endl;
    
    v = "Hello";
    cout << "string 값: " << get<string>(v) << endl;
    
    // 현재 타입 확인
    cout << "\n=== 현재 타입 확인 ===" << endl;
    if (holds_alternative<int>(v)) {
        cout << "int 타입: " << get<int>(v) << endl;
    } else if (holds_alternative<double>(v)) {
        cout << "double 타입: " << get<double>(v) << endl;
    } else if (holds_alternative<string>(v)) {
        cout << "string 타입: " << get<string>(v) << endl;
    }
    
    // visit 사용
    cout << "\n=== visit 사용 ===" << endl;
    variant<int, string> data = "Hello";
    
    visit([](auto& value) {
        cout << "값: " << value << endl;
    }, data);
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    variant<int, string, double> value = 42;
    
    auto printer = [](auto& val) {
        using T = decay_t<decltype(val)>;
        if constexpr (is_same_v<T, int>) {
            cout << "정수: " << val << endl;
        } else if constexpr (is_same_v<T, string>) {
            cout << "문자열: " << val << endl;
        } else if constexpr (is_same_v<T, double>) {
            cout << "실수: " << val << endl;
        }
    };
    
    visit(printer, value);
    
    return 0;
}
