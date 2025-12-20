/*
 * 4단계 예제 8: 정적 멤버
 * 
 * static 멤버는 클래스의 모든 객체가 공유합니다.
 * 클래스 레벨의 데이터와 함수를 구현할 수 있습니다.
 */

#include <iostream>
using namespace std;

class Counter {
private:
    static int totalCount;  // 정적 멤버 변수
    int instanceCount;

public:
    Counter() : instanceCount(0) {
        totalCount++;
        instanceCount = totalCount;
    }
    
    ~Counter() {
        totalCount--;
    }
    
    // 정적 멤버 함수
    static int getTotalCount() {
        return totalCount;
    }
    
    int getInstanceCount() const {
        return instanceCount;
    }
    
    void increment() {
        instanceCount++;
    }
};

// 정적 멤버 변수 정의 (클래스 외부에서)
int Counter::totalCount = 0;

// 유틸리티 클래스
class MathUtils {
public:
    static double PI;
    
    static double square(double x) {
        return x * x;
    }
    
    static double circleArea(double radius) {
        return PI * radius * radius;
    }
    
    static int max(int a, int b) {
        return (a > b) ? a : b;
    }
};

double MathUtils::PI = 3.14159;

int main() {
    // 정적 멤버 변수
    cout << "=== 정적 멤버 변수 ===" << endl;
    cout << "초기 카운트: " << Counter::getTotalCount() << endl;
    
    Counter c1, c2, c3;
    cout << "객체 생성 후 카운트: " << Counter::getTotalCount() << endl;
    cout << "c1 인스턴스 번호: " << c1.getInstanceCount() << endl;
    cout << "c2 인스턴스 번호: " << c2.getInstanceCount() << endl;
    cout << "c3 인스턴스 번호: " << c3.getInstanceCount() << endl;
    
    {
        Counter c4;
        cout << "블록 내 카운트: " << Counter::getTotalCount() << endl;
    }  // c4 소멸
    
    cout << "블록 종료 후 카운트: " << Counter::getTotalCount() << endl;
    
    // 정적 멤버 함수
    cout << "\n=== 정적 멤버 함수 ===" << endl;
    cout << "MathUtils::PI = " << MathUtils::PI << endl;
    cout << "MathUtils::square(5) = " << MathUtils::square(5) << endl;
    cout << "MathUtils::circleArea(5) = " << MathUtils::circleArea(5) << endl;
    cout << "MathUtils::max(10, 20) = " << MathUtils::max(10, 20) << endl;
    
    // 객체 없이 호출 가능
    MathUtils utils;
    cout << "객체를 통해서도 호출 가능: " << utils.square(3) << endl;
    
    return 0;
}



