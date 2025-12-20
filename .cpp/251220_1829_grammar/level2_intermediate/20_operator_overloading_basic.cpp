/*
 * 2단계 예제 20: 연산자 오버로딩 기초
 * 
 * 사용자 정의 타입에 대해 연산자를 재정의하는 기본 개념을 학습합니다.
 * 간단한 예제로 개념을 이해합니다.
 */

#include <iostream>
using namespace std;

// 간단한 Point 클래스
class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // 좌표 출력
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
    
    // 덧셈 연산자 오버로딩
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    // 뺄셈 연산자 오버로딩
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    // 곱셈 연산자 오버로딩 (스칼라 곱)
    Point operator*(int scalar) const {
        return Point(x * scalar, y * scalar);
    }
    
    // 비교 연산자 오버로딩
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    // 복합 할당 연산자
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    // 출력 연산자 오버로딩 (friend 함수)
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    // 기본 사용
    cout << "=== 기본 사용 ===" << endl;
    Point p1(1, 2);
    Point p2(3, 4);
    
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    
    // 덧셈 연산
    cout << "\n=== 덧셈 연산 ===" << endl;
    Point p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;
    
    // 뺄셈 연산
    cout << "\n=== 뺄셈 연산 ===" << endl;
    Point p4 = p2 - p1;
    cout << "p2 - p1 = " << p4 << endl;
    
    // 스칼라 곱
    cout << "\n=== 스칼라 곱 ===" << endl;
    Point p5 = p1 * 3;
    cout << "p1 * 3 = " << p5 << endl;
    
    // 비교 연산
    cout << "\n=== 비교 연산 ===" << endl;
    Point p6(1, 2);
    cout << "p1 == p6: " << (p1 == p6) << endl;
    cout << "p1 != p2: " << (p1 != p2) << endl;
    
    // 복합 할당
    cout << "\n=== 복합 할당 ===" << endl;
    Point p7(10, 20);
    p7 += p1;
    cout << "p7 += p1 후: " << p7 << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 두 점 사이의 벡터 계산
    Point start(0, 0);
    Point end(5, 5);
    Point vector = end - start;
    cout << "시작점: " << start << ", 끝점: " << end << endl;
    cout << "벡터: " << vector << endl;
    
    // 점 이동
    Point position(10, 10);
    Point movement(2, 3);
    position += movement;
    cout << "이동 후 위치: " << position << endl;
    
    // 스케일링
    Point point(2, 3);
    Point scaled = point * 2;
    cout << "원본: " << point << ", 2배: " << scaled << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 연산자 오버로딩은 직관적으로 사용해야 함" << endl;
    cout << "2. 기존 의미를 크게 벗어나지 않아야 함" << endl;
    cout << "3. 일관성 있게 구현해야 함" << endl;
    cout << "4. 모든 연산자를 오버로딩할 필요는 없음" << endl;
    
    return 0;
}
