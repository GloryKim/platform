/*
 * 4단계 예제 11: STL set
 * 
 * set은 중복 없는 요소를 저장하는 컨테이너입니다.
 * 자동 정렬되며 빠른 검색을 제공합니다.
 */

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    // set 선언 및 초기화
    cout << "=== set 선언 및 초기화 ===" << endl;
    set<int> numbers;
    set<string> names = {"Alice", "Bob", "Charlie"};
    
    // 요소 추가
    cout << "\n=== 요소 추가 ===" << endl;
    numbers.insert(5);
    numbers.insert(2);
    numbers.insert(8);
    numbers.insert(2);  // 중복, 추가되지 않음
    numbers.insert(1);
    
    cout << "numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 요소 검색
    cout << "\n=== 요소 검색 ===" << endl;
    auto it = numbers.find(5);
    if (it != numbers.end()) {
        cout << "5를 찾았습니다." << endl;
    }
    
    if (numbers.count(2) > 0) {
        cout << "2가 존재합니다." << endl;
    }
    
    // 요소 삭제
    cout << "\n=== 요소 삭제 ===" << endl;
    numbers.erase(2);
    cout << "2 삭제 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 크기 확인
    cout << "\n=== 크기 확인 ===" << endl;
    cout << "크기: " << numbers.size() << endl;
    cout << "비어있음: " << numbers.empty() << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 중복 제거
    int arr[] = {5, 2, 8, 2, 5, 1, 8};
    set<int> uniqueNumbers(arr, arr + 7);
    
    cout << "원본 배열: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "중복 제거 후: ";
    for (int num : uniqueNumbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 회원 목록 관리
    set<string> members;
    members.insert("홍길동");
    members.insert("김철수");
    members.insert("이영희");
    members.insert("홍길동");  // 중복
    
    cout << "\n회원 목록: ";
    for (const string& member : members) {
        cout << member << " ";
    }
    cout << endl;
    
    return 0;
}



