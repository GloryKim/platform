/*
 * 2단계 예제 17: 전처리기 (Preprocessor)
 * 
 * 전처리기는 컴파일 전에 코드를 처리합니다.
 * #include, #define, #ifdef 등을 사용합니다.
 */

#include <iostream>
using namespace std;

// 매크로 정의
#define PI 3.14159
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))

// 조건부 컴파일
#define DEBUG_MODE

int main() {
    // 매크로 상수 사용
    cout << "=== 매크로 상수 사용 ===" << endl;
    cout << "PI = " << PI << endl;
    
    double radius = 5.0;
    double area = PI * radius * radius;
    cout << "반지름 " << radius << "인 원의 넓이: " << area << endl;
    
    // 매크로 함수 사용
    cout << "\n=== 매크로 함수 사용 ===" << endl;
    int a = 10, b = 20;
    cout << "MAX(" << a << ", " << b << ") = " << MAX(a, b) << endl;
    cout << "SQUARE(5) = " << SQUARE(5) << endl;
    cout << "SQUARE(3 + 2) = " << SQUARE(3 + 2) << endl;
    
    // 조건부 컴파일
    cout << "\n=== 조건부 컴파일 ===" << endl;
    #ifdef DEBUG_MODE
        cout << "디버그 모드 활성화" << endl;
    #else
        cout << "디버그 모드 비활성화" << endl;
    #endif
    
    #ifndef RELEASE_MODE
        cout << "릴리즈 모드가 아님" << endl;
    #endif
    
    // 매크로 취소
    #undef DEBUG_MODE
    
    #ifdef DEBUG_MODE
        cout << "이 메시지는 출력되지 않음" << endl;
    #else
        cout << "DEBUG_MODE가 정의되지 않음" << endl;
    #endif
    
    // 실제 사용 예제 1: 버전 정보
    cout << "\n=== 실제 사용 예제 1: 버전 정보 ===" << endl;
    #define VERSION_MAJOR 1
    #define VERSION_MINOR 0
    #define VERSION_PATCH 0
    
    cout << "버전: " << VERSION_MAJOR << "." 
         << VERSION_MINOR << "." << VERSION_PATCH << endl;
    
    // 실제 사용 예제 2: 플랫폼별 코드
    cout << "\n=== 실제 사용 예제 2: 플랫폼별 코드 ===" << endl;
    #ifdef _WIN32
        cout << "Windows 플랫폼" << endl;
    #elif __linux__
        cout << "Linux 플랫폼" << endl;
    #elif __APPLE__
        cout << "macOS 플랫폼" << endl;
    #else
        cout << "알 수 없는 플랫폼" << endl;
    #endif
    
    // 실제 사용 예제 3: 디버그 출력
    cout << "\n=== 실제 사용 예제 3: 디버그 출력 ===" << endl;
    #define DEBUG_PRINT(x) cout << "DEBUG: " << x << endl
    
    int value = 42;
    DEBUG_PRINT("변수 값: " << value);
    
    // 실제 사용 예제 4: 배열 크기
    cout << "\n=== 실제 사용 예제 4: 배열 크기 ===" << endl;
    #define ARRAY_SIZE 10
    int numbers[ARRAY_SIZE];
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = i * 2;
    }
    
    cout << "배열 요소: ";
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 매크로는 단순 텍스트 치환이므로 괄호 사용에 주의" << endl;
    cout << "2. 매크로 함수는 타입 안전성이 없음" << endl;
    cout << "3. 인라인 함수나 const 변수를 사용하는 것이 더 안전" << endl;
    cout << "4. 매크로 이름은 대문자로 작성하는 것이 관례" << endl;
    
    return 0;
}
