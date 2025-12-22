/*
 * 1단계 예제 19: 열거형 (Enum)
 * 
 * 열거형은 관련된 상수들을 그룹화하는 방법입니다.
 * 코드의 가독성을 높이고 오류를 줄일 수 있습니다.
 */

#include <iostream>
using namespace std;

// 기본 열거형
enum Color {
    RED,      // 0
    GREEN,    // 1
    BLUE      // 2
};

// 값 지정 열거형
enum Day {
    MONDAY = 1,
    TUESDAY = 2,
    WEDNESDAY = 3,
    THURSDAY = 4,
    FRIDAY = 5,
    SATURDAY = 6,
    SUNDAY = 7
};

// C++11 스타일 enum class (권장)
enum class Status {
    PENDING,
    APPROVED,
    REJECTED
};

enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

int main() {
    // 기본 열거형 사용
    cout << "=== 기본 열거형 ===" << endl;
    Color favoriteColor = RED;
    cout << "좋아하는 색: " << favoriteColor << endl;  // 0 출력
    
    Color currentColor = GREEN;
    if (currentColor == GREEN) {
        cout << "현재 색은 초록색입니다." << endl;
    }
    
    // 열거형 값 확인
    cout << "\n색상 값:" << endl;
    cout << "RED = " << RED << endl;
    cout << "GREEN = " << GREEN << endl;
    cout << "BLUE = " << BLUE << endl;
    
    // switch 문과 함께 사용
    cout << "\n=== switch 문과 함께 사용 ===" << endl;
    Day today = WEDNESDAY;
    switch (today) {
        case MONDAY:
            cout << "월요일입니다." << endl;
            break;
        case TUESDAY:
            cout << "화요일입니다." << endl;
            break;
        case WEDNESDAY:
            cout << "수요일입니다." << endl;
            break;
        case THURSDAY:
            cout << "목요일입니다." << endl;
            break;
        case FRIDAY:
            cout << "금요일입니다." << endl;
            break;
        case SATURDAY:
            cout << "토요일입니다." << endl;
            break;
        case SUNDAY:
            cout << "일요일입니다." << endl;
            break;
    }
    
    // enum class 사용 (C++11, 권장)
    cout << "\n=== enum class (권장) ===" << endl;
    Status orderStatus = Status::PENDING;
    
    // enum class는 타입 안전성 제공
    if (orderStatus == Status::PENDING) {
        cout << "주문 대기 중입니다." << endl;
    }
    
    // enum class는 직접 정수로 변환되지 않음
    // cout << orderStatus;  // 에러! 명시적 변환 필요
    cout << "상태 값: " << (int)orderStatus << endl;
    
    Priority taskPriority = Priority::HIGH;
    cout << "우선순위 값: " << (int)taskPriority << endl;
    
    // enum class의 장점: 이름 공간 분리
    enum class Color2 { RED, GREEN, BLUE };
    // Color::RED와 Color2::RED는 다른 타입 (충돌 없음)
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 게임 상태 관리
    enum class GameState {
        MENU,
        PLAYING,
        PAUSED,
        GAME_OVER
    };
    
    GameState currentState = GameState::MENU;
    
    switch (currentState) {
        case GameState::MENU:
            cout << "메뉴 화면" << endl;
            break;
        case GameState::PLAYING:
            cout << "게임 중" << endl;
            break;
        case GameState::PAUSED:
            cout << "일시 정지" << endl;
            break;
        case GameState::GAME_OVER:
            cout << "게임 오버" << endl;
            break;
    }
    
    // 방향 열거형
    enum class Direction {
        NORTH = 0,
        EAST = 1,
        SOUTH = 2,
        WEST = 3
    };
    
    Direction playerDirection = Direction::NORTH;
    cout << "\n플레이어 방향: " << (int)playerDirection << " (북쪽)" << endl;
    
    // 열거형을 배열 인덱스로 사용
    string directionNames[] = {"북", "동", "남", "서"};
    cout << "방향 이름: " << directionNames[(int)playerDirection] << endl;
    
    return 0;
}
