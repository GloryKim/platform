/*
 * 1단계 예제 8: 문자열 기본 사용법
 * 
 * string 클래스를 사용한 문자열 처리의 기본을 학습합니다.
 * C++의 string은 동적 크기 조절이 가능한 문자열 클래스입니다.
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // 문자열 선언 및 초기화
    string str1 = "Hello";
    string str2("World");
    string str3;                    // 빈 문자열
    string str4 = str1;            // 복사
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << " (빈 문자열)" << endl;
    cout << "str4: " << str4 << endl;
    
    // 문자열 연결 (concatenation)
    string greeting = str1 + " " + str2;
    cout << "\n문자열 연결: " << greeting << endl;
    
    // 문자열 길이
    cout << "\n문자열 길이:" << endl;
    cout << "str1.length(): " << str1.length() << endl;
    cout << "str1.size(): " << str1.size() << endl;  // length()와 동일
    
    // 문자열 비교
    cout << "\n문자열 비교:" << endl;
    cout << "str1 == str2: " << (str1 == str2) << endl;
    cout << "str1 < str2: " << (str1 < str2) << endl;  // 사전순 비교
    
    // 문자열 접근
    cout << "\n문자열 접근:" << endl;
    cout << "str1[0]: " << str1[0] << endl;        // 첫 번째 문자 'H'
    cout << "str1[1]: " << str1[1] << endl;        // 두 번째 문자 'e'
    str1[0] = 'h';                                  // 문자 변경
    cout << "str1[0] = 'h' 후: " << str1 << endl;
    
    // 부분 문자열 (substring)
    string text = "Hello World";
    string sub1 = text.substr(0, 5);               // 0부터 5개 문자
    string sub2 = text.substr(6);                   // 6부터 끝까지
    cout << "\n부분 문자열:" << endl;
    cout << "text.substr(0, 5): " << sub1 << endl;
    cout << "text.substr(6): " << sub2 << endl;
    
    // 문자열 찾기
    cout << "\n문자열 찾기:" << endl;
    size_t pos = text.find("World");
    if (pos != string::npos) {
        cout << "'World'를 " << pos << "번째 위치에서 찾았습니다." << endl;
    }
    
    // 문자열 입력
    cout << "\n문자열 입력:" << endl;
    string name;
    cout << "이름을 입력하세요: ";
    cin >> name;                                    // 공백 전까지만 입력
    cout << "입력된 이름: " << name << endl;
    
    // 공백 포함 문자열 입력
    cin.ignore();                                   // 버퍼 비우기
    string fullName;
    cout << "전체 이름을 입력하세요 (공백 포함): ";
    getline(cin, fullName);                         // 공백 포함 입력
    cout << "전체 이름: " << fullName << endl;
    
    // 문자열 변환
    string numStr = "123";
    int num = stoi(numStr);                         // string to int
    cout << "\n문자열을 정수로: " << num << " (타입: int)" << endl;
    
    int value = 456;
    string valueStr = to_string(value);             // int to string
    cout << "정수를 문자열로: " << valueStr << " (타입: string)" << endl;
    
    return 0;
}
