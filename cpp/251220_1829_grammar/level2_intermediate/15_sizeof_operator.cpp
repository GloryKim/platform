/*
 * 2단계 예제 15: sizeof 연산자
 * 
 * sizeof 연산자는 변수나 타입의 크기를 바이트 단위로 반환합니다.
 * 메모리 관리와 배열 크기 계산에 유용합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 타입의 크기
    cout << "=== 기본 타입의 크기 ===" << endl;
    cout << "sizeof(char): " << sizeof(char) << " 바이트" << endl;
    cout << "sizeof(short): " << sizeof(short) << " 바이트" << endl;
    cout << "sizeof(int): " << sizeof(int) << " 바이트" << endl;
    cout << "sizeof(long): " << sizeof(long) << " 바이트" << endl;
    cout << "sizeof(long long): " << sizeof(long long) << " 바이트" << endl;
    cout << "sizeof(float): " << sizeof(float) << " 바이트" << endl;
    cout << "sizeof(double): " << sizeof(double) << " 바이트" << endl;
    cout << "sizeof(long double): " << sizeof(long double) << " 바이트" << endl;
    cout << "sizeof(bool): " << sizeof(bool) << " 바이트" << endl;
    
    // 변수의 크기
    cout << "\n=== 변수의 크기 ===" << endl;
    int num = 10;
    double price = 99.99;
    char ch = 'A';
    
    cout << "sizeof(num): " << sizeof(num) << " 바이트" << endl;
    cout << "sizeof(price): " << sizeof(price) << " 바이트" << endl;
    cout << "sizeof(ch): " << sizeof(ch) << " 바이트" << endl;
    
    // 배열의 크기
    cout << "\n=== 배열의 크기 ===" << endl;
    int arr[10];
    double prices[5];
    char str[20];
    
    cout << "sizeof(arr): " << sizeof(arr) << " 바이트" << endl;
    cout << "sizeof(arr[0]): " << sizeof(arr[0]) << " 바이트" << endl;
    cout << "배열 요소 개수: " << sizeof(arr) / sizeof(arr[0]) << endl;
    
    cout << "sizeof(prices): " << sizeof(prices) << " 바이트" << endl;
    cout << "배열 요소 개수: " << sizeof(prices) / sizeof(prices[0]) << endl;
    
    cout << "sizeof(str): " << sizeof(str) << " 바이트" << endl;
    
    // 2차원 배열의 크기
    cout << "\n=== 2차원 배열의 크기 ===" << endl;
    int matrix[3][4];
    
    cout << "sizeof(matrix): " << sizeof(matrix) << " 바이트" << endl;
    cout << "sizeof(matrix[0]): " << sizeof(matrix[0]) << " 바이트" << endl;
    cout << "sizeof(matrix[0][0]): " << sizeof(matrix[0][0]) << " 바이트" << endl;
    cout << "행 개수: " << sizeof(matrix) / sizeof(matrix[0]) << endl;
    cout << "열 개수: " << sizeof(matrix[0]) / sizeof(matrix[0][0]) << endl;
    
    // 포인터의 크기
    cout << "\n=== 포인터의 크기 ===" << endl;
    int* ptr;
    double* dptr;
    char* cptr;
    
    cout << "sizeof(ptr): " << sizeof(ptr) << " 바이트" << endl;
    cout << "sizeof(dptr): " << sizeof(dptr) << " 바이트" << endl;
    cout << "sizeof(cptr): " << sizeof(cptr) << " 바이트" << endl;
    cout << "포인터 크기는 시스템에 따라 다름 (보통 4 또는 8 바이트)" << endl;
    
    // 구조체의 크기
    cout << "\n=== 구조체의 크기 ===" << endl;
    struct Point {
        int x;
        int y;
    };
    
    struct Student {
        char name[20];
        int age;
        double score;
    };
    
    cout << "sizeof(Point): " << sizeof(Point) << " 바이트" << endl;
    cout << "sizeof(Student): " << sizeof(Student) << " 바이트" << endl;
    
    Point p;
    cout << "sizeof(p): " << sizeof(p) << " 바이트" << endl;
    
    // 실제 사용 예제 1: 배열 크기 계산
    cout << "\n=== 실제 사용 예제 1: 배열 크기 계산 ===" << endl;
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    cout << "배열 크기: " << size << endl;
    
    // 실제 사용 예제 2: 메모리 할당 확인
    cout << "\n=== 실제 사용 예제 2: 메모리 할당 확인 ===" << endl;
    int largeArray[1000];
    cout << "largeArray 크기: " << sizeof(largeArray) << " 바이트" << endl;
    cout << "largeArray 크기: " << sizeof(largeArray) / 1024.0 << " KB" << endl;
    
    // 실제 사용 예제 3: 타입 안전성
    cout << "\n=== 실제 사용 예제 3: 타입 안전성 ===" << endl;
    int arr1[10];
    int arr2[20];
    
    if (sizeof(arr1) != sizeof(arr2)) {
        cout << "배열 크기가 다릅니다." << endl;
        cout << "arr1: " << sizeof(arr1) / sizeof(arr1[0]) << "개 요소" << endl;
        cout << "arr2: " << sizeof(arr2) / sizeof(arr2[0]) << "개 요소" << endl;
    }
    
    // 실제 사용 예제 4: 동적 메모리와의 차이
    cout << "\n=== 실제 사용 예제 4: 동적 메모리와의 차이 ===" << endl;
    int staticArray[10];
    int* dynamicArray = new int[10];
    
    cout << "정적 배열 크기: " << sizeof(staticArray) << " 바이트" << endl;
    cout << "동적 배열 포인터 크기: " << sizeof(dynamicArray) << " 바이트" << endl;
    cout << "주의: 동적 배열의 실제 크기는 sizeof로 알 수 없음" << endl;
    
    delete[] dynamicArray;
    
    // 실제 사용 예제 5: 구조체 패딩
    cout << "\n=== 실제 사용 예제 5: 구조체 패딩 ===" << endl;
    struct Packed {
        char a;   // 1 바이트
        int b;     // 4 바이트
        char c;    // 1 바이트
    };
    
    struct Optimized {
        int b;     // 4 바이트
        char a;    // 1 바이트
        char c;    // 1 바이트
    };
    
    cout << "sizeof(Packed): " << sizeof(Packed) << " 바이트" << endl;
    cout << "sizeof(Optimized): " << sizeof(Optimized) << " 바이트" << endl;
    cout << "메모리 정렬 때문에 크기가 다를 수 있음" << endl;
    
    return 0;
}



