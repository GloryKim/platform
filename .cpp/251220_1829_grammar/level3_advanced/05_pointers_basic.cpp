/*
 * 3단계 예제 5: 포인터 기본
 * 
 * 포인터는 메모리 주소를 저장하는 변수입니다.
 * C++의 핵심 개념 중 하나로, 동적 메모리 관리에 필수적입니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 포인터 선언 및 초기화
    cout << "=== 포인터 선언 및 초기화 ===" << endl;
    int num = 42;
    int* ptr = &num;  // num의 주소를 저장
    
    cout << "num의 값: " << num << endl;
    cout << "num의 주소: " << &num << endl;
    cout << "ptr이 가리키는 주소: " << ptr << endl;
    cout << "ptr이 가리키는 값: " << *ptr << endl;
    
    // 포인터를 통한 값 변경
    cout << "\n=== 포인터를 통한 값 변경 ===" << endl;
    *ptr = 100;  // num의 값을 변경
    cout << "ptr을 통해 값 변경 후 num: " << num << endl;
    
    // 널 포인터
    cout << "\n=== 널 포인터 ===" << endl;
    int* nullPtr = nullptr;
    // int* nullPtr = NULL;  // C 스타일
    
    if (nullPtr == nullptr) {
        cout << "포인터가 null입니다." << endl;
    }
    
    // 포인터 연산
    cout << "\n=== 포인터 연산 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int* arrPtr = arr;  // 배열의 첫 번째 요소 주소
    
    cout << "arrPtr이 가리키는 값: " << *arrPtr << endl;
    arrPtr++;  // 다음 요소로 이동
    cout << "arrPtr++ 후 값: " << *arrPtr << endl;
    arrPtr += 2;  // 2개 요소 앞으로 이동
    cout << "arrPtr += 2 후 값: " << *arrPtr << endl;
    
    // 배열과 포인터
    cout << "\n=== 배열과 포인터 ===" << endl;
    int numbers[] = {1, 2, 3, 4, 5};
    int* numPtr = numbers;
    
    cout << "배열 요소 (포인터 사용): ";
    for (int i = 0; i < 5; i++) {
        cout << *(numPtr + i) << " ";
    }
    cout << endl;
    
    // 포인터의 포인터
    cout << "\n=== 포인터의 포인터 ===" << endl;
    int value = 42;
    int* ptr1 = &value;
    int** ptr2 = &ptr1;  // ptr1의 주소를 저장
    
    cout << "value: " << value << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "**ptr2: " << **ptr2 << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 두 변수 교환
    int a = 10, b = 20;
    int* aPtr = &a;
    int* bPtr = &b;
    
    cout << "교환 전: a=" << a << ", b=" << b << endl;
    int temp = *aPtr;
    *aPtr = *bPtr;
    *bPtr = temp;
    cout << "교환 후: a=" << a << ", b=" << b << endl;
    
    // 배열 최대값 찾기
    int scores[] = {85, 92, 78, 96, 88};
    int* maxPtr = scores;
    
    for (int i = 1; i < 5; i++) {
        if (scores[i] > *maxPtr) {
            maxPtr = &scores[i];
        }
    }
    cout << "최대값: " << *maxPtr << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 초기화되지 않은 포인터 사용 금지" << endl;
    cout << "2. 널 포인터 역참조 금지" << endl;
    cout << "3. 해제된 메모리 접근 금지" << endl;
    cout << "4. 포인터 연산 시 범위 확인 필수" << endl;
    
    return 0;
}
