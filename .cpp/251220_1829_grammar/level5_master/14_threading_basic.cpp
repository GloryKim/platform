/*
 * 5단계 예제 14: 스레딩 기본
 * 
 * 멀티스레딩은 여러 작업을 동시에 수행할 수 있게 합니다.
 * <thread> 헤더를 사용합니다.
 */

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// 스레드 함수
void printNumbers(int start, int end) {
    for (int i = start; i <= end; i++) {
        cout << "스레드: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void printMessage(string msg, int count) {
    for (int i = 0; i < count; i++) {
        cout << msg << " " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    // 기본 스레드 생성
    cout << "=== 기본 스레드 생성 ===" << endl;
    thread t1(printNumbers, 1, 5);
    thread t2(printMessage, "Hello", 3);
    
    // 스레드 대기
    t1.join();
    t2.join();
    
    // 람다와 스레드
    cout << "\n=== 람다와 스레드 ===" << endl;
    thread t3([]() {
        for (int i = 0; i < 3; i++) {
            cout << "람다 스레드: " << i << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });
    
    t3.join();
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. join() 또는 detach() 필수" << endl;
    cout << "2. 데이터 경쟁 주의" << endl;
    cout << "3. 동기화 메커니즘 필요" << endl;
    cout << "4. 예외 안전성 고려" << endl;
    
    return 0;
}


