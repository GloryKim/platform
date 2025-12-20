/*
 * 2단계 예제 5: do-while 루프
 * 
 * do-while 루프는 조건을 확인하기 전에 최소 한 번은 실행됩니다.
 * while과의 차이점을 학습합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 do-while 루프
    cout << "=== 기본 do-while 루프 ===" << endl;
    int i = 0;
    do {
        cout << i << " ";
        i++;
    } while (i < 5);
    cout << endl;
    
    // while vs do-while 차이점
    cout << "\n=== while vs do-while 차이점 ===" << endl;
    
    // while: 조건이 false면 실행 안 됨
    int count1 = 10;
    cout << "while 루프 (조건 false): ";
    while (count1 < 5) {
        cout << count1 << " ";  // 실행 안 됨
        count1++;
    }
    cout << "실행 안 됨" << endl;
    
    // do-while: 최소 한 번은 실행됨
    int count2 = 10;
    cout << "do-while 루프 (조건 false): ";
    do {
        cout << count2 << " ";  // 한 번 실행됨
        count2++;
    } while (count2 < 5);
    cout << endl;
    
    // 메뉴 선택 예제
    cout << "\n=== 메뉴 선택 예제 ===" << endl;
    int choice;
    int menuCount = 0;
    
    do {
        menuCount++;
        // 시뮬레이션: 실제로는 cin >> choice;
        choice = (menuCount == 1) ? 1 : (menuCount == 2) ? 2 : 4;
        
        switch (choice) {
            case 1:
                cout << "1. 파일 열기" << endl;
                break;
            case 2:
                cout << "2. 파일 저장" << endl;
                break;
            case 3:
                cout << "3. 파일 삭제" << endl;
                break;
            case 4:
                cout << "4. 종료" << endl;
                break;
        }
    } while (choice != 4);
    
    // 사용자 입력 검증
    cout << "\n=== 사용자 입력 검증 ===" << endl;
    int number;
    int attempt = 0;
    
    do {
        attempt++;
        // 시뮬레이션: 실제로는 cin >> number;
        number = (attempt == 1) ? 0 : (attempt == 2) ? -5 : 10;
        
        if (number <= 0) {
            cout << "양수를 입력하세요. (시도 " << attempt << ")" << endl;
        }
    } while (number <= 0);
    
    cout << "올바른 입력: " << number << endl;
    
    // 합계 계산 (최소 한 번 실행)
    cout << "\n=== 합계 계산 ===" << endl;
    int sum = 0;
    int value = 1;
    
    do {
        sum += value;
        value++;
    } while (value <= 5);
    
    cout << "1부터 5까지의 합: " << sum << endl;
    
    // 숫자 자릿수 세기
    cout << "\n=== 숫자 자릿수 세기 ===" << endl;
    int num = 12345;
    int digits = 0;
    int temp = num;
    
    do {
        digits++;
        temp /= 10;
    } while (temp != 0);
    
    cout << num << "의 자릿수: " << digits << endl;
    
    // 팩토리얼 계산
    cout << "\n=== 팩토리얼 계산 ===" << endl;
    int n = 5;
    long long factorial = 1;
    int factCount = 1;
    
    do {
        factorial *= factCount;
        factCount++;
    } while (factCount <= n);
    
    cout << n << "! = " << factorial << endl;
    
    // break와 continue 사용
    cout << "\n=== break와 continue 사용 ===" << endl;
    int j = 0;
    do {
        j++;
        if (j == 3) {
            continue;  // 3은 건너뛰기
        }
        if (j > 5) {
            break;  // 5보다 크면 종료
        }
        cout << j << " ";
    } while (j < 10);
    cout << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 게임 루프
    bool gameOver = false;
    int round = 0;
    
    do {
        round++;
        cout << "라운드 " << round << " 진행 중..." << endl;
        
        // 시뮬레이션: 게임 로직
        if (round >= 3) {
            gameOver = true;
            cout << "게임 종료!" << endl;
        }
    } while (!gameOver);
    
    // 암호 입력 (최소 한 번은 입력받음)
    cout << "\n=== 암호 입력 시뮬레이션 ===" << endl;
    string password;
    bool correct = false;
    int tries = 0;
    
    do {
        tries++;
        // 시뮬레이션: 실제로는 cin >> password;
        password = (tries == 1) ? "wrong" : "correct";
        
        if (password == "correct") {
            correct = true;
            cout << "암호가 맞습니다!" << endl;
        } else {
            cout << "암호가 틀렸습니다. 다시 시도하세요." << endl;
        }
    } while (!correct && tries < 3);
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. do-while은 최소 한 번은 실행됨" << endl;
    cout << "2. 조건이 false여도 한 번은 실행됨" << endl;
    cout << "3. 사용자 입력 검증에 유용함" << endl;
    cout << "4. 무한 루프에 빠지지 않도록 주의" << endl;
    
    return 0;
}
