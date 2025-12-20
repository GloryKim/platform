/*
 * 1단계 예제 7: 상수 (Constants)
 * 
 * 상수는 한 번 값이 할당되면 변경할 수 없는 변수입니다.
 * const 키워드를 사용하여 선언합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // const로 선언한 상수
    const int MAX_SIZE = 100;           // 정수 상수
    const double PI = 3.14159265359;   // 실수 상수
    const char NEWLINE = '\n';         // 문자 상수
    const string GREETING = "Hello";   // 문자열 상수
    
    cout << "MAX_SIZE: " << MAX_SIZE << endl;
    cout << "PI: " << PI << endl;
    cout << "GREETING: " << GREETING << endl;
    
    // 상수는 변경할 수 없음 (컴파일 에러 발생)
    // MAX_SIZE = 200;  // 에러!
    
    // 상수는 선언과 동시에 초기화해야 함
    // const int VALUE;  // 에러! 초기화 필요
    
    // 매직 넘버 대신 상수 사용 (코드 가독성 향상)
    const int MIN_AGE = 18;
    const int MAX_AGE = 65;
    int age = 25;
    
    if (age >= MIN_AGE && age <= MAX_AGE) {
        cout << "나이가 유효합니다." << endl;
    }
    
    // 리터럴 상수
    cout << "\n리터럴 상수:" << endl;
    cout << "정수: " << 42 << endl;
    cout << "실수: " << 3.14 << endl;
    cout << "문자: " << 'A' << endl;
    cout << "문자열: " << "Hello World" << endl;
    cout << "불리언: " << true << " " << false << endl;
    
    // 상수 표현식
    const int HOURS_PER_DAY = 24;
    const int DAYS_PER_WEEK = 7;
    const int HOURS_PER_WEEK = HOURS_PER_DAY * DAYS_PER_WEEK;
    
    cout << "\n시간 계산:" << endl;
    cout << "하루 시간: " << HOURS_PER_DAY << endl;
    cout << "일주일 시간: " << HOURS_PER_WEEK << endl;
    
    // 열거형 상수 (enum)
    enum Color { RED, GREEN, BLUE };
    const Color favoriteColor = RED;
    cout << "\n열거형 상수: " << favoriteColor << endl;
    
    return 0;
}
