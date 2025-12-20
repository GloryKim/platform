/*
 * 3단계 예제 20: 정의되지 않은 동작 (Undefined Behavior)
 * 
 * 정의되지 않은 동작은 피해야 하는 코드 패턴입니다.
 * 예측할 수 없는 결과를 초래할 수 있습니다.
 */

#include <iostream>
using namespace std;

int main() {
    cout << "=== 정의되지 않은 동작 예제 ===" << endl;
    
    // 1. 초기화되지 않은 변수 사용
    cout << "\n1. 초기화되지 않은 변수 사용" << endl;
    // int uninitialized;
    // cout << uninitialized << endl;  // 정의되지 않은 동작!
    
    // 올바른 방법
    int initialized = 0;
    cout << "초기화된 변수: " << initialized << endl;
    
    // 2. 배열 범위를 벗어난 접근
    cout << "\n2. 배열 범위를 벗어난 접근" << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    // cout << arr[10] << endl;  // 정의되지 않은 동작!
    
    // 올바른 방법
    if (10 < 5) {
        cout << arr[10] << endl;
    } else {
        cout << "인덱스 범위 확인 필요" << endl;
    }
    
    // 3. 널 포인터 역참조
    cout << "\n3. 널 포인터 역참조" << endl;
    int* ptr = nullptr;
    // cout << *ptr << endl;  // 정의되지 않은 동작!
    
    // 올바른 방법
    if (ptr != nullptr) {
        cout << *ptr << endl;
    } else {
        cout << "포인터가 null입니다." << endl;
    }
    
    // 4. 해제된 메모리 접근
    cout << "\n4. 해제된 메모리 접근" << endl;
    int* dynamicPtr = new int(42);
    delete dynamicPtr;
    // cout << *dynamicPtr << endl;  // 정의되지 않은 동작!
    
    // 올바른 방법
    dynamicPtr = nullptr;  // 해제 후 nullptr 설정
    if (dynamicPtr != nullptr) {
        cout << *dynamicPtr << endl;
    }
    
    // 5. 0으로 나누기
    cout << "\n5. 0으로 나누기" << endl;
    int a = 10, b = 0;
    // int result = a / b;  // 정의되지 않은 동작!
    
    // 올바른 방법
    if (b != 0) {
        int result = a / b;
        cout << "결과: " << result << endl;
    } else {
        cout << "0으로 나눌 수 없습니다." << endl;
    }
    
    // 6. 부호 있는 정수 오버플로우
    cout << "\n6. 부호 있는 정수 오버플로우" << endl;
    int maxInt = 2147483647;
    // int overflow = maxInt + 1;  // 정의되지 않은 동작!
    
    // 올바른 방법
    if (maxInt < 2147483647) {
        int safe = maxInt + 1;
    } else {
        cout << "오버플로우 위험" << endl;
    }
    
    // 7. 같은 메모리 두 번 해제
    cout << "\n7. 같은 메모리 두 번 해제" << endl;
    int* doubleDelete = new int(10);
    delete doubleDelete;
    // delete doubleDelete;  // 정의되지 않은 동작!
    
    // 올바른 방법
    doubleDelete = nullptr;  // 해제 후 nullptr 설정
    
    // 8. 지역 변수 참조 반환
    cout << "\n8. 지역 변수 참조 반환" << endl;
    // int& getLocalRef() {
    //     int local = 42;
    //     return local;  // 정의되지 않은 동작!
    // }
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 모든 변수는 사용 전 초기화" << endl;
    cout << "2. 배열 인덱스 범위 확인" << endl;
    cout << "3. 포인터 사용 전 null 체크" << endl;
    cout << "4. 메모리 해제 후 nullptr 설정" << endl;
    cout << "5. 나눗셈 전에 0 체크" << endl;
    cout << "6. 오버플로우 가능성 확인" << endl;
    cout << "7. 컴파일러 경고 주의 깊게 읽기" << endl;
    cout << "8. 정적 분석 도구 사용 권장" << endl;
    
    return 0;
}


