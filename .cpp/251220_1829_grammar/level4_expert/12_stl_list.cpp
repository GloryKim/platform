/*
 * 4단계 예제 12: STL list
 * 
 * list는 이중 연결 리스트입니다.
 * 임의 위치 삽입/삭제가 빠르지만 임의 접근은 느립니다.
 */

#include <iostream>
#include <list>
using namespace std;

int main() {
    // list 선언 및 초기화
    cout << "=== list 선언 및 초기화 ===" << endl;
    list<int> numbers = {1, 2, 3, 4, 5};
    
    // 앞뒤 요소 추가
    cout << "\n=== 앞뒤 요소 추가 ===" << endl;
    numbers.push_front(0);
    numbers.push_back(6);
    
    cout << "리스트: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 앞뒤 요소 삭제
    cout << "\n=== 앞뒤 요소 삭제 ===" << endl;
    numbers.pop_front();
    numbers.pop_back();
    
    cout << "삭제 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 요소 삽입
    cout << "\n=== 요소 삽입 ===" << endl;
    auto it = numbers.begin();
    advance(it, 2);  // 2번째 위치로 이동
    numbers.insert(it, 99);
    
    cout << "삽입 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 요소 삭제
    cout << "\n=== 요소 삭제 ===" << endl;
    it = numbers.begin();
    advance(it, 2);
    numbers.erase(it);
    
    cout << "삭제 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 정렬
    cout << "\n=== 정렬 ===" << endl;
    list<int> unsorted = {5, 2, 8, 1, 9};
    unsorted.sort();
    
    cout << "정렬 후: ";
    for (int num : unsorted) {
        cout << num << " ";
    }
    cout << endl;
    
    // 역순
    cout << "\n=== 역순 ===" << endl;
    unsorted.reverse();
    cout << "역순: ";
    for (int num : unsorted) {
        cout << num << " ";
    }
    cout << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 작업 큐
    list<string> tasks;
    tasks.push_back("작업1");
    tasks.push_back("작업2");
    tasks.push_back("작업3");
    
    while (!tasks.empty()) {
        cout << "처리 중: " << tasks.front() << endl;
        tasks.pop_front();
    }
    
    return 0;
}


