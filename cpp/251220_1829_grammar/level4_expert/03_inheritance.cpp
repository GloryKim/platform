/*
 * 4단계 예제 3: 상속
 * 
 * 상속은 기존 클래스를 확장하여 새로운 클래스를 만드는 방법입니다.
 * 코드 재사용성과 확장성을 높입니다.
 */

#include <iostream>
#include <string>
using namespace std;

// 기본 클래스
class Animal {
protected:
    string name;
    int age;

public:
    Animal(string n, int a) : name(n), age(a) {}
    
    void eat() {
        cout << name << "이(가) 먹고 있습니다." << endl;
    }
    
    void sleep() {
        cout << name << "이(가) 자고 있습니다." << endl;
    }
    
    virtual void makeSound() {
        cout << name << "이(가) 소리를 냅니다." << endl;
    }
    
    virtual ~Animal() {}
};

// 파생 클래스 1
class Dog : public Animal {
private:
    string breed;

public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}
    
    void bark() {
        cout << name << "이(가) 멍멍 짖습니다." << endl;
    }
    
    void makeSound() override {
        cout << name << "이(가) 멍멍합니다." << endl;
    }
    
    void display() {
        cout << "이름: " << name << ", 나이: " << age 
             << ", 품종: " << breed << endl;
    }
};

// 파생 클래스 2
class Cat : public Animal {
private:
    bool isIndoor;

public:
    Cat(string n, int a, bool indoor) : Animal(n, a), isIndoor(indoor) {}
    
    void meow() {
        cout << name << "이(가) 야옹합니다." << endl;
    }
    
    void makeSound() override {
        cout << name << "이(가) 야옹합니다." << endl;
    }
    
    void display() {
        cout << "이름: " << name << ", 나이: " << age 
             << ", 실내: " << (isIndoor ? "예" : "아니오") << endl;
    }
};

int main() {
    // 기본 클래스 객체
    cout << "=== 기본 클래스 객체 ===" << endl;
    Animal animal("동물", 5);
    animal.eat();
    animal.sleep();
    animal.makeSound();
    
    // 파생 클래스 객체
    cout << "\n=== 파생 클래스 객체 ===" << endl;
    Dog dog("바둑이", 3, "골든 리트리버");
    dog.display();
    dog.eat();
    dog.sleep();
    dog.bark();
    dog.makeSound();
    
    Cat cat("나비", 2, true);
    cat.display();
    cat.eat();
    cat.sleep();
    cat.meow();
    cat.makeSound();
    
    // 다형성
    cout << "\n=== 다형성 ===" << endl;
    Animal* animals[] = {&dog, &cat};
    
    for (int i = 0; i < 2; i++) {
        animals[i]->makeSound();  // 각각의 오버라이드된 함수 호출
    }
    
    return 0;
}



