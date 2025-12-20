/*
 * 3단계 예제 18: 스코프 해석 연산자 (::)
 * 
 * :: 연산자는 전역 스코프나 네임스페이스에 접근할 때 사용합니다.
 * 변수 이름 가리기를 해결하는 데 유용합니다.
 */

#include <iostream>
using namespace std;

int value = 100;  // 전역 변수

namespace Math {
    const double PI = 3.14159;
    int value = 200;
    
    namespace Geometry {
        double area(double radius) {
            return PI * radius * radius;
        }
    }
}

namespace Physics {
    const double GRAVITY = 9.8;
    int value = 300;
}

int main() {
    // 전역 변수 접근
    cout << "=== 전역 변수 접근 ===" << endl;
    int value = 50;  // 지역 변수
    
    cout << "지역 value: " << value << endl;
    cout << "전역 value: " << ::value << endl;
    
    // 네임스페이스 접근
    cout << "\n=== 네임스페이스 접근 ===" << endl;
    cout << "Math::PI: " << Math::PI << endl;
    cout << "Math::value: " << Math::value << endl;
    cout << "Physics::GRAVITY: " << Physics::GRAVITY << endl;
    cout << "Physics::value: " << Physics::value << endl;
    
    // 중첩 네임스페이스
    cout << "\n=== 중첩 네임스페이스 ===" << endl;
    double radius = 5.0;
    cout << "반지름 " << radius << "인 원의 넓이: " 
         << Math::Geometry::area(radius) << endl;
    
    // using 선언 후에도 :: 사용 가능
    cout << "\n=== using 선언 후 ===" << endl;
    using Math::PI;
    cout << "PI: " << PI << endl;
    cout << "Math::PI: " << Math::PI << endl;  // 여전히 사용 가능
    
    // 클래스 스코프 (간단한 예제)
    cout << "\n=== 클래스 스코프 ===" << endl;
    class Counter {
    public:
        static int count;
        static void increment() {
            count++;
        }
    };
    
    Counter::count = 0;
    Counter::increment();
    cout << "Counter::count: " << Counter::count << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 이름 충돌 해결
    int Math::value = 200;  // 네임스페이스 변수
    int localValue = 400;   // 지역 변수
    
    cout << "localValue: " << localValue << endl;
    cout << "Math::value: " << Math::value << endl;
    cout << "::value (전역): " << ::value << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. ::는 전역 스코프 접근" << endl;
    cout << "2. 네임스페이스 구분에 사용" << endl;
    cout << "3. 클래스 정적 멤버 접근에 사용" << endl;
    cout << "4. 이름 가리기 해결에 유용" << endl;
    
    return 0;
}


