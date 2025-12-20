/*
 * 3단계 예제 3: 함수 오버로딩
 * 
 * 같은 이름의 함수를 여러 개 정의하는 함수 오버로딩을 학습합니다.
 * 매개변수의 타입이나 개수가 달라야 합니다.
 */

#include <iostream>
using namespace std;

// 정수 덧셈
int add(int a, int b) {
    return a + b;
}

// 실수 덧셈
double add(double a, double b) {
    return a + b;
}

// 세 개의 정수 덧셈
int add(int a, int b, int c) {
    return a + b + c;
}

// 정수 배열 합계
int add(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 문자열 연결
string add(string a, string b) {
    return a + b;
}

// 제곱 계산 (정수)
int square(int x) {
    return x * x;
}

// 제곱 계산 (실수)
double square(double x) {
    return x * x;
}

// 출력 함수 오버로딩
void print(int value) {
    cout << "정수: " << value << endl;
}

void print(double value) {
    cout << "실수: " << value << endl;
}

void print(string value) {
    cout << "문자열: " << value << endl;
}

void print(int arr[], int size) {
    cout << "배열: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // 정수 덧셈
    cout << "=== 정수 덧셈 ===" << endl;
    cout << "add(5, 3) = " << add(5, 3) << endl;
    
    // 실수 덧셈
    cout << "\n=== 실수 덧셈 ===" << endl;
    cout << "add(3.14, 2.86) = " << add(3.14, 2.86) << endl;
    
    // 세 개의 정수 덧셈
    cout << "\n=== 세 개의 정수 덧셈 ===" << endl;
    cout << "add(1, 2, 3) = " << add(1, 2, 3) << endl;
    
    // 배열 합계
    cout << "\n=== 배열 합계 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    cout << "배열 합계: " << add(arr, 5) << endl;
    
    // 문자열 연결
    cout << "\n=== 문자열 연결 ===" << endl;
    string result = add("Hello", " World");
    cout << "문자열 연결: " << result << endl;
    
    // 제곱 계산
    cout << "\n=== 제곱 계산 ===" << endl;
    cout << "square(5) = " << square(5) << endl;
    cout << "square(3.14) = " << square(3.14) << endl;
    
    // 출력 함수 오버로딩
    cout << "\n=== 출력 함수 오버로딩 ===" << endl;
    print(42);
    print(3.14);
    print("Hello");
    
    int numbers[] = {1, 2, 3, 4, 5};
    print(numbers, 5);
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 최대값 찾기
    int max(int a, int b);
    double max(double a, double b);
    
    cout << "max(10, 20) = " << max(10, 20) << endl;
    cout << "max(3.14, 2.71) = " << max(3.14, 2.71) << endl;
    
    return 0;
}

// 최대값 함수 오버로딩
int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}
