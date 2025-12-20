/*
 * 4단계 예제 7: 연산자 오버로딩
 * 
 * 연산자를 사용자 정의 타입에 대해 재정의할 수 있습니다.
 * 직관적이고 자연스러운 코드를 작성할 수 있습니다.
 */

#include <iostream>
using namespace std;

class Vector {
private:
    double x, y;

public:
    Vector(double x = 0, double y = 0) : x(x), y(y) {}
    
    // 산술 연산자
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }
    
    Vector operator*(double scalar) const {
        return Vector(x * scalar, y * scalar);
    }
    
    // 복합 할당 연산자
    Vector& operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector& operator-=(const Vector& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    // 비교 연산자
    bool operator==(const Vector& other) const {
        return (x == other.x && y == other.y);
    }
    
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    
    // 증감 연산자
    Vector& operator++() {  // 전위
        x++;
        y++;
        return *this;
    }
    
    Vector operator++(int) {  // 후위
        Vector temp = *this;
        ++(*this);
        return temp;
    }
    
    // 출력 연산자 (friend)
    friend ostream& operator<<(ostream& os, const Vector& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
    
    // 입력 연산자 (friend)
    friend istream& operator>>(istream& is, Vector& v) {
        is >> v.x >> v.y;
        return is;
    }
    
    // 인덱스 연산자
    double operator[](int index) const {
        return (index == 0) ? x : y;
    }
    
    double& operator[](int index) {
        return (index == 0) ? x : y;
    }
};

int main() {
    // 산술 연산자
    cout << "=== 산술 연산자 ===" << endl;
    Vector v1(3, 4);
    Vector v2(1, 2);
    
    Vector v3 = v1 + v2;
    cout << "v1 + v2 = " << v3 << endl;
    
    Vector v4 = v1 - v2;
    cout << "v1 - v2 = " << v4 << endl;
    
    Vector v5 = v1 * 2;
    cout << "v1 * 2 = " << v5 << endl;
    
    // 복합 할당
    cout << "\n=== 복합 할당 ===" << endl;
    Vector v6(5, 6);
    v6 += v1;
    cout << "v6 += v1: " << v6 << endl;
    
    // 비교 연산자
    cout << "\n=== 비교 연산자 ===" << endl;
    cout << "v1 == v2: " << (v1 == v2) << endl;
    cout << "v1 != v2: " << (v1 != v2) << endl;
    
    // 증감 연산자
    cout << "\n=== 증감 연산자 ===" << endl;
    Vector v7(1, 1);
    cout << "++v7: " << ++v7 << endl;
    cout << "v7++: " << v7++ << ", 이후: " << v7 << endl;
    
    // 인덱스 연산자
    cout << "\n=== 인덱스 연산자 ===" << endl;
    cout << "v1[0] = " << v1[0] << ", v1[1] = " << v1[1] << endl;
    v1[0] = 10;
    cout << "수정 후 v1: " << v1 << endl;
    
    return 0;
}



