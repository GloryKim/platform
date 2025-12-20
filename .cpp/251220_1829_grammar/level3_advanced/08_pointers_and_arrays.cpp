/*
 * 3단계 예제 8: 포인터와 배열
 * 
 * 배열과 포인터의 관계를 학습합니다.
 * 배열 이름은 첫 번째 요소의 주소입니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 배열 이름은 포인터
    cout << "=== 배열 이름은 포인터 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    
    cout << "arr: " << arr << " (배열의 시작 주소)" << endl;
    cout << "&arr[0]: " << &arr[0] << " (첫 번째 요소 주소)" << endl;
    cout << "arr == &arr[0]: " << (arr == &arr[0]) << endl;
    
    // 배열 요소 접근 방법
    cout << "\n=== 배열 요소 접근 방법 ===" << endl;
    cout << "arr[2]: " << arr[2] << endl;
    cout << "*(arr + 2): " << *(arr + 2) << endl;
    cout << "2[arr]: " << 2[arr] << endl;  // 흔하지 않지만 가능
    
    // 포인터를 배열처럼 사용
    cout << "\n=== 포인터를 배열처럼 사용 ===" << endl;
    int* ptr = arr;
    cout << "ptr[0]: " << ptr[0] << endl;
    cout << "ptr[1]: " << ptr[1] << endl;
    cout << "*(ptr + 1): " << *(ptr + 1) << endl;
    
    // 포인터 산술 연산
    cout << "\n=== 포인터 산술 연산 ===" << endl;
    int* p = arr;
    cout << "*p: " << *p << endl;
    p++;  // 다음 요소로 이동
    cout << "p++ 후 *p: " << *p << endl;
    p += 2;  // 2개 요소 앞으로 이동
    cout << "p += 2 후 *p: " << *p << endl;
    
    // 배열을 함수에 전달
    cout << "\n=== 배열을 함수에 전달 ===" << endl;
    void printArray(int* arr, int size);
    printArray(arr, 5);
    
    // 배열 크기 계산
    cout << "\n=== 배열 크기 계산 ===" << endl;
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "배열 크기: " << size << endl;
    
    // 포인터와 배열의 차이
    cout << "\n=== 포인터와 배열의 차이 ===" << endl;
    int* dynamicArr = new int[5];
    for (int i = 0; i < 5; i++) {
        dynamicArr[i] = (i + 1) * 10;
    }
    
    cout << "sizeof(arr): " << sizeof(arr) << " (전체 배열 크기)" << endl;
    cout << "sizeof(dynamicArr): " << sizeof(dynamicArr) << " (포인터 크기)" << endl;
    
    delete[] dynamicArr;
    
    // 2차원 배열과 포인터
    cout << "\n=== 2차원 배열과 포인터 ===" << endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int* matrixPtr = matrix[0];  // 첫 번째 행의 시작 주소
    cout << "2차원 배열 (포인터로 접근):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << *(matrixPtr + i * 4 + j) << "\t";
        }
        cout << endl;
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 배열 최대값 찾기
    int* findMax(int* arr, int size);
    int numbers[] = {85, 92, 78, 96, 88};
    int* maxPtr = findMax(numbers, 5);
    cout << "최대값: " << *maxPtr << " (인덱스: " << (maxPtr - numbers) << ")" << endl;
    
    // 배열 역순
    void reverseArray(int* arr, int size);
    int reverseArr[] = {1, 2, 3, 4, 5};
    cout << "원본: ";
    for (int i = 0; i < 5; i++) {
        cout << reverseArr[i] << " ";
    }
    cout << endl;
    
    reverseArray(reverseArr, 5);
    cout << "역순: ";
    for (int i = 0; i < 5; i++) {
        cout << reverseArr[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// 배열 출력 함수
void printArray(int* arr, int size) {
    cout << "배열: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 최대값 찾기
int* findMax(int* arr, int size) {
    int* maxPtr = arr;
    for (int i = 1; i < size; i++) {
        if (arr[i] > *maxPtr) {
            maxPtr = &arr[i];
        }
    }
    return maxPtr;
}

// 배열 역순
void reverseArray(int* arr, int size) {
    int* start = arr;
    int* end = arr + size - 1;
    
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}


