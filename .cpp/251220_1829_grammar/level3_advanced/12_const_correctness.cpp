/*
 * 3단계 예제 12: const 정확성 (Const Correctness)
 * 
 * const 키워드를 사용하여 값의 불변성을 보장합니다.
 * 코드의 안전성과 가독성을 높입니다.
 */

#include <iostream>
using namespace std;

// const 매개변수
void printValue(const int& value) {
    cout << "값: " << value << endl;
    // value = 10;  // 에러! const이므로 수정 불가
}

// const 포인터
void processArray(const int* arr, int size) {
    // *arr = 10;  // 에러! const 포인터는 역참조 수정 불가
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// const 멤버 함수 (클래스 예제)
class Counter {
private:
    int count;

public:
    Counter(int c = 0) : count(c) {}
    
    void increment() {
        count++;
    }
    
    int getCount() const {  // const 멤버 함수
        // count++;  // 에러! const 멤버 함수는 멤버 변수 수정 불가
        return count;
    }
};

// const 반환값
const int* getPointer(const int* arr, int index) {
    return &arr[index];
}

int main() {
    // const 변수
    cout << "=== const 변수 ===" << endl;
    const int MAX_SIZE = 100;
    // MAX_SIZE = 200;  // 에러!
    cout << "MAX_SIZE: " << MAX_SIZE << endl;
    
    // const 참조
    cout << "\n=== const 참조 ===" << endl;
    int value = 42;
    const int& ref = value;
    cout << "ref: " << ref << endl;
    // ref = 50;  // 에러!
    value = 50;  // 원본은 변경 가능
    cout << "value 변경 후 ref: " << ref << endl;
    
    // const 포인터
    cout << "\n=== const 포인터 ===" << endl;
    int num = 10;
    const int* ptr1 = &num;  // 포인터가 가리키는 값이 const
    // *ptr1 = 20;  // 에러!
    ptr1 = nullptr;  // 포인터 자체는 변경 가능
    
    int* const ptr2 = &num;  // 포인터 자체가 const
    *ptr2 = 20;  // 값 변경 가능
    // ptr2 = nullptr;  // 에러!
    
    const int* const ptr3 = &num;  // 둘 다 const
    // *ptr3 = 30;  // 에러!
    // ptr3 = nullptr;  // 에러!
    
    // const 배열
    cout << "\n=== const 배열 ===" << endl;
    const int arr[] = {1, 2, 3, 4, 5};
    // arr[0] = 10;  // 에러!
    processArray(arr, 5);
    
    // const 멤버 함수
    cout << "\n=== const 멤버 함수 ===" << endl;
    const Counter counter(10);
    cout << "카운트: " << counter.getCount() << endl;
    // counter.increment();  // 에러! const 객체는 const 멤버만 호출 가능
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 문자열 상수
    const char* message = "Hello World";
    // message[0] = 'h';  // 에러!
    cout << "메시지: " << message << endl;
    
    // 상수 표현식
    const int HOURS_PER_DAY = 24;
    const int DAYS_PER_WEEK = 7;
    const int HOURS_PER_WEEK = HOURS_PER_DAY * DAYS_PER_WEEK;
    cout << "일주일 시간: " << HOURS_PER_WEEK << "시간" << endl;
    
    return 0;
}
