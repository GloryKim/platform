/*
 * 4단계 예제 17: 추상 클래스
 * 
 * 추상 클래스는 순수 가상 함수를 가진 클래스입니다.
 * 직접 인스턴스화할 수 없으며 파생 클래스에서 구현해야 합니다.
 */

#include <iostream>
using namespace std;

// 추상 클래스
class Shape {
protected:
    string name;

public:
    Shape(string n) : name(n) {}
    
    // 순수 가상 함수
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    
    // 일반 가상 함수
    virtual void display() const {
        cout << "도형: " << name << endl;
    }
    
    virtual ~Shape() {}
};

// 구체 클래스 1
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

// 구체 클래스 2
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

int main() {
    // 추상 클래스는 인스턴스화 불가
    // Shape shape("도형");  // 에러!
    
    // 구체 클래스 사용
    cout << "=== 구체 클래스 사용 ===" << endl;
    Circle circle(5.0);
    Rectangle rect(4.0, 6.0);
    
    circle.display();
    cout << "넓이: " << circle.area() << endl;
    cout << "둘레: " << circle.perimeter() << endl;
    
    rect.display();
    cout << "넓이: " << rect.area() << endl;
    cout << "둘레: " << rect.perimeter() << endl;
    
    // 다형성
    cout << "\n=== 다형성 ===" << endl;
    Shape* shapes[] = {&circle, &rect};
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->display();
        cout << "넓이: " << shapes[i]->area() << endl;
        cout << "둘레: " << shapes[i]->perimeter() << endl;
        cout << endl;
    }
    
    return 0;
}



