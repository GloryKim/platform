/*
 * 2단계 예제 7: break와 continue
 * 
 * 루프 제어를 위한 break와 continue를 학습합니다.
 * break: 루프를 즉시 종료
 * continue: 현재 반복을 건너뛰고 다음 반복으로
 */

#include <iostream>
using namespace std;

int main() {
    // break 사용
    cout << "=== break 사용 ===" << endl;
    cout << "1부터 10까지 출력 (5에서 중단): ";
    for (int i = 1; i <= 10; i++) {
        if (i > 5) {
            break;  // 5보다 크면 루프 종료
        }
        cout << i << " ";
    }
    cout << endl;
    
    // continue 사용
    cout << "\n=== continue 사용 ===" << endl;
    cout << "1부터 10까지 출력 (홀수만): ";
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 짝수는 건너뛰기
        }
        cout << i << " ";
    }
    cout << endl;
    
    // break와 continue 함께 사용
    cout << "\n=== break와 continue 함께 사용 ===" << endl;
    cout << "1부터 20까지 출력 (3의 배수 건너뛰기, 15에서 중단): ";
    for (int i = 1; i <= 20; i++) {
        if (i > 15) {
            break;
        }
        if (i % 3 == 0) {
            continue;
        }
        cout << i << " ";
    }
    cout << endl;
    
    // while 루프에서 break
    cout << "\n=== while 루프에서 break ===" << endl;
    int num = 1;
    while (true) {
        if (num > 5) {
            break;
        }
        cout << num << " ";
        num++;
    }
    cout << endl;
    
    // 중첩 루프에서 break
    cout << "\n=== 중첩 루프에서 break ===" << endl;
    cout << "break는 가장 가까운 루프만 종료:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 3) {
                break;  // 내부 루프만 종료
            }
            cout << "(" << i << ", " << j << ") ";
        }
        cout << endl;
    }
    
    // 중첩 루프에서 continue
    cout << "\n=== 중첩 루프에서 continue ===" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 2) {
                continue;  // 내부 루프의 현재 반복만 건너뛰기
            }
            cout << "(" << i << ", " << j << ") ";
        }
        cout << endl;
    }
    
    // 실제 사용 예제 1: 숫자 찾기
    cout << "\n=== 실제 사용 예제 1: 숫자 찾기 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int target = 30;
    bool found = false;
    
    for (int i = 0; i < 5; i++) {
        if (arr[i] == target) {
            found = true;
            cout << target << "을(를) " << i << "번째 위치에서 찾았습니다." << endl;
            break;  // 찾으면 즉시 종료
        }
    }
    
    if (!found) {
        cout << target << "을(를) 찾을 수 없습니다." << endl;
    }
    
    // 실제 사용 예제 2: 소수 찾기
    cout << "\n=== 실제 사용 예제 2: 소수 찾기 ===" << endl;
    int number = 17;
    bool isPrime = true;
    
    if (number < 2) {
        isPrime = false;
    } else {
        for (int i = 2; i * i <= number; i++) {
            if (number % i == 0) {
                isPrime = false;
                break;  // 약수를 찾으면 즉시 종료
            }
        }
    }
    
    cout << number << "은(는) " << (isPrime ? "소수" : "합성수") << "입니다." << endl;
    
    // 실제 사용 예제 3: 입력 검증
    cout << "\n=== 실제 사용 예제 3: 입력 검증 ===" << endl;
    int validCount = 0;
    int invalidCount = 0;
    
    // 시뮬레이션: 여러 입력값
    int inputs[] = {5, -3, 10, 0, 7, -1, 15};
    
    for (int i = 0; i < 7; i++) {
        int input = inputs[i];
        
        if (input <= 0) {
            invalidCount++;
            continue;  // 유효하지 않은 입력은 건너뛰기
        }
        
        validCount++;
        cout << "유효한 입력: " << input << endl;
    }
    
    cout << "유효한 입력: " << validCount << "개" << endl;
    cout << "유효하지 않은 입력: " << invalidCount << "개" << endl;
    
    // 실제 사용 예제 4: 합계 계산 (특정 조건에서 중단)
    cout << "\n=== 실제 사용 예제 4: 합계 계산 ===" << endl;
    int sum = 0;
    int numbers[] = {5, 10, 15, -1, 20, 25};  // -1은 종료 신호
    
    for (int i = 0; i < 6; i++) {
        if (numbers[i] < 0) {
            break;  // 음수면 종료
        }
        sum += numbers[i];
    }
    
    cout << "합계: " << sum << endl;
    
    // 실제 사용 예제 5: 데이터 필터링
    cout << "\n=== 실제 사용 예제 5: 데이터 필터링 ===" << endl;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "2의 배수이면서 3의 배수는 아닌 수: ";
    
    for (int i = 0; i < 10; i++) {
        if (data[i] % 2 != 0) {
            continue;  // 홀수는 건너뛰기
        }
        if (data[i] % 3 == 0) {
            continue;  // 3의 배수는 건너뛰기
        }
        cout << data[i] << " ";
    }
    cout << endl;
    
    return 0;
}



