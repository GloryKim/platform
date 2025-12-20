/*
 * 4단계 예제 9: STL vector
 * 
 * vector는 동적 배열입니다.
 * 크기가 자동으로 조절되며 다양한 유용한 함수를 제공합니다.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // vector 선언 및 초기화
    cout << "=== vector 선언 및 초기화 ===" << endl;
    vector<int> v1;
    vector<int> v2(5);  // 5개 요소, 기본값 0
    vector<int> v3(5, 10);  // 5개 요소, 모두 10
    vector<int> v4 = {1, 2, 3, 4, 5};
    
    // 요소 추가
    cout << "\n=== 요소 추가 ===" << endl;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    
    cout << "v1: ";
    for (int num : v1) {
        cout << num << " ";
    }
    cout << endl;
    
    // 요소 접근
    cout << "\n=== 요소 접근 ===" << endl;
    cout << "v4[0] = " << v4[0] << endl;
    cout << "v4.at(1) = " << v4.at(1) << endl;
    cout << "v4.front() = " << v4.front() << endl;
    cout << "v4.back() = " << v4.back() << endl;
    
    // 크기 및 용량
    cout << "\n=== 크기 및 용량 ===" << endl;
    cout << "v4.size() = " << v4.size() << endl;
    cout << "v4.capacity() = " << v4.capacity() << endl;
    cout << "v4.empty() = " << v4.empty() << endl;
    
    // 요소 삽입
    cout << "\n=== 요소 삽입 ===" << endl;
    v4.insert(v4.begin() + 2, 99);
    cout << "삽입 후: ";
    for (int num : v4) {
        cout << num << " ";
    }
    cout << endl;
    
    // 요소 삭제
    cout << "\n=== 요소 삭제 ===" << endl;
    v4.erase(v4.begin() + 2);
    v4.pop_back();
    cout << "삭제 후: ";
    for (int num : v4) {
        cout << num << " ";
    }
    cout << endl;
    
    // 반복자
    cout << "\n=== 반복자 ===" << endl;
    cout << "반복자로 출력: ";
    for (auto it = v4.begin(); it != v4.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // 알고리즘 사용
    cout << "\n=== 알고리즘 사용 ===" << endl;
    vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    sort(numbers.begin(), numbers.end());
    cout << "정렬 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    reverse(numbers.begin(), numbers.end());
    cout << "역순: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    auto maxIt = max_element(numbers.begin(), numbers.end());
    cout << "최대값: " << *maxIt << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    vector<string> names = {"Alice", "Bob", "Charlie"};
    
    names.push_back("David");
    cout << "이름 목록: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    return 0;
}



