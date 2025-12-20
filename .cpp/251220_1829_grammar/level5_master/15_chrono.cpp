/*
 * 5단계 예제 15: chrono
 * 
 * chrono는 시간 관련 기능을 제공합니다.
 * 시간 측정, 대기, 시간 포인트 등을 다룹니다.
 */

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

int main() {
    // 시간 측정
    cout << "=== 시간 측정 ===" << endl;
    auto start = high_resolution_clock::now();
    
    // 작업 시뮬레이션
    this_thread::sleep_for(milliseconds(100));
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "소요 시간: " << duration.count() << "ms" << endl;
    
    // 시간 단위
    cout << "\n=== 시간 단위 ===" << endl;
    seconds sec(5);
    milliseconds ms = duration_cast<milliseconds>(sec);
    cout << "5초 = " << ms.count() << "ms" << endl;
    
    // 현재 시간
    cout << "\n=== 현재 시간 ===" << endl;
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    cout << "현재 시간: " << ctime(&time);
    
    // 시간 포인트
    cout << "\n=== 시간 포인트 ===" << endl;
    auto timePoint = system_clock::now();
    auto elapsed = timePoint.time_since_epoch();
    cout << "경과 시간: " << duration_cast<seconds>(elapsed).count() << "초" << endl;
    
    return 0;
}


