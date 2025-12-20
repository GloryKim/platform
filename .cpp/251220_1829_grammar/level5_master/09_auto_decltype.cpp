/*
 * 5단계 예제 9: auto와 decltype
 * 
 * auto는 타입 추론을, decltype은 표현식의 타입을 추출합니다.
 * 코드를 간결하고 유연하게 만듭니다.
 */

#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

int main() {
    // auto 사용
    cout << "=== auto 사용 ===" << endl;
    auto x = 42;  // int
    auto y = 3.14;  // double
    auto z = "Hello";  // const char*
    
    cout << "x 타입: " << typeid(x).name() << ", 값: " << x << endl;
    cout << "y 타입: " << typeid(y).name() << ", 값: " << y << endl;
    cout << "z 타입: " << typeid(z).name() << ", 값: " << z << endl;
    
    // auto와 반복자
    cout << "\n=== auto와 반복자 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // auto와 람다
    cout << "\n=== auto와 람다 ===" << endl;
    auto add = [](int a, int b) { return a + b; };
    auto result = add(5, 3);
    cout << "add(5, 3) = " << result << endl;
    
    // decltype 사용
    cout << "\n=== decltype 사용 ===" << endl;
    int a = 10;
    decltype(a) b = 20;  // b는 int 타입
    
    decltype(a + b) sum = a + b;  // sum은 int 타입
    cout << "sum: " << sum << endl;
    
    // decltype과 함수 반환 타입
    auto multiply = [](int x, int y) -> decltype(x * y) {
        return x * y;
    };
    
    cout << "multiply(5, 3) = " << multiply(5, 3) << endl;
    
    // trailing return type
    cout << "\n=== trailing return type ===" << endl;
    auto divide = [](double a, double b) -> decltype(a / b) {
        return a / b;
    };
    
    cout << "divide(10.0, 2.0) = " << divide(10.0, 2.0) << endl;
    
    return 0;
}
