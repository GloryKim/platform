/*
 * 1단계 예제 12: 네임스페이스 (Namespace)
 * 
 * 네임스페이스는 이름 충돌을 방지하고 코드를 조직화하는 방법입니다.
 * std 네임스페이스는 C++ 표준 라이브러리를 포함합니다.
 */

#include <iostream>
// using namespace std;  // 이 줄이 없으면 std::를 매번 붙여야 함

int main() {
    // 네임스페이스 없이 사용
    std::cout << "std::cout 사용" << std::endl;
    std::string name = "C++";
    std::cout << "이름: " << name << std::endl;
    
    // using 선언으로 특정 이름만 가져오기
    using std::cout;
    using std::endl;
    cout << "using 선언 사용" << endl;
    
    // using namespace로 전체 네임스페이스 가져오기
    using namespace std;
    cout << "using namespace std 사용" << endl;
    
    // 사용자 정의 네임스페이스
    namespace Math {
        const double PI = 3.14159;
        double add(double a, double b) {
            return a + b;
        }
    }
    
    namespace Physics {
        const double GRAVITY = 9.8;
        double force(double mass, double acceleration) {
            return mass * acceleration;
        }
    }
    
    // 네임스페이스 사용
    cout << "\n사용자 정의 네임스페이스:" << endl;
    cout << "Math::PI = " << Math::PI << endl;
    cout << "Math::add(3, 4) = " << Math::add(3, 4) << endl;
    cout << "Physics::GRAVITY = " << Physics::GRAVITY << endl;
    
    // using으로 네임스페이스 가져오기
    using namespace Math;
    cout << "\nusing namespace Math 후:" << endl;
    cout << "PI = " << PI << endl;  // Math:: 없이 사용 가능
    cout << "add(5, 6) = " << add(5, 6) << endl;
    
    // 중첩 네임스페이스
    namespace Outer {
        namespace Inner {
            int value = 42;
        }
    }
    
    cout << "\n중첩 네임스페이스:" << endl;
    cout << "Outer::Inner::value = " << Outer::Inner::value << endl;
    
    // 네임스페이스 별칭
    namespace M = Math;
    namespace P = Physics;
    cout << "\n네임스페이스 별칭:" << endl;
    cout << "M::PI = " << M::PI << endl;
    cout << "P::GRAVITY = " << P::GRAVITY << endl;
    
    return 0;
}


