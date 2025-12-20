/*
 * 3단계 예제 2: 함수 매개변수
 * 
 * 값 전달, 참조 전달, 포인터 전달의 차이를 학습합니다.
 * 각 방식의 장단점과 사용 시기를 이해합니다.
 */

#include <iostream>
using namespace std;

// 값 전달 (Pass by Value)
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // 원본 변수는 변경되지 않음
}

// 참조 전달 (Pass by Reference)
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    // 원본 변수가 변경됨
}

// 포인터 전달 (Pass by Pointer)
void swapByPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    // 원본 변수가 변경됨
}

// 값 전달 예제
void incrementByValue(int x) {
    x++;  // 복사본만 증가
}

// 참조 전달 예제
void incrementByReference(int& x) {
    x++;  // 원본 증가
}

// 포인터 전달 예제
void incrementByPointer(int* x) {
    (*x)++;  // 원본 증가
}

// const 참조 전달 (읽기 전용, 복사 비용 절약)
void printValue(const int& x) {
    cout << "값: " << x << endl;
    // x = 10;  // 에러! const이므로 수정 불가
}

int main() {
    // 값 전달 vs 참조 전달
    cout << "=== 값 전달 vs 참조 전달 ===" << endl;
    int a = 10, b = 20;
    
    cout << "교환 전: a=" << a << ", b=" << b << endl;
    swapByValue(a, b);
    cout << "값 전달 후: a=" << a << ", b=" << b << " (변경 안 됨)" << endl;
    
    swapByReference(a, b);
    cout << "참조 전달 후: a=" << a << ", b=" << b << " (변경됨)" << endl;
    
    // 포인터 전달
    cout << "\n=== 포인터 전달 ===" << endl;
    int x = 5, y = 10;
    cout << "교환 전: x=" << x << ", y=" << y << endl;
    swapByPointer(&x, &y);
    cout << "포인터 전달 후: x=" << x << ", y=" << y << " (변경됨)" << endl;
    
    // 증가 연산 비교
    cout << "\n=== 증가 연산 비교 ===" << endl;
    int num1 = 5, num2 = 5, num3 = 5;
    
    incrementByValue(num1);
    cout << "값 전달 후: " << num1 << " (변경 안 됨)" << endl;
    
    incrementByReference(num2);
    cout << "참조 전달 후: " << num2 << " (변경됨)" << endl;
    
    incrementByPointer(&num3);
    cout << "포인터 전달 후: " << num3 << " (변경됨)" << endl;
    
    // const 참조 전달
    cout << "\n=== const 참조 전달 ===" << endl;
    int value = 42;
    printValue(value);
    
    // 배열 전달
    cout << "\n=== 배열 전달 ===" << endl;
    void printArray(int arr[], int size);
    int arr[] = {1, 2, 3, 4, 5};
    printArray(arr, 5);
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 큰 객체는 참조로 전달 (복사 비용 절약)
    struct LargeStruct {
        int data[1000];
    };
    
    void processLargeStruct(const LargeStruct& s);
    LargeStruct ls;
    processLargeStruct(ls);  // 참조로 전달하여 복사 비용 절약
    
    return 0;
}

// 배열 출력 함수
void printArray(int arr[], int size) {
    cout << "배열: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 큰 구조체 처리 함수
void processLargeStruct(const LargeStruct& s) {
    cout << "큰 구조체 처리 완료" << endl;
}


