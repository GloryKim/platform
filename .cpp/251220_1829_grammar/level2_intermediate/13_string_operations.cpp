/*
 * 2단계 예제 13: 문자열 연산
 * 
 * string 클래스를 사용한 문자열 조작을 학습합니다.
 * C 스타일 문자열보다 안전하고 편리합니다.
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    // 문자열 선언 및 초기화
    cout << "=== 문자열 선언 및 초기화 ===" << endl;
    string str1 = "Hello";
    string str2("World");
    string str3;
    string str4 = str1;  // 복사
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << " (빈 문자열)" << endl;
    cout << "str4: " << str4 << endl;
    
    // 문자열 연결
    cout << "\n=== 문자열 연결 ===" << endl;
    string greeting = str1 + " " + str2;
    cout << "연결: " << greeting << endl;
    
    str1 += " C++";
    cout << "+= 연산 후 str1: " << str1 << endl;
    
    // 문자열 길이
    cout << "\n=== 문자열 길이 ===" << endl;
    string text = "Hello World";
    cout << "text.length(): " << text.length() << endl;
    cout << "text.size(): " << text.size() << endl;
    cout << "text.empty(): " << text.empty() << endl;
    
    // 문자열 접근
    cout << "\n=== 문자열 접근 ===" << endl;
    cout << "text[0]: " << text[0] << endl;
    cout << "text[6]: " << text[6] << endl;
    cout << "text.at(0): " << text.at(0) << endl;
    
    text[0] = 'h';
    cout << "수정 후 text: " << text << endl;
    
    // 부분 문자열
    cout << "\n=== 부분 문자열 ===" << endl;
    string sub1 = text.substr(0, 5);  // 0부터 5개 문자
    string sub2 = text.substr(6);     // 6부터 끝까지
    cout << "substr(0, 5): " << sub1 << endl;
    cout << "substr(6): " << sub2 << endl;
    
    // 문자열 찾기
    cout << "\n=== 문자열 찾기 ===" << endl;
    string sentence = "Hello World Hello";
    size_t pos1 = sentence.find("Hello");
    size_t pos2 = sentence.find("World");
    size_t pos3 = sentence.find("C++");
    
    if (pos1 != string::npos) {
        cout << "'Hello'를 " << pos1 << "번째 위치에서 찾았습니다." << endl;
    }
    if (pos2 != string::npos) {
        cout << "'World'를 " << pos2 << "번째 위치에서 찾았습니다." << endl;
    }
    if (pos3 == string::npos) {
        cout << "'C++'를 찾을 수 없습니다." << endl;
    }
    
    // 문자열 교체
    cout << "\n=== 문자열 교체 ===" << endl;
    string str = "Hello World";
    str.replace(6, 5, "C++");  // 6번째부터 5개 문자를 "C++"로 교체
    cout << "교체 후: " << str << endl;
    
    // 문자열 삽입
    cout << "\n=== 문자열 삽입 ===" << endl;
    str = "Hello World";
    str.insert(5, " C++");  // 5번째 위치에 " C++" 삽입
    cout << "삽입 후: " << str << endl;
    
    // 문자열 삭제
    cout << "\n=== 문자열 삭제 ===" << endl;
    str = "Hello World";
    str.erase(5, 6);  // 5번째부터 6개 문자 삭제
    cout << "삭제 후: " << str << endl;
    
    // 문자열 비교
    cout << "\n=== 문자열 비교 ===" << endl;
    string s1 = "apple";
    string s2 = "banana";
    string s3 = "apple";
    
    cout << "s1 == s3: " << (s1 == s3) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;
    cout << "s1.compare(s2): " << s1.compare(s2) << endl;
    
    // 대소문자 변환
    cout << "\n=== 대소문자 변환 ===" << endl;
    string mixed = "Hello World";
    
    // 대문자로 변환
    string upper = mixed;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout << "대문자: " << upper << endl;
    
    // 소문자로 변환
    string lower = mixed;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    cout << "소문자: " << lower << endl;
    
    // 문자열 뒤집기
    cout << "\n=== 문자열 뒤집기 ===" << endl;
    string reverse = "Hello";
    reverse_string(reverse.begin(), reverse.end());
    cout << "뒤집기: " << reverse << endl;
    
    // 숫자와 문자열 변환
    cout << "\n=== 숫자와 문자열 변환 ===" << endl;
    string numStr = "123";
    int num = stoi(numStr);  // string to int
    cout << "stoi(\"123\"): " << num << endl;
    
    double dbl = stod("3.14");  // string to double
    cout << "stod(\"3.14\"): " << dbl << endl;
    
    int value = 456;
    string valueStr = to_string(value);  // int to string
    cout << "to_string(456): \"" << valueStr << "\"" << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 이메일 주소 검증 (간단한 예제)
    string email = "user@example.com";
    if (email.find('@') != string::npos && email.find('.') != string::npos) {
        cout << "유효한 이메일 형식: " << email << endl;
    }
    
    // 파일 확장자 추출
    string filename = "document.pdf";
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != string::npos) {
        string extension = filename.substr(dotPos + 1);
        cout << "파일 확장자: " << extension << endl;
    }
    
    // 단어 개수 세기 (간단한 예제)
    string sentence2 = "Hello World C++";
    int wordCount = 1;
    for (char c : sentence2) {
        if (c == ' ') {
            wordCount++;
        }
    }
    cout << "단어 개수: " << wordCount << endl;
    
    return 0;
}
