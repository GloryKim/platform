/*
 * 2단계 예제 3: for 루프
 * 
 * 반복 실행을 위한 for 루프를 학습합니다.
 * 반복 횟수를 알고 있을 때 주로 사용합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 for 루프
    cout << "=== 기본 for 루프 ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // 1부터 시작하는 루프
    cout << "\n=== 1부터 시작하는 루프 ===" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // 역순 루프
    cout << "\n=== 역순 루프 ===" << endl;
    for (int i = 5; i >= 1; i--) {
        cout << i << " ";
    }
    cout << endl;
    
    // 2씩 증가하는 루프
    cout << "\n=== 2씩 증가하는 루프 ===" << endl;
    for (int i = 0; i < 10; i += 2) {
        cout << i << " ";
    }
    cout << endl;
    
    // 중첩 for 루프
    cout << "\n=== 중첩 for 루프 (구구단) ===" << endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << i << " x " << j << " = " << (i * j) << "\t";
        }
        cout << endl;
    }
    
    // 별 찍기
    cout << "\n=== 별 찍기 ===" << endl;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    
    // 배열 순회
    cout << "\n=== 배열 순회 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "배열 요소: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 범위 기반 for 루프 (C++11)
    cout << "\n=== 범위 기반 for 루프 (C++11) ===" << endl;
    int numbers[] = {1, 2, 3, 4, 5};
    
    cout << "배열 요소: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 합계 계산
    cout << "\n=== 합계 계산 ===" << endl;
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
    cout << "1부터 10까지의 합: " << sum << endl;
    
    // 팩토리얼 계산
    cout << "\n=== 팩토리얼 계산 ===" << endl;
    int n = 5;
    long long factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    cout << n << "! = " << factorial << endl;
    
    // continue 사용
    cout << "\n=== continue 사용 (짝수만 출력) ===" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 != 0) {
            continue;  // 홀수는 건너뛰기
        }
        cout << i << " ";
    }
    cout << endl;
    
    // break 사용
    cout << "\n=== break 사용 (5에서 중단) ===" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i > 5) {
            break;  // 5보다 크면 루프 종료
        }
        cout << i << " ";
    }
    cout << endl;
    
    // 무한 루프 (조건부 break)
    cout << "\n=== 무한 루프 (조건부 break) ===" << endl;
    int count = 0;
    for (;;) {
        count++;
        if (count > 5) {
            break;
        }
        cout << count << " ";
    }
    cout << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 최대값 찾기
    int scores[] = {85, 92, 78, 96, 88};
    int maxScore = scores[0];
    for (int i = 1; i < 5; i++) {
        if (scores[i] > maxScore) {
            maxScore = scores[i];
        }
    }
    cout << "최대 점수: " << maxScore << endl;
    
    // 평균 계산
    double total = 0;
    for (int i = 0; i < 5; i++) {
        total += scores[i];
    }
    double average = total / 5;
    cout << "평균 점수: " << average << endl;
    
    // 소수 찾기
    cout << "\n1부터 20까지의 소수: ";
    for (int num = 2; num <= 20; num++) {
        bool isPrime = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << num << " ";
        }
    }
    cout << endl;
    
    return 0;
}


