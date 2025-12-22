/*
 * 3단계 예제 9: 함수 포인터
 * 
 * 함수를 가리키는 포인터를 학습합니다.
 * 콜백 함수나 함수 테이블 구현에 유용합니다.
 */

#include <iostream>
using namespace std;

// 함수들
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

void greet(string name) {
    cout << "안녕하세요, " << name << "님!" << endl;
}

int main() {
    // 함수 포인터 선언
    cout << "=== 함수 포인터 선언 ===" << endl;
    int (*funcPtr)(int, int);  // 두 개의 int를 받고 int를 반환하는 함수 포인터
    
    // 함수 포인터에 함수 할당
    funcPtr = add;
    cout << "add(5, 3) = " << funcPtr(5, 3) << endl;
    
    funcPtr = multiply;
    cout << "multiply(5, 3) = " << funcPtr(5, 3) << endl;
    
    funcPtr = subtract;
    cout << "subtract(5, 3) = " << funcPtr(5, 3) << endl;
    
    // 함수 포인터 배열
    cout << "\n=== 함수 포인터 배열 ===" << endl;
    int (*operations[])(int, int) = {add, subtract, multiply};
    char opNames[] = {'+', '-', '*'};
    
    int a = 10, b = 5;
    for (int i = 0; i < 3; i++) {
        cout << a << " " << opNames[i] << " " << b 
             << " = " << operations[i](a, b) << endl;
    }
    
    // 함수 포인터를 매개변수로 전달
    cout << "\n=== 함수 포인터를 매개변수로 전달 ===" << endl;
    int calculate(int a, int b, int (*op)(int, int));
    
    cout << "calculate(10, 5, add): " << calculate(10, 5, add) << endl;
    cout << "calculate(10, 5, multiply): " << calculate(10, 5, multiply) << endl;
    
    // 함수 포인터를 반환
    cout << "\n=== 함수 포인터를 반환 ===" << endl;
    int (*getOperation(char op))(int, int);
    
    int (*op1)(int, int) = getOperation('+');
    cout << "10 + 5 = " << op1(10, 5) << endl;
    
    // 실제 사용 예제: 계산기
    cout << "\n=== 실제 사용 예제: 계산기 ===" << endl;
    char operation = '+';
    int num1 = 10, num2 = 5;
    int (*calcFunc)(int, int) = nullptr;
    
    switch (operation) {
        case '+':
            calcFunc = add;
            break;
        case '-':
            calcFunc = subtract;
            break;
        case '*':
            calcFunc = multiply;
            break;
    }
    
    if (calcFunc != nullptr) {
        cout << num1 << " " << operation << " " << num2 
             << " = " << calcFunc(num1, num2) << endl;
    }
    
    // typedef 사용 (가독성 향상)
    cout << "\n=== typedef 사용 ===" << endl;
    typedef int (*MathFunc)(int, int);
    MathFunc func1 = add;
    MathFunc func2 = multiply;
    
    cout << "func1(5, 3) = " << func1(5, 3) << endl;
    cout << "func2(5, 3) = " << func2(5, 3) << endl;
    
    return 0;
}

// 함수 포인터를 매개변수로 받는 함수
int calculate(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}

// 함수 포인터를 반환하는 함수
int (*getOperation(char op))(int, int) {
    switch (op) {
        case '+':
            return add;
        case '-':
            return subtract;
        case '*':
            return multiply;
        default:
            return nullptr;
    }
}



