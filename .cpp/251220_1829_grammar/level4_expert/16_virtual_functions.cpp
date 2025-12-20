/*
 * 4단계 예제 16: 가상 함수
 * 
 * virtual 함수는 런타임 다형성을 구현합니다.
 * 파생 클래스의 오버라이드된 함수가 호출됩니다.
 */

#include <iostream>
using namespace std;

class Base {
public:
    // 일반 함수
    void normalFunction() {
        cout << "Base::normalFunction()" << endl;
    }
    
    // 가상 함수
    virtual void virtualFunction() {
        cout << "Base::virtualFunction()" << endl;
    }
    
    // 순수 가상 함수
    virtual void pureVirtualFunction() = 0;
    
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void normalFunction() {
        cout << "Derived::normalFunction()" << endl;
    }
    
    void virtualFunction() override {
        cout << "Derived::virtualFunction()" << endl;
    }
    
    void pureVirtualFunction() override {
        cout << "Derived::pureVirtualFunction()" << endl;
    }
};

int main() {
    // 일반 함수 vs 가상 함수
    cout << "=== 일반 함수 vs 가상 함수 ===" << endl;
    Derived d;
    Base* ptr = &d;
    
    ptr->normalFunction();      // Base 함수 호출 (컴파일 타임)
    ptr->virtualFunction();     // Derived 함수 호출 (런타임)
    
    // 객체 직접 호출
    cout << "\n=== 객체 직접 호출 ===" << endl;
    d.normalFunction();
    d.virtualFunction();
    d.pureVirtualFunction();
    
    // 다형성
    cout << "\n=== 다형성 ===" << endl;
    Base* objects[] = {new Derived(), new Derived()};
    
    for (int i = 0; i < 2; i++) {
        objects[i]->virtualFunction();
        objects[i]->pureVirtualFunction();
    }
    
    // 메모리 해제
    for (int i = 0; i < 2; i++) {
        delete objects[i];
    }
    
    return 0;
}


