/*
 * 5단계 예제 11: 범위 기반 for 루프
 * 
 * 범위 기반 for는 컨테이너의 모든 요소를 순회합니다.
 * 간결하고 안전한 반복을 제공합니다.
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main() {
    // 배열 순회
    cout << "=== 배열 순회 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    // vector 순회
    cout << "\n=== vector 순회 ===" << endl;
    vector<int> numbers = {10, 20, 30, 40, 50};
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 참조로 순회 (수정 가능)
    cout << "\n=== 참조로 순회 ===" << endl;
    for (int& num : numbers) {
        num *= 2;
    }
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // const 참조로 순회
    cout << "\n=== const 참조로 순회 ===" << endl;
    const vector<int> constNumbers = {1, 2, 3, 4, 5};
    for (const int& num : constNumbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // map 순회
    cout << "\n=== map 순회 ===" << endl;
    map<string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };
    
    for (const auto& pair : scores) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // 구조화된 바인딩 (C++17)
    cout << "\n=== 구조화된 바인딩 ===" << endl;
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    // 문자열 순회
    cout << "\n=== 문자열 순회 ===" << endl;
    string text = "Hello";
    for (char c : text) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}



