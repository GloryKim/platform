/*
 * 3단계 예제 7: 참조 (References)
 * 
 * 참조는 변수의 별칭(alias)입니다.
 * 포인터보다 안전하고 사용하기 쉬운 대안입니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 참조 선언 및 초기화
    cout << "=== 참조 선언 및 초기화 ===" << endl;
    int num = 42;
    int& ref = num;  // ref는 num의 별칭
    
    cout << "num: " << num << endl;
    cout << "ref: " << ref << endl;
    
    // 참조를 통한 값 변경
    cout << "\n=== 참조를 통한 값 변경 ===" << endl;
    ref = 100;  // num의 값도 변경됨
    cout << "ref 변경 후 num: " << num << endl;
    cout << "ref 변경 후 ref: " << ref << endl;
    
    // 참조는 재할당 불가
    cout << "\n=== 참조는 재할당 불가 ===" << endl;
    int another = 200;
    // ref = another;  // 이것은 값 복사, 참조 재할당 아님
    ref = another;  // num = another와 동일
    cout << "ref = another 후 num: " << num << endl;
    
    // 함수 매개변수로 참조 사용
    cout << "\n=== 함수 매개변수로 참조 사용 ===" << endl;
    void swap(int& a, int& b);
    int x = 10, y = 20;
    
    cout << "교환 전: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "교환 후: x=" << x << ", y=" << y << endl;
    
    // const 참조
    cout << "\n=== const 참조 ===" << endl;
    const int& constRef = num;
    cout << "constRef: " << constRef << endl;
    // constRef = 50;  // 에러! const 참조는 수정 불가
    
    // 참조 반환
    cout << "\n=== 참조 반환 ===" << endl;
    int& getMax(int& a, int& b);
    int a = 10, b = 20;
    int& maxRef = getMax(a, b);
    cout << "maxRef: " << maxRef << endl;
    maxRef = 100;  // 원본 변수도 변경됨
    cout << "maxRef 변경 후 b: " << b << endl;
    
    // 배열 요소 참조
    cout << "\n=== 배열 요소 참조 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int& first = arr[0];
    int& last = arr[4];
    
    cout << "first: " << first << ", last: " << last << endl;
    first = 100;
    last = 500;
    cout << "변경 후 arr[0]: " << arr[0] << ", arr[4]: " << arr[4] << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 큰 객체를 참조로 전달 (복사 비용 절약)
    struct LargeData {
        int data[1000];
    };
    
    void processData(const LargeData& data);
    LargeData ld;
    processData(ld);  // 복사 없이 전달
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 참조는 선언 시 반드시 초기화해야 함" << endl;
    cout << "2. 참조는 재할당 불가 (항상 같은 변수 참조)" << endl;
    cout << "3. 널 참조는 없음 (포인터와의 차이)" << endl;
    cout << "4. 지역 변수의 참조를 반환하면 안 됨" << endl;
    cout << "5. 포인터보다 안전하지만 덜 유연함" << endl;
    
    return 0;
}

// 교환 함수
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 최대값 참조 반환
int& getMax(int& a, int& b) {
    return (a > b) ? a : b;
}

// 큰 데이터 처리
void processData(const LargeData& data) {
    cout << "데이터 처리 완료" << endl;
}


