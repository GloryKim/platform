/*
 * 1단계 예제 18: 출력 포맷팅
 * 
 * cout을 사용한 출력 포맷팅 방법을 학습합니다.
 * <iomanip> 헤더의 조작자(manipulator)를 사용합니다.
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 기본 출력
    cout << "=== 기본 출력 ===" << endl;
    cout << "Hello" << " " << "World" << endl;
    
    // 정수 포맷팅
    cout << "\n=== 정수 포맷팅 ===" << endl;
    int num = 123;
    cout << "기본: " << num << endl;
    cout << "8진수: " << oct << num << endl;
    cout << "16진수: " << hex << num << endl;
    cout << "10진수로 복원: " << dec << num << endl;
    
    // 16진수 대문자
    cout << "16진수 대문자: " << uppercase << hex << num << nouppercase << dec << endl;
    
    // 필드 너비 설정
    cout << "\n=== 필드 너비 설정 ===" << endl;
    int value = 42;
    cout << "기본: [" << value << "]" << endl;
    cout << "너비 10: [" << setw(10) << value << "]" << endl;
    cout << "너비 10, 오른쪽 정렬: [" << setw(10) << right << value << "]" << endl;
    cout << "너비 10, 왼쪽 정렬: [" << setw(10) << left << value << "]" << endl;
    cout << "너비 10, 내부 정렬: [" << setw(10) << internal << value << "]" << endl;
    
    // 채움 문자 설정
    cout << "\n=== 채움 문자 설정 ===" << endl;
    cout << "0으로 채우기: [" << setfill('0') << setw(5) << value << "]" << endl;
    cout << "*로 채우기: [" << setfill('*') << setw(10) << value << "]" << endl;
    cout << "공백으로 복원: [" << setfill(' ') << setw(10) << value << "]" << endl;
    
    // 실수 포맷팅
    cout << "\n=== 실수 포맷팅 ===" << endl;
    double pi = 3.141592653589793;
    
    // 기본 출력
    cout << "기본: " << pi << endl;
    
    // 고정 소수점 표기법
    cout << fixed;
    cout << "고정 소수점 (기본): " << pi << endl;
    cout << "고정 소수점 (소수점 2자리): " << setprecision(2) << pi << endl;
    cout << "고정 소수점 (소수점 5자리): " << setprecision(5) << pi << endl;
    
    // 과학적 표기법
    cout << scientific;
    cout << "과학적 표기법: " << pi << endl;
    cout << "과학적 표기법 (소수점 2자리): " << setprecision(2) << pi << endl;
    
    // 기본 표기법으로 복원
    cout << defaultfloat;
    cout << "기본 표기법: " << setprecision(6) << pi << endl;
    
    // 부울 값 포맷팅
    cout << "\n=== 부울 값 포맷팅 ===" << endl;
    bool flag = true;
    cout << "기본: " << flag << endl;
    cout << boolalpha;
    cout << "boolalpha: " << flag << endl;
    cout << noboolalpha;
    cout << "noboolalpha: " << flag << endl;
    
    // 표 형식 출력
    cout << "\n=== 표 형식 출력 ===" << endl;
    cout << fixed << setprecision(2);
    cout << left << setfill(' ');
    cout << setw(15) << "이름" << setw(10) << "나이" << setw(15) << "점수" << endl;
    cout << setw(15) << "홍길동" << setw(10) << 25 << setw(15) << 95.5 << endl;
    cout << setw(15) << "김철수" << setw(10) << 30 << setw(15) << 87.3 << endl;
    cout << setw(15) << "이영희" << setw(10) << 28 << setw(15) << 92.1 << endl;
    
    // 숫자 정렬
    cout << "\n=== 숫자 정렬 ===" << endl;
    cout << right << setfill(' ');
    cout << setw(10) << 123 << endl;
    cout << setw(10) << 45 << endl;
    cout << setw(10) << 6789 << endl;
    
    // 통화 형식 (간단한 예제)
    cout << "\n=== 통화 형식 ===" << endl;
    double price = 1234.56;
    cout << fixed << setprecision(2);
    cout << "가격: $" << setw(10) << right << price << endl;
    cout << "가격: " << setw(10) << right << price << "원" << endl;
    
    // 16진수 표시
    cout << "\n=== 16진수 표시 ===" << endl;
    int hexValue = 255;
    cout << "10진수: " << dec << hexValue << endl;
    cout << "16진수: 0x" << hex << uppercase << hexValue << dec << endl;
    cout << "16진수 (소문자): 0x" << hex << nouppercase << hexValue << dec << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 성적표 출력
    cout << fixed << setprecision(1);
    cout << left << setfill(' ');
    cout << "\n성적표\n";
    cout << setw(10) << "과목" << setw(10) << "점수" << setw(10) << "등급" << endl;
    cout << setw(10) << "수학" << setw(10) << 95.5 << setw(10) << "A" << endl;
    cout << setw(10) << "영어" << setw(10) << 87.3 << setw(10) << "B" << endl;
    cout << setw(10) << "과학" << setw(10) << 92.1 << setw(10) << "A" << endl;
    
    return 0;
}
