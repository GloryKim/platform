/*
 * 2단계 예제 4: while 루프
 * 
 * 조건이 참인 동안 반복 실행하는 while 루프를 학습합니다.
 * 반복 횟수를 모를 때 주로 사용합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 while 루프
    cout << "=== 기본 while 루프 ===" << endl;
    int i = 0;
    while (i < 5) {
        cout << i << " ";
        i++;
    }
    cout << endl;
    
    // 카운트다운
    cout << "\n=== 카운트다운 ===" << endl;
    int count = 5;
    while (count > 0) {
        cout << count << " ";
        count--;
    }
    cout << "발사!" << endl;
    
    // 합계 계산
    cout << "\n=== 합계 계산 ===" << endl;
    int sum = 0;
    int num = 1;
    while (num <= 10) {
        sum += num;
        num++;
    }
    cout << "1부터 10까지의 합: " << sum << endl;
    
    // 사용자 입력 받기 (시뮬레이션)
    cout << "\n=== 사용자 입력 받기 (시뮬레이션) ===" << endl;
    int input = 0;
    int attempts = 0;
    
    // 올바른 입력(1~10)을 받을 때까지 반복
    while (input < 1 || input > 10) {
        attempts++;
        // 시뮬레이션: 실제로는 cin >> input;
        input = (attempts == 3) ? 5 : 0;  // 3번째 시도에서 5 입력
        if (input < 1 || input > 10) {
            cout << "잘못된 입력입니다. 1~10 사이의 숫자를 입력하세요." << endl;
        }
    }
    cout << "올바른 입력: " << input << endl;
    
    // break 사용
    cout << "\n=== break 사용 ===" << endl;
    int j = 0;
    while (true) {  // 무한 루프
        j++;
        if (j > 5) {
            break;  // 조건 만족 시 루프 종료
        }
        cout << j << " ";
    }
    cout << endl;
    
    // continue 사용
    cout << "\n=== continue 사용 (홀수 건너뛰기) ===" << endl;
    int k = 0;
    while (k < 10) {
        k++;
        if (k % 2 == 1) {
            continue;  // 홀수는 건너뛰기
        }
        cout << k << " ";
    }
    cout << endl;
    
    // 숫자 자릿수 세기
    cout << "\n=== 숫자 자릿수 세기 ===" << endl;
    int number = 12345;
    int digits = 0;
    int temp = number;
    
    while (temp != 0) {
        digits++;
        temp /= 10;
    }
    cout << number << "의 자릿수: " << digits << endl;
    
    // 숫자 뒤집기
    cout << "\n=== 숫자 뒤집기 ===" << endl;
    int original = 12345;
    int reversed = 0;
    temp = original;
    
    while (temp != 0) {
        reversed = reversed * 10 + temp % 10;
        temp /= 10;
    }
    cout << original << " -> " << reversed << endl;
    
    // 피보나치 수열
    cout << "\n=== 피보나치 수열 (처음 10개) ===" << endl;
    int a = 0, b = 1;
    int fibCount = 0;
    
    cout << a << " " << b << " ";
    while (fibCount < 8) {
        int next = a + b;
        cout << next << " ";
        a = b;
        b = next;
        fibCount++;
    }
    cout << endl;
    
    // 최대공약수 (GCD) 구하기
    cout << "\n=== 최대공약수 (GCD) 구하기 ===" << endl;
    int num1 = 48, num2 = 18;
    int gcd1 = num1, gcd2 = num2;
    
    while (gcd2 != 0) {
        int temp = gcd2;
        gcd2 = gcd1 % gcd2;
        gcd1 = temp;
    }
    cout << "GCD(" << num1 << ", " << num2 << ") = " << gcd1 << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 메뉴 반복
    int choice = 0;
    int menuCount = 0;
    
    while (choice != 5 && menuCount < 3) {  // 5번 선택하거나 3번 반복하면 종료
        menuCount++;
        // 시뮬레이션: 실제로는 cin >> choice;
        choice = (menuCount == 1) ? 1 : (menuCount == 2) ? 2 : 5;
        
        switch (choice) {
            case 1:
                cout << "메뉴 1 선택" << endl;
                break;
            case 2:
                cout << "메뉴 2 선택" << endl;
                break;
            case 3:
                cout << "메뉴 3 선택" << endl;
                break;
            case 4:
                cout << "메뉴 4 선택" << endl;
                break;
            case 5:
                cout << "종료" << endl;
                break;
        }
    }
    
    // 무한 루프 주의사항
    cout << "\n=== 무한 루프 주의사항 ===" << endl;
    cout << "1. 조건이 항상 true가 되지 않도록 주의" << endl;
    cout << "2. 루프 내에서 조건을 변경하는 변수를 수정해야 함" << endl;
    cout << "3. break나 return으로 종료 조건을 명확히 해야 함" << endl;
    
    return 0;
}



