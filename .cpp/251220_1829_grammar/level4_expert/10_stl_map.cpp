/*
 * 4단계 예제 10: STL map
 * 
 * map은 키-값 쌍을 저장하는 연관 컨테이너입니다.
 * 키를 기준으로 자동 정렬되며 빠른 검색을 제공합니다.
 */

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // map 선언 및 초기화
    cout << "=== map 선언 및 초기화 ===" << endl;
    map<string, int> scores;
    
    // 요소 추가
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    scores.insert({"David", 88});
    scores.insert(make_pair("Eve", 90));
    
    // 요소 접근
    cout << "\n=== 요소 접근 ===" << endl;
    cout << "Alice의 점수: " << scores["Alice"] << endl;
    cout << "Bob의 점수: " << scores.at("Bob") << endl;
    
    // 요소 검색
    cout << "\n=== 요소 검색 ===" << endl;
    auto it = scores.find("Charlie");
    if (it != scores.end()) {
        cout << "Charlie의 점수: " << it->second << endl;
    }
    
    // 요소 존재 확인
    if (scores.count("David") > 0) {
        cout << "David가 존재합니다." << endl;
    }
    
    // 전체 순회
    cout << "\n=== 전체 순회 ===" << endl;
    for (const auto& pair : scores) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // 반복자 사용
    cout << "\n=== 반복자 사용 ===" << endl;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        cout << it->first << " -> " << it->second << endl;
    }
    
    // 요소 삭제
    cout << "\n=== 요소 삭제 ===" << endl;
    scores.erase("Eve");
    cout << "Eve 삭제 후 크기: " << scores.size() << endl;
    
    // 크기 확인
    cout << "\n=== 크기 확인 ===" << endl;
    cout << "map 크기: " << scores.size() << endl;
    cout << "비어있음: " << scores.empty() << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 학생 점수 관리
    map<string, int> studentScores;
    studentScores["홍길동"] = 95;
    studentScores["김철수"] = 87;
    studentScores["이영희"] = 92;
    
    // 점수 업데이트
    studentScores["김철수"] = 90;
    
    // 평균 계산
    int sum = 0;
    for (const auto& pair : studentScores) {
        sum += pair.second;
    }
    double average = (double)sum / studentScores.size();
    cout << "평균 점수: " << average << endl;
    
    // 단어 빈도 계산
    map<string, int> wordCount;
    string words[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    
    for (const string& word : words) {
        wordCount[word]++;
    }
    
    cout << "\n단어 빈도:" << endl;
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << "번" << endl;
    }
    
    return 0;
}
