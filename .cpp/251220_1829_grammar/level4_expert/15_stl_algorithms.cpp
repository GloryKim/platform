/*
 * 4단계 예제 15: STL 알고리즘
 * 
 * STL 알고리즘은 컨테이너에 대해 다양한 연산을 수행합니다.
 * 정렬, 검색, 변환 등의 기능을 제공합니다.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // 정렬
    cout << "=== 정렬 ===" << endl;
    sort(numbers.begin(), numbers.end());
    cout << "정렬 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 역순 정렬
    sort(numbers.begin(), numbers.end(), greater<int>());
    cout << "역순 정렬: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 검색
    cout << "\n=== 검색 ===" << endl;
    sort(numbers.begin(), numbers.end());
    bool found = binary_search(numbers.begin(), numbers.end(), 5);
    cout << "5 검색: " << (found ? "찾음" : "없음") << endl;
    
    auto it = find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        cout << "7을 " << distance(numbers.begin(), it) << "번째 위치에서 찾음" << endl;
    }
    
    // 최대/최소
    cout << "\n=== 최대/최소 ===" << endl;
    auto maxIt = max_element(numbers.begin(), numbers.end());
    auto minIt = min_element(numbers.begin(), numbers.end());
    cout << "최대값: " << *maxIt << endl;
    cout << "최소값: " << *minIt << endl;
    
    // 카운트
    cout << "\n=== 카운트 ===" << endl;
    numbers.push_back(5);
    int count5 = count(numbers.begin(), numbers.end(), 5);
    cout << "5의 개수: " << count5 << endl;
    
    // 변환
    cout << "\n=== 변환 ===" << endl;
    vector<int> doubled(numbers.size());
    transform(numbers.begin(), numbers.end(), doubled.begin(), 
              [](int x) { return x * 2; });
    
    cout << "2배: ";
    for (int num : doubled) {
        cout << num << " ";
    }
    cout << endl;
    
    // 합계
    cout << "\n=== 합계 ===" << endl;
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    cout << "합계: " << sum << endl;
    
    // 역순
    cout << "\n=== 역순 ===" << endl;
    reverse(numbers.begin(), numbers.end());
    cout << "역순: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 제거
    cout << "\n=== 제거 ===" << endl;
    numbers.erase(remove(numbers.begin(), numbers.end(), 5), numbers.end());
    cout << "5 제거 후: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
