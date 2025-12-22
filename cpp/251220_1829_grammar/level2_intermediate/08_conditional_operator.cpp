/*
 * 2단계 예제 8: 조건 연산자 (삼항 연산자)
 * 
 * 조건에 따라 값을 선택하는 삼항 연산자 ? : 를 학습합니다.
 * 간단한 if-else를 한 줄로 표현할 수 있습니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 사용법
    cout << "=== 기본 사용법 ===" << endl;
    int a = 10, b = 20;
    
    // 조건 ? 값1 : 값2
    // 조건이 true면 값1, false면 값2
    int max = (a > b) ? a : b;
    cout << "max(" << a << ", " << b << ") = " << max << endl;
    
    int min = (a < b) ? a : b;
    cout << "min(" << a << ", " << b << ") = " << min << endl;
    
    // 문자열 선택
    cout << "\n=== 문자열 선택 ===" << endl;
    int score = 85;
    string result = (score >= 60) ? "합격" : "불합격";
    cout << "점수 " << score << "점: " << result << endl;
    
    // 짝수/홀수 판별
    cout << "\n=== 짝수/홀수 판별 ===" << endl;
    int num = 7;
    string parity = (num % 2 == 0) ? "짝수" : "홀수";
    cout << num << "은(는) " << parity << "입니다." << endl;
    
    // 양수/음수/0 판별
    cout << "\n=== 양수/음수/0 판별 ===" << endl;
    int value = -5;
    string sign = (value > 0) ? "양수" : (value < 0) ? "음수" : "0";
    cout << value << "은(는) " << sign << "입니다." << endl;
    
    // 중첩 삼항 연산자
    cout << "\n=== 중첩 삼항 연산자 ===" << endl;
    int age = 25;
    string category = (age < 18) ? "미성년자" : (age < 65) ? "성인" : "노인";
    cout << "나이 " << age << "세: " << category << endl;
    
    // 등급 판정
    cout << "\n=== 등급 판정 ===" << endl;
    int studentScore = 92;
    char grade = (studentScore >= 90) ? 'A' : 
                 (studentScore >= 80) ? 'B' : 
                 (studentScore >= 70) ? 'C' : 
                 (studentScore >= 60) ? 'D' : 'F';
    cout << "점수 " << studentScore << "점: 등급 " << grade << endl;
    
    // 절댓값 계산
    cout << "\n=== 절댓값 계산 ===" << endl;
    int x = -10;
    int absValue = (x >= 0) ? x : -x;
    cout << "|" << x << "| = " << absValue << endl;
    
    // 변수에 할당
    cout << "\n=== 변수에 할당 ===" << endl;
    int num1 = 5, num2 = 3;
    int larger = (num1 > num2) ? num1 : num2;
    int smaller = (num1 < num2) ? num1 : num2;
    cout << "더 큰 수: " << larger << ", 더 작은 수: " << smaller << endl;
    
    // 출력에 직접 사용
    cout << "\n=== 출력에 직접 사용 ===" << endl;
    bool isEven = true;
    cout << "숫자는 " << (isEven ? "짝수" : "홀수") << "입니다." << endl;
    
    // 함수 인자로 사용
    cout << "\n=== 함수 인자로 사용 ===" << endl;
    int val1 = 10, val2 = 20;
    cout << "더 큰 값: " << ((val1 > val2) ? val1 : val2) << endl;
    
    // 실제 사용 예제 1: 최대값 찾기
    cout << "\n=== 실제 사용 예제 1: 최대값 찾기 ===" << endl;
    int arr[] = {10, 5, 20, 15, 8};
    int maxVal = arr[0];
    
    for (int i = 1; i < 5; i++) {
        maxVal = (arr[i] > maxVal) ? arr[i] : maxVal;
    }
    cout << "최대값: " << maxVal << endl;
    
    // 실제 사용 예제 2: 문자열 포맷팅
    cout << "\n=== 실제 사용 예제 2: 문자열 포맷팅 ===" << endl;
    int count = 1;
    cout << count << "개의 " << (count == 1 ? "아이템" : "아이템들") << endl;
    
    count = 5;
    cout << count << "개의 " << (count == 1 ? "아이템" : "아이템들") << endl;
    
    // 실제 사용 예제 3: 상태 표시
    cout << "\n=== 실제 사용 예제 3: 상태 표시 ===" << endl;
    bool isOnline = true;
    string status = isOnline ? "온라인" : "오프라인";
    cout << "상태: " << status << endl;
    
    // 실제 사용 예제 4: 할인 계산
    cout << "\n=== 실제 사용 예제 4: 할인 계산 ===" << endl;
    double price = 100.0;
    bool isMember = true;
    double discount = isMember ? 0.1 : 0.0;  // 회원 10% 할인
    double finalPrice = price * (1 - discount);
    cout << "원가: " << price << "원" << endl;
    cout << "할인율: " << (discount * 100) << "%" << endl;
    cout << "최종 가격: " << finalPrice << "원" << endl;
    
    // 실제 사용 예제 5: 배열 인덱스 선택
    cout << "\n=== 실제 사용 예제 5: 배열 인덱스 선택 ===" << endl;
    int index1 = 2, index2 = 4;
    int arr2[] = {10, 20, 30, 40, 50};
    int selected = (index1 < index2) ? arr2[index1] : arr2[index2];
    cout << "선택된 값: " << selected << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 삼항 연산자는 간단한 조건에만 사용" << endl;
    cout << "2. 복잡한 로직은 if-else가 더 읽기 쉬움" << endl;
    cout << "3. 중첩 삼항 연산자는 가독성이 떨어질 수 있음" << endl;
    cout << "4. 타입이 일치해야 함 (자동 변환 가능한 경우 제외)" << endl;
    
    return 0;
}



