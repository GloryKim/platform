/*
 * 5단계 예제 3: 람다 표현식
 * 
 * 람다는 익명 함수 객체입니다.
 * 간결하고 유연한 함수 정의를 가능하게 합니다.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 기본 람다
    cout << "=== 기본 람다 ===" << endl;
    auto add = [](int a, int b) { return a + b; };
    cout << "add(5, 3) = " << add(5, 3) << endl;
    
    // 캡처 없는 람다
    auto square = [](int x) { return x * x; };
    cout << "square(5) = " << square(5) << endl;
    
    // 값 캡처
    cout << "\n=== 값 캡처 ===" << endl;
    int multiplier = 10;
    auto multiply = [multiplier](int x) { return x * multiplier; };
    cout << "multiply(5) = " << multiply(5) << endl;
    
    // 참조 캡처
    cout << "\n=== 참조 캡처 ===" << endl;
    int counter = 0;
    auto increment = [&counter]() { counter++; };
    increment();
    increment();
    cout << "counter: " << counter << endl;
    
    // 모든 변수 캡처
    cout << "\n=== 모든 변수 캡처 ===" << endl;
    int a = 10, b = 20;
    auto sum = [=]() { return a + b; };  // 값으로 모두 캡처
    auto modify = [&]() { a++; b++; };    // 참조로 모두 캡처
    
    cout << "sum(): " << sum() << endl;
    modify();
    cout << "modify 후 a=" << a << ", b=" << b << endl;
    
    // STL 알고리즘과 함께 사용
    cout << "\n=== STL 알고리즘과 함께 사용 ===" << endl;
    vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // 정렬
    sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;  // 역순 정렬
    });
    
    cout << "역순 정렬: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 필터링
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evens),
            [](int x) { return x % 2 == 0; });
    
    cout << "짝수: ";
    for (int num : evens) {
        cout << num << " ";
    }
    cout << endl;
    
    // 변환
    vector<int> doubled;
    transform(numbers.begin(), numbers.end(), back_inserter(doubled),
              [](int x) { return x * 2; });
    
    cout << "2배: ";
    for (int num : doubled) {
        cout << num << " ";
    }
    cout << endl;
    
    // mutable 람다
    cout << "\n=== mutable 람다 ===" << endl;
    int value = 10;
    auto addValue = [value]() mutable {
        value += 5;
        return value;
    };
    
    cout << "addValue(): " << addValue() << endl;
    cout << "원본 value: " << value << endl;  // 변경되지 않음
    
    return 0;
}
