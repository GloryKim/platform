/*
 * 2단계 예제 1: if 문
 * 
 * 조건에 따라 코드를 실행하는 if 문을 학습합니다.
 * 가장 기본적인 제어문입니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 if 문
    cout << "=== 기본 if 문 ===" << endl;
    int age = 20;
    
    if (age >= 18) {
        cout << "성인입니다." << endl;
    }
    
    // if-else 문
    cout << "\n=== if-else 문 ===" << endl;
    int score = 85;
    
    if (score >= 60) {
        cout << "합격입니다." << endl;
    } else {
        cout << "불합격입니다." << endl;
    }
    
    // if-else if-else 문
    cout << "\n=== if-else if-else 문 ===" << endl;
    int temperature = 25;
    
    if (temperature > 30) {
        cout << "날씨가 매우 덥습니다." << endl;
    } else if (temperature > 20) {
        cout << "날씨가 따뜻합니다." << endl;
    } else if (temperature > 10) {
        cout << "날씨가 시원합니다." << endl;
    } else {
        cout << "날씨가 춥습니다." << endl;
    }
    
    // 중첩 if 문
    cout << "\n=== 중첩 if 문 ===" << endl;
    bool hasLicense = true;
    int driverAge = 25;
    
    if (hasLicense) {
        if (driverAge >= 18) {
            cout << "운전 가능합니다." << endl;
        } else {
            cout << "면허는 있지만 나이가 부족합니다." << endl;
        }
    } else {
        cout << "면허가 없습니다." << endl;
    }
    
    // 논리 연산자와 함께 사용
    cout << "\n=== 논리 연산자와 함께 사용 ===" << endl;
    int num = 15;
    
    if (num > 10 && num < 20) {
        cout << num << "은 10보다 크고 20보다 작습니다." << endl;
    }
    
    if (num < 5 || num > 25) {
        cout << num << "은 5보다 작거나 25보다 큽니다." << endl;
    } else {
        cout << num << "은 5와 25 사이에 있습니다." << endl;
    }
    
    // 삼항 연산자 (조건 연산자)
    cout << "\n=== 삼항 연산자 ===" << endl;
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    cout << "max(" << a << ", " << b << ") = " << max << endl;
    
    string result = (score >= 60) ? "합격" : "불합격";
    cout << "점수 " << score << "점: " << result << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 등급 판정
    int studentScore = 92;
    char grade;
    
    if (studentScore >= 90) {
        grade = 'A';
    } else if (studentScore >= 80) {
        grade = 'B';
    } else if (studentScore >= 70) {
        grade = 'C';
    } else if (studentScore >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }
    
    cout << "점수: " << studentScore << ", 등급: " << grade << endl;
    
    // 짝수/홀수 판별
    int number = 7;
    if (number % 2 == 0) {
        cout << number << "은(는) 짝수입니다." << endl;
    } else {
        cout << number << "은(는) 홀수입니다." << endl;
    }
    
    // 양수/음수/0 판별
    int value = -5;
    if (value > 0) {
        cout << value << "은(는) 양수입니다." << endl;
    } else if (value < 0) {
        cout << value << "은(는) 음수입니다." << endl;
    } else {
        cout << value << "은(는) 0입니다." << endl;
    }
    
    return 0;
}
