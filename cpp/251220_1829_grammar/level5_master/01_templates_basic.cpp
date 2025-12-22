/*
 * 5단계 예제 1: 템플릿 기본
 * 
 * 템플릿은 타입에 독립적인 코드를 작성할 수 있게 합니다.
 * 제네릭 프로그래밍의 핵심입니다.
 */

#include <iostream>
using namespace std;

// 함수 템플릿
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// 여러 타입 매개변수
template<typename T, typename U>
void printPair(T first, U second) {
    cout << "(" << first << ", " << second << ")" << endl;
}

// 클래스 템플릿
template<typename T>
class Stack {
private:
    T* data;
    int top;
    int capacity;

public:
    Stack(int size = 10) : capacity(size), top(-1) {
        data = new T[capacity];
    }
    
    ~Stack() {
        delete[] data;
    }
    
    void push(T value) {
        if (top < capacity - 1) {
            data[++top] = value;
        }
    }
    
    T pop() {
        if (top >= 0) {
            return data[top--];
        }
        return T();
    }
    
    bool empty() const {
        return top == -1;
    }
};

int main() {
    // 함수 템플릿 사용
    cout << "=== 함수 템플릿 사용 ===" << endl;
    cout << "maximum(5, 3) = " << maximum(5, 3) << endl;
    cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << endl;
    cout << "maximum('a', 'z') = " << maximum('a', 'z') << endl;
    
    printPair(10, "Hello");
    printPair(3.14, 42);
    
    // 클래스 템플릿 사용
    cout << "\n=== 클래스 템플릿 사용 ===" << endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    while (!intStack.empty()) {
        cout << intStack.pop() << " ";
    }
    cout << endl;
    
    Stack<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    
    while (!stringStack.empty()) {
        cout << stringStack.pop() << " ";
    }
    cout << endl;
    
    return 0;
}



