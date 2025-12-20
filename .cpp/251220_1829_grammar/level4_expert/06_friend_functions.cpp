/*
 * 4단계 예제 6: friend 함수
 * 
 * friend 함수는 클래스의 private/protected 멤버에 접근할 수 있는 특권을 가집니다.
 * 캡슐화를 유지하면서 특정 함수에 접근 권한을 부여합니다.
 */

#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // friend 함수 선언
    friend double distance(const Point& p1, const Point& p2);
    friend void display(const Point& p);
    friend class PointUtils;  // friend 클래스
    
    // 일반 멤버 함수
    int getX() const { return x; }
    int getY() const { return y; }
};

// friend 함수 정의
double distance(const Point& p1, const Point& p2) {
    // private 멤버에 직접 접근 가능
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

void display(const Point& p) {
    // private 멤버에 직접 접근 가능
    cout << "(" << p.x << ", " << p.y << ")" << endl;
}

// friend 클래스
class PointUtils {
public:
    static Point add(const Point& p1, const Point& p2) {
        // private 멤버에 접근 가능
        return Point(p1.x + p2.x, p1.y + p2.y);
    }
    
    static Point multiply(const Point& p, int scalar) {
        return Point(p.x * scalar, p.y * scalar);
    }
};

int main() {
    // friend 함수 사용
    cout << "=== friend 함수 사용 ===" << endl;
    Point p1(3, 4);
    Point p2(0, 0);
    
    display(p1);
    display(p2);
    cout << "거리: " << distance(p1, p2) << endl;
    
    // friend 클래스 사용
    cout << "\n=== friend 클래스 사용 ===" << endl;
    Point p3 = PointUtils::add(p1, p2);
    display(p3);
    
    Point p4 = PointUtils::multiply(p1, 2);
    display(p4);
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. friend는 캡슐화를 약화시킴" << endl;
    cout << "2. 필요한 경우에만 사용" << endl;
    cout << "3. 연산자 오버로딩에 유용" << endl;
    cout << "4. 클래스 간 밀접한 관계 표현" << endl;
    
    return 0;
}
