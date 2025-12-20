/*
 * 4단계 예제 13: STL queue
 * 
 * queue는 FIFO(First In First Out) 자료구조입니다.
 * 큐의 앞에서만 삭제, 뒤에서만 추가가 가능합니다.
 */

#include <iostream>
#include <queue>
using namespace std;

int main() {
    // queue 선언
    cout << "=== queue 선언 ===" << endl;
    queue<int> q;
    
    // 요소 추가
    cout << "\n=== 요소 추가 ===" << endl;
    q.push(10);
    q.push(20);
    q.push(30);
    
    cout << "큐 크기: " << q.size() << endl;
    
    // 요소 접근
    cout << "\n=== 요소 접근 ===" << endl;
    cout << "front: " << q.front() << endl;
    cout << "back: " << q.back() << endl;
    
    // 요소 삭제
    cout << "\n=== 요소 삭제 ===" << endl;
    while (!q.empty()) {
        cout << "제거: " << q.front() << endl;
        q.pop();
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 작업 대기열
    queue<string> tasks;
    tasks.push("작업1");
    tasks.push("작업2");
    tasks.push("작업3");
    
    cout << "대기 중인 작업 수: " << tasks.size() << endl;
    
    while (!tasks.empty()) {
        cout << "처리 중: " << tasks.front() << endl;
        tasks.pop();
    }
    
    return 0;
}


