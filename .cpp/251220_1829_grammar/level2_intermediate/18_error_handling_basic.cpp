/*
 * 2단계 예제 18: 기본 에러 처리
 * 
 * 프로그램에서 발생할 수 있는 에러를 처리하는 기본 방법을 학습합니다.
 * 입력 검증, 범위 확인 등을 다룹니다.
 */

#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

int main() {
    // 입력 검증
    cout << "=== 입력 검증 ===" << endl;
    int age;
    
    // 시뮬레이션: 실제로는 cin >> age;
    age = 25;  // 정상 입력
    // age = -5;  // 잘못된 입력
    
    if (age < 0 || age > 150) {
        cout << "에러: 나이는 0~150 사이여야 합니다." << endl;
    } else {
        cout << "유효한 나이: " << age << "세" << endl;
    }
    
    // 0으로 나누기 방지
    cout << "\n=== 0으로 나누기 방지 ===" << endl;
    double numerator = 10.0;
    double denominator = 0.0;
    
    if (denominator == 0.0) {
        cout << "에러: 0으로 나눌 수 없습니다." << endl;
    } else {
        double result = numerator / denominator;
        cout << "결과: " << result << endl;
    }
    
    // 배열 인덱스 범위 확인
    cout << "\n=== 배열 인덱스 범위 확인 ===" << endl;
    int arr[5] = {10, 20, 30, 40, 50};
    int index = 3;
    
    if (index >= 0 && index < 5) {
        cout << "arr[" << index << "] = " << arr[index] << endl;
    } else {
        cout << "에러: 인덱스가 범위를 벗어났습니다." << endl;
    }
    
    // 제곱근 계산 (음수 체크)
    cout << "\n=== 제곱근 계산 (음수 체크) ===" << endl;
    double number = 16.0;
    // number = -4.0;  // 잘못된 입력
    
    if (number < 0) {
        cout << "에러: 음수의 제곱근을 계산할 수 없습니다." << endl;
    } else {
        double sqrtValue = sqrt(number);
        cout << "sqrt(" << number << ") = " << sqrtValue << endl;
    }
    
    // 문자열 검증
    cout << "\n=== 문자열 검증 ===" << endl;
    string email = "user@example.com";
    // email = "invalid-email";  // 잘못된 형식
    
    if (email.find('@') == string::npos) {
        cout << "에러: 유효한 이메일 형식이 아닙니다." << endl;
    } else {
        cout << "유효한 이메일: " << email << endl;
    }
    
    // 메모리 할당 확인 (간단한 예제)
    cout << "\n=== 메모리 할당 확인 ===" << endl;
    int* ptr = new int[10];
    
    if (ptr == nullptr) {
        cout << "에러: 메모리 할당 실패" << endl;
    } else {
        cout << "메모리 할당 성공" << endl;
        delete[] ptr;
    }
    
    // 파일 열기 확인 (시뮬레이션)
    cout << "\n=== 파일 열기 확인 ===" << endl;
    bool fileOpened = true;  // 시뮬레이션
    
    if (!fileOpened) {
        cout << "에러: 파일을 열 수 없습니다." << endl;
    } else {
        cout << "파일 열기 성공" << endl;
    }
    
    // 실제 사용 예제 1: 계산기
    cout << "\n=== 실제 사용 예제 1: 계산기 ===" << endl;
    double num1 = 10.0, num2 = 0.0;
    char op = '/';
    double calcResult;
    bool error = false;
    
    switch (op) {
        case '+':
            calcResult = num1 + num2;
            break;
        case '-':
            calcResult = num1 - num2;
            break;
        case '*':
            calcResult = num1 * num2;
            break;
        case '/':
            if (num2 == 0.0) {
                cout << "에러: 0으로 나눌 수 없습니다." << endl;
                error = true;
            } else {
                calcResult = num1 / num2;
            }
            break;
        default:
            cout << "에러: 알 수 없는 연산자" << endl;
            error = true;
    }
    
    if (!error) {
        cout << num1 << " " << op << " " << num2 << " = " << calcResult << endl;
    }
    
    // 실제 사용 예제 2: 나이 검증
    cout << "\n=== 실제 사용 예제 2: 나이 검증 ===" << endl;
    int userAge = 25;
    string message;
    
    if (userAge < 0) {
        message = "에러: 나이는 음수일 수 없습니다.";
    } else if (userAge > 150) {
        message = "에러: 나이는 150을 초과할 수 없습니다.";
    } else if (userAge < 18) {
        message = "미성년자입니다.";
    } else {
        message = "성인입니다.";
    }
    
    cout << message << endl;
    
    // 실제 사용 예제 3: 범위 검증
    cout << "\n=== 실제 사용 예제 3: 범위 검증 ===" << endl;
    int score = 85;
    const int MIN_SCORE = 0;
    const int MAX_SCORE = 100;
    
    if (score < MIN_SCORE || score > MAX_SCORE) {
        cout << "에러: 점수는 " << MIN_SCORE << "~" << MAX_SCORE 
             << " 사이여야 합니다." << endl;
    } else {
        char grade;
        if (score >= 90) grade = 'A';
        else if (score >= 80) grade = 'B';
        else if (score >= 70) grade = 'C';
        else if (score >= 60) grade = 'D';
        else grade = 'F';
        
        cout << "점수: " << score << ", 등급: " << grade << endl;
    }
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 모든 사용자 입력은 검증해야 함" << endl;
    cout << "2. 배열 인덱스는 항상 범위 확인" << endl;
    cout << "3. 나눗셈 전에 0 체크 필수" << endl;
    cout << "4. 포인터 사용 전 nullptr 체크" << endl;
    cout << "5. 명확한 에러 메시지 제공" << endl;
    
    return 0;
}
