/*
 * 4단계 예제 18: 다중 상속
 * 
 * 다중 상속은 클래스가 여러 기본 클래스를 상속받는 것입니다.
 * 유연하지만 다이아몬드 문제 등의 복잡성이 있습니다.
 */

#include <iostream>
using namespace std;

// 기본 클래스 1
class Animal {
protected:
    string name;

public:
    Animal(string n) : name(n) {}
    
    void eat() {
        cout << name << "이(가) 먹고 있습니다." << endl;
    }
};

// 기본 클래스 2
class Flyable {
public:
    virtual void fly() {
        cout << "날고 있습니다." << endl;
    }
};

// 기본 클래스 3
class Swimmable {
public:
    virtual void swim() {
        cout << "수영하고 있습니다." << endl;
    }
};

// 단일 상속
class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    
    void bark() {
        cout << name << "이(가) 멍멍 짖습니다." << endl;
    }
};

// 다중 상속
class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(string n) : Animal(n) {}
    
    void display() {
        cout << name << "은(는) 오리입니다." << endl;
    }
};

int main() {
    // 단일 상속
    cout << "=== 단일 상속 ===" << endl;
    Dog dog("바둑이");
    dog.eat();
    dog.bark();
    
    // 다중 상속
    cout << "\n=== 다중 상속 ===" << endl;
    Duck duck("도날드");
    duck.display();
    duck.eat();
    duck.fly();
    duck.swim();
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 다이아몬드 문제 주의" << endl;
    cout << "2. 가상 상속으로 해결 가능" << endl;
    cout << "3. 복잡도 증가" << endl;
    cout << "4. 인터페이스 상속 권장" << endl;
    
    return 0;
}
