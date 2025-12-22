/*
 * 4단계 예제 4: 다형성
 * 
 * 다형성은 같은 인터페이스로 다른 동작을 수행하는 것입니다.
 * virtual 함수와 오버라이딩을 통해 구현합니다.
 */

#include <iostream>
#include <string>
using namespace std;

// 기본 클래스
class Shape {
protected:
    string name;

public:
    Shape(string n) : name(n) {}
    
    virtual double area() const {
        return 0.0;
    }
    
    virtual double perimeter() const {
        return 0.0;
    }
    
    virtual void display() const {
        cout << "도형: " << name << endl;
    }
    
    virtual ~Shape() {}
};

// 파생 클래스 1
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("원"), radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void display() const override {
        cout << "원 (반지름: " << radius << ")" << endl;
    }
};

// 파생 클래스 2
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : Shape("사각형"), width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "사각형 (가로: " << width << ", 세로: " << height << ")" << endl;
    }
};

// 파생 클래스 3
class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(double b, double h) : Shape("삼각형"), base(b), height(h) {}
    
    double area() const override {
        return 0.5 * base * height;
    }
    
    double perimeter() const override {
        return base + height + sqrt(base * base + height * height);
    }
    
    void display() const override {
        cout << "삼각형 (밑변: " << base << ", 높이: " << height << ")" << endl;
    }
};

int main() {
    // 다형성 사용
    cout << "=== 다형성 사용 ===" << endl;
    Shape* shapes[] = {
        new Circle(5.0),
        new Rectangle(4.0, 6.0),
        new Triangle(3.0, 4.0)
    };
    
    for (int i = 0; i < 3; i++) {
        shapes[i]->display();
        cout << "넓이: " << shapes[i]->area() << endl;
        cout << "둘레: " << shapes[i]->perimeter() << endl;
        cout << endl;
    }
    
    // 메모리 해제
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    // 순수 가상 함수 예제
    cout << "=== 순수 가상 함수 ===" << endl;
    cout << "순수 가상 함수는 파생 클래스에서 반드시 구현해야 합니다." << endl;
    
    return 0;
}



