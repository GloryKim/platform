/*
 * 2단계 예제 9: goto 문
 * 
 * goto 문은 프로그램의 흐름을 레이블로 점프시킵니다.
 * 일반적으로 권장되지 않지만 특정 상황에서 유용할 수 있습니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 goto 사용
    cout << "=== 기본 goto 사용 ===" << endl;
    int i = 0;
    
start:
    cout << i << " ";
    i++;
    if (i < 5) {
        goto start;  // start 레이블로 점프
    }
    cout << endl;
    
    // 루프 탈출에 사용
    cout << "\n=== 루프 탈출에 사용 ===" << endl;
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 5; k++) {
            if (k == 3) {
                goto outer_break;  // 외부 루프까지 탈출
            }
            cout << "(" << j << ", " << k << ") ";
        }
    }
outer_break:
    cout << "\n외부 루프 탈출 완료" << endl;
    
    // 에러 처리에 사용
    cout << "\n=== 에러 처리에 사용 ===" << endl;
    int value = 10;
    
    if (value < 0) {
        goto error_handler;
    }
    
    if (value > 100) {
        goto error_handler;
    }
    
    cout << "정상 처리: " << value << endl;
    goto end;
    
error_handler:
    cout << "에러: 값이 범위를 벗어났습니다." << endl;
    
end:
    cout << "프로그램 종료" << endl;
    
    // 중첩 루프에서의 사용
    cout << "\n=== 중첩 루프에서의 사용 ===" << endl;
    int x = 0, y = 0;
    
loop:
    cout << "(" << x << ", " << y << ") ";
    y++;
    if (y < 3) {
        goto loop;
    }
    y = 0;
    x++;
    if (x < 3) {
        goto loop;
    }
    cout << endl;
    
    // 실제 사용 예제 1: 입력 검증
    cout << "\n=== 실제 사용 예제 1: 입력 검증 ===" << endl;
    int input = 5;  // 시뮬레이션
    
    // 입력 검증
    if (input < 1) {
        goto invalid_input;
    }
    if (input > 10) {
        goto invalid_input;
    }
    
    cout << "유효한 입력: " << input << endl;
    goto valid_end;
    
invalid_input:
    cout << "잘못된 입력입니다." << endl;
    
valid_end:
    // 계속 진행
    
    // 실제 사용 예제 2: 상태 머신 (간단한 예제)
    cout << "\n=== 실제 사용 예제 2: 상태 머신 ===" << endl;
    int state = 0;
    
state0:
    cout << "상태 0" << endl;
    state = 1;
    goto state1;
    
state1:
    cout << "상태 1" << endl;
    state = 2;
    goto state2;
    
state2:
    cout << "상태 2" << endl;
    goto end_state;
    
end_state:
    cout << "상태 머신 종료" << endl;
    
    // 주의사항 및 권장사항
    cout << "\n=== 주의사항 및 권장사항 ===" << endl;
    cout << "1. goto는 일반적으로 권장되지 않음" << endl;
    cout << "2. 코드 가독성을 해칠 수 있음" << endl;
    cout << "3. 대부분의 경우 break, continue, 함수로 대체 가능" << endl;
    cout << "4. 에러 처리나 중첩 루프 탈출에만 제한적으로 사용" << endl;
    cout << "5. 레이블은 사용 전에 선언되어야 함" << endl;
    
    // goto 대신 사용할 수 있는 방법
    cout << "\n=== goto 대신 사용할 수 있는 방법 ===" << endl;
    
    // 방법 1: break 사용
    cout << "방법 1: break 사용" << endl;
    bool found = false;
    for (int i = 0; i < 3 && !found; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 3) {
                found = true;
                break;
            }
            cout << "(" << i << ", " << j << ") ";
        }
    }
    cout << endl;
    
    // 방법 2: 함수 사용
    cout << "방법 2: 함수 사용" << endl;
    auto processData = []() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (j == 3) {
                    return;  // 함수 종료로 루프 탈출
                }
                cout << "(" << i << ", " << j << ") ";
            }
        }
    };
    processData();
    cout << endl;
    
    return 0;
}
