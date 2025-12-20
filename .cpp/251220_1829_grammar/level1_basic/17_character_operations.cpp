/*
 * 1단계 예제 17: 문자 연산
 * 
 * 문자(char) 타입의 연산과 변환을 학습합니다.
 * 문자는 ASCII 값으로 저장되므로 정수처럼 연산할 수 있습니다.
 */

#include <iostream>
#include <cctype>  // 문자 관련 함수들
using namespace std;

int main() {
    // 문자 기본 사용
    cout << "=== 문자 기본 사용 ===" << endl;
    
    char ch1 = 'A';
    char ch2 = 'B';
    char ch3 = 'a';
    
    cout << "ch1 = '" << ch1 << "'" << endl;
    cout << "ch2 = '" << ch2 << "'" << endl;
    cout << "ch3 = '" << ch3 << "'" << endl;
    
    // 문자와 정수
    cout << "\n=== 문자와 정수 ===" << endl;
    cout << "ch1의 ASCII 값: " << (int)ch1 << endl;
    cout << "ASCII 65는 문자: " << (char)65 << endl;
    
    // 문자 연산
    cout << "\n=== 문자 연산 ===" << endl;
    char letter = 'A';
    cout << "letter = '" << letter << "'" << endl;
    cout << "letter + 1 = '" << (char)(letter + 1) << "'" << endl;  // 'B'
    cout << "letter + 3 = '" << (char)(letter + 3) << "'" << endl;  // 'D'
    
    // 대소문자 변환
    cout << "\n=== 대소문자 변환 ===" << endl;
    char upper = 'A';
    char lower = 'z';
    
    // tolower, toupper 함수 사용
    cout << "tolower('" << upper << "') = '" << (char)tolower(upper) << "'" << endl;
    cout << "toupper('" << lower << "') = '" << (char)toupper(lower) << "'" << endl;
    
    // 수동 변환 (ASCII 차이 이용)
    char ch = 'M';
    char lowerCh = ch + 32;  // 대문자 + 32 = 소문자
    cout << "'" << ch << "' -> '" << lowerCh << "'" << endl;
    
    // 문자 검사 함수
    cout << "\n=== 문자 검사 함수 ===" << endl;
    char test1 = 'A', test2 = 'a', test3 = '5', test4 = ' ', test5 = '!';
    
    cout << "isalpha('" << test1 << "'): " << isalpha(test1) << " (알파벳인가?)" << endl;
    cout << "isdigit('" << test3 << "'): " << isdigit(test3) << " (숫자인가?)" << endl;
    cout << "isalnum('" << test1 << "'): " << isalnum(test1) << " (알파벳 또는 숫자인가?)" << endl;
    cout << "isspace('" << test4 << "'): " << isspace(test4) << " (공백인가?)" << endl;
    cout << "isupper('" << test1 << "'): " << isupper(test1) << " (대문자인가?)" << endl;
    cout << "islower('" << test2 << "'): " << islower(test2) << " (소문자인가?)" << endl;
    cout << "ispunct('" << test5 << "'): " << ispunct(test5) << " (구두점인가?)" << endl;
    
    // 문자 비교
    cout << "\n=== 문자 비교 ===" << endl;
    char c1 = 'A', c2 = 'B', c3 = 'A';
    cout << "'" << c1 << "' == '" << c3 << "': " << (c1 == c3) << endl;
    cout << "'" << c1 << "' < '" << c2 << "': " << (c1 < c2) << endl;
    cout << "'" << c1 << "' > '" << c2 << "': " << (c1 > c2) << endl;
    
    // 문자 배열 (문자열)
    cout << "\n=== 문자 배열 ===" << endl;
    char str1[] = "Hello";
    char str2[10] = "World";
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    
    // 개별 문자 접근
    cout << "str1[0]: '" << str1[0] << "'" << endl;
    cout << "str1[1]: '" << str1[1] << "'" << endl;
    
    // 문자 반복
    cout << "\n=== 문자 반복 ===" << endl;
    cout << "알파벳 대문자: ";
    for (char c = 'A'; c <= 'Z'; c++) {
        cout << c << " ";
    }
    cout << endl;
    
    cout << "알파벳 소문자: ";
    for (char c = 'a'; c <= 'z'; c++) {
        cout << c << " ";
    }
    cout << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 문자열의 모든 문자를 대문자로 변환
    char text[] = "Hello World";
    cout << "원본: " << text << endl;
    cout << "대문자 변환: ";
    for (int i = 0; text[i] != '\0'; i++) {
        cout << (char)toupper(text[i]);
    }
    cout << endl;
    
    // 문자열의 모든 문자를 소문자로 변환
    cout << "소문자 변환: ";
    for (int i = 0; text[i] != '\0'; i++) {
        cout << (char)tolower(text[i]);
    }
    cout << endl;
    
    // 숫자 문자를 정수로 변환
    char digit = '7';
    int num = digit - '0';  // '7' - '0' = 7
    cout << "\n문자 '" << digit << "'를 정수로: " << num << endl;
    
    // 정수를 문자로 변환
    int number = 5;
    char digitChar = number + '0';  // 5 + '0' = '5'
    cout << "정수 " << number << "를 문자로: '" << digitChar << "'" << endl;
    
    return 0;
}



