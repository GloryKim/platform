/*
 * 2단계 예제 19: 어설션 (Assertions)
 * 
 * assert 매크로를 사용하여 프로그램의 가정을 검증합니다.
 * 디버깅과 개발 중 버그 발견에 유용합니다.
 */

#include <iostream>
#include <cassert>
using namespace std;

int divide(int a, int b) {
    assert(b != 0 && "0으로 나눌 수 없습니다!");
    return a / b;
}

int main() {
    // 기본 assert 사용
    cout << "=== 기본 assert 사용 ===" << endl;
    int x = 10;
    assert(x > 0);  // 조건이 true면 통과
    cout << "assert 통과" << endl;
    
    // assert 실패 예제 (주석 처리)
    // int y = -5;
    // assert(y > 0 && "y는 양수여야 합니다!");  // 실패 시 프로그램 종료
    
    // 함수에서 assert 사용
    cout << "\n=== 함수에서 assert 사용 ===" << endl;
    int result = divide(10, 2);
    cout << "10 / 2 = " << result << endl;
    
    // 배열 인덱스 검증
    cout << "\n=== 배열 인덱스 검증 ===" << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    int index = 2;
    assert(index >= 0 && index < 5);
    cout << "arr[" << index << "] = " << arr[index] << endl;
    
    // 포인터 검증
    cout << "\n=== 포인터 검증 ===" << endl;
    int* ptr = new int(42);
    assert(ptr != nullptr && "메모리 할당 실패!");
    cout << "*ptr = " << *ptr << endl;
    delete ptr;
    
    // 실제 사용 예제 1: 범위 검증
    cout << "\n=== 실제 사용 예제 1: 범위 검증 ===" << endl;
    int score = 85;
    assert(score >= 0 && score <= 100 && "점수는 0~100 사이여야 합니다!");
    cout << "점수: " << score << endl;
    
    // 실제 사용 예제 2: 상태 검증
    cout << "\n=== 실제 사용 예제 2: 상태 검증 ===" << endl;
    bool isInitialized = true;
    assert(isInitialized && "초기화되지 않았습니다!");
    cout << "초기화 완료" << endl;
    
    // 실제 사용 예제 3: 불변식 검증
    cout << "\n=== 실제 사용 예제 3: 불변식 검증 ===" << endl;
    int balance = 1000;
    int withdrawal = 500;
    
    assert(balance >= withdrawal && "잔액이 부족합니다!");
    balance -= withdrawal;
    assert(balance >= 0 && "잔액은 음수가 될 수 없습니다!");
    
    cout << "출금 후 잔액: " << balance << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. assert는 디버그 모드에서만 작동 (NDEBUG 정의 시 비활성화)" << endl;
    cout << "2. 프로덕션 코드에서는 사용하지 않음" << endl;
    cout << "3. 사용자 입력 검증에는 적합하지 않음" << endl;
    cout << "4. 프로그램의 가정을 검증하는 용도로만 사용" << endl;
    cout << "5. assert 실패 시 프로그램이 즉시 종료됨" << endl;
    
    // NDEBUG 정의 시 assert 비활성화
    // #define NDEBUG
    // #include <cassert>
    // assert(false);  // 이제 작동하지 않음
    
    return 0;
}



