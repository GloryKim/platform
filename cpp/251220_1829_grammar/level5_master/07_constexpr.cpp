/*
 * 5단계 예제 7: constexpr
 * 
 * constexpr는 컴파일 타임에 평가되는 상수 표현식을 만듭니다.
 * 성능 향상과 타입 안전성을 제공합니다.
 */

#include <iostream>
using namespace std;

// constexpr 함수
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// constexpr 변수
constexpr int MAX_SIZE = 100;
constexpr double PI = 3.14159;

// constexpr 클래스
class Point {
private:
    int x, y;

public:
    constexpr Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    constexpr int getX() const { return x; }
    constexpr int getY() const { return y; }
    
    constexpr Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};

int main() {
    // constexpr 함수 사용
    cout << "=== constexpr 함수 사용 ===" << endl;
    constexpr int fact5 = factorial(5);
    cout << "5! = " << fact5 << endl;
    
    // constexpr 변수
    cout << "\n=== constexpr 변수 ===" << endl;
    cout << "MAX_SIZE: " << MAX_SIZE << endl;
    cout << "PI: " << PI << endl;
    
    // constexpr 객체
    cout << "\n=== constexpr 객체 ===" << endl;
    constexpr Point p1(3, 4);
    constexpr Point p2(1, 2);
    constexpr Point p3 = p1 + p2;
    
    cout << "p1: (" << p1.getX() << ", " << p1.getY() << ")" << endl;
    cout << "p2: (" << p2.getX() << ", " << p2.getY() << ")" << endl;
    cout << "p3: (" << p3.getX() << ", " << p3.getY() << ")" << endl;
    
    // 배열 크기
    cout << "\n=== 배열 크기 ===" << endl;
    int arr[fact5];  // 컴파일 타임에 크기 결정
    cout << "배열 크기: " << sizeof(arr) / sizeof(arr[0]) << endl;
    
    return 0;
}



