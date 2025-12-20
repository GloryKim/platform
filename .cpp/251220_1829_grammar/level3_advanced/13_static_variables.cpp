/*
 * 3단계 예제 13: 정적 변수 (Static Variables)
 * 
 * static 키워드는 변수의 생명주기와 스코프를 제어합니다.
 * 함수 내부에서도 프로그램 종료까지 유지됩니다.
 */

#include <iostream>
using namespace std;

// 함수 내부 정적 변수
void counter() {
    static int count = 0;  // 한 번만 초기화, 값 유지
    count++;
    cout << "호출 횟수: " << count << endl;
}

// 정적 변수로 ID 생성
int generateId() {
    static int nextId = 1;
    return nextId++;
}

// 정적 변수로 팩토리얼 캐싱
long long factorial(int n) {
    static long long cache[20] = {0};
    
    if (n <= 1) {
        return 1;
    }
    
    if (cache[n] != 0) {
        return cache[n];
    }
    
    cache[n] = n * factorial(n - 1);
    return cache[n];
}

// 전역 정적 변수
static int globalStatic = 100;  // 파일 내부에서만 접근 가능

int main() {
    // 함수 내부 정적 변수
    cout << "=== 함수 내부 정적 변수 ===" << endl;
    counter();
    counter();
    counter();
    
    // ID 생성
    cout << "\n=== ID 생성 ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "생성된 ID: " << generateId() << endl;
    }
    
    // 팩토리얼 캐싱
    cout << "\n=== 팩토리얼 캐싱 ===" << endl;
    cout << "5! = " << factorial(5) << endl;
    cout << "7! = " << factorial(7) << endl;
    cout << "5! = " << factorial(5) << " (캐시에서)" << endl;
    
    // 정적 변수 vs 자동 변수
    cout << "\n=== 정적 변수 vs 자동 변수 ===" << endl;
    for (int i = 0; i < 3; i++) {
        static int staticVar = 0;  // 한 번만 초기화
        int autoVar = 0;  // 매번 초기화
        
        staticVar++;
        autoVar++;
        
        cout << "staticVar: " << staticVar << ", autoVar: " << autoVar << endl;
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 싱글톤 패턴 (간단한 예제)
    class Singleton {
    private:
        static Singleton* instance;
        Singleton() {}
        
    public:
        static Singleton* getInstance() {
            if (instance == nullptr) {
                instance = new Singleton();
            }
            return instance;
        }
    };
    
    // 통계 수집
    void recordEvent(string event);
    recordEvent("로그인");
    recordEvent("페이지 조회");
    recordEvent("로그아웃");
    
    return 0;
}

// 싱글톤 인스턴스
Singleton* Singleton::instance = nullptr;

// 이벤트 기록
void recordEvent(string event) {
    static int eventCount = 0;
    eventCount++;
    cout << "이벤트 #" << eventCount << ": " << event << endl;
}
