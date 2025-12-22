/*
 * 2단계 예제 2: switch 문
 * 
 * 여러 조건 중 하나를 선택하는 switch 문을 학습합니다.
 * if-else if 체인보다 가독성이 좋을 수 있습니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 switch 문
    cout << "=== 기본 switch 문 ===" << endl;
    int day = 3;
    
    switch (day) {
        case 1:
            cout << "월요일" << endl;
            break;
        case 2:
            cout << "화요일" << endl;
            break;
        case 3:
            cout << "수요일" << endl;
            break;
        case 4:
            cout << "목요일" << endl;
            break;
        case 5:
            cout << "금요일" << endl;
            break;
        case 6:
            cout << "토요일" << endl;
            break;
        case 7:
            cout << "일요일" << endl;
            break;
        default:
            cout << "잘못된 날짜" << endl;
            break;
    }
    
    // break 없는 경우 (fall-through)
    cout << "\n=== break 없는 경우 (fall-through) ===" << endl;
    int month = 2;
    
    switch (month) {
        case 12:
        case 1:
        case 2:
            cout << "겨울" << endl;
            break;
        case 3:
        case 4:
        case 5:
            cout << "봄" << endl;
            break;
        case 6:
        case 7:
        case 8:
            cout << "여름" << endl;
            break;
        case 9:
        case 10:
        case 11:
            cout << "가을" << endl;
            break;
        default:
            cout << "잘못된 월" << endl;
    }
    
    // 문자 switch
    cout << "\n=== 문자 switch ===" << endl;
    char grade = 'B';
    
    switch (grade) {
        case 'A':
        case 'a':
            cout << "우수" << endl;
            break;
        case 'B':
        case 'b':
            cout << "양호" << endl;
            break;
        case 'C':
        case 'c':
            cout << "보통" << endl;
            break;
        case 'D':
        case 'd':
            cout << "미흡" << endl;
            break;
        case 'F':
        case 'f':
            cout << "불합격" << endl;
            break;
        default:
            cout << "알 수 없는 등급" << endl;
    }
    
    // 계산기 예제
    cout << "\n=== 계산기 예제 ===" << endl;
    double num1 = 10, num2 = 5;
    char op = '+';
    double result;
    
    switch (op) {
        case '+':
            result = num1 + num2;
            cout << num1 << " + " << num2 << " = " << result << endl;
            break;
        case '-':
            result = num1 - num2;
            cout << num1 << " - " << num2 << " = " << result << endl;
            break;
        case '*':
            result = num1 * num2;
            cout << num1 << " * " << num2 << " = " << result << endl;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                cout << num1 << " / " << num2 << " = " << result << endl;
            } else {
                cout << "0으로 나눌 수 없습니다." << endl;
            }
            break;
        default:
            cout << "알 수 없는 연산자" << endl;
    }
    
    // 메뉴 선택 예제
    cout << "\n=== 메뉴 선택 예제 ===" << endl;
    int choice = 2;
    
    switch (choice) {
        case 1:
            cout << "1. 새 파일 생성" << endl;
            break;
        case 2:
            cout << "2. 파일 열기" << endl;
            break;
        case 3:
            cout << "3. 파일 저장" << endl;
            break;
        case 4:
            cout << "4. 파일 삭제" << endl;
            break;
        case 5:
            cout << "5. 종료" << endl;
            break;
        default:
            cout << "잘못된 선택" << endl;
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 방향 이동
    char direction = 'N';
    int x = 0, y = 0;
    
    switch (direction) {
        case 'N':
        case 'n':
            y++;
            cout << "북쪽으로 이동: (" << x << ", " << y << ")" << endl;
            break;
        case 'S':
        case 's':
            y--;
            cout << "남쪽으로 이동: (" << x << ", " << y << ")" << endl;
            break;
        case 'E':
        case 'e':
            x++;
            cout << "동쪽으로 이동: (" << x << ", " << y << ")" << endl;
            break;
        case 'W':
        case 'w':
            x--;
            cout << "서쪽으로 이동: (" << x << ", " << y << ")" << endl;
            break;
        default:
            cout << "알 수 없는 방향" << endl;
    }
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. switch는 정수형, 문자형, 열거형만 사용 가능" << endl;
    cout << "2. 각 case 끝에 break를 넣지 않으면 다음 case로 계속 실행됨" << endl;
    cout << "3. default는 선택사항이지만 권장됨" << endl;
    
    return 0;
}



