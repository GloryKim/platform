/*
 * 3단계 예제 15: 구조체 (Structures)
 * 
 * 구조체는 서로 다른 타입의 데이터를 하나로 묶는 사용자 정의 타입입니다.
 * 관련된 데이터를 그룹화하는 데 유용합니다.
 */

#include <iostream>
#include <string>
using namespace std;

// 기본 구조체
struct Point {
    int x;
    int y;
};

// 구조체 초기화
struct Student {
    string name;
    int age;
    double score;
};

// 구조체 함수
struct Rectangle {
    double width;
    double height;
    
    double area() {
        return width * height;
    }
    
    double perimeter() {
        return 2 * (width + height);
    }
};

// 중첩 구조체
struct Address {
    string street;
    string city;
    string zipCode;
};

struct Person {
    string name;
    int age;
    Address address;
};

int main() {
    // 구조체 변수 선언 및 초기화
    cout << "=== 구조체 변수 선언 및 초기화 ===" << endl;
    Point p1 = {10, 20};
    Point p2;
    p2.x = 30;
    p2.y = 40;
    
    cout << "p1: (" << p1.x << ", " << p1.y << ")" << endl;
    cout << "p2: (" << p2.x << ", " << p2.y << ")" << endl;
    
    // 구조체 배열
    cout << "\n=== 구조체 배열 ===" << endl;
    Student students[3] = {
        {"홍길동", 20, 95.5},
        {"김철수", 21, 87.3},
        {"이영희", 19, 92.1}
    };
    
    for (int i = 0; i < 3; i++) {
        cout << students[i].name << ": " << students[i].age 
             << "세, " << students[i].score << "점" << endl;
    }
    
    // 구조체 함수 사용
    cout << "\n=== 구조체 함수 사용 ===" << endl;
    Rectangle rect = {5.0, 3.0};
    cout << "넓이: " << rect.area() << endl;
    cout << "둘레: " << rect.perimeter() << endl;
    
    // 중첩 구조체
    cout << "\n=== 중첩 구조체 ===" << endl;
    Person person = {
        "홍길동",
        25,
        {"서울시 강남구", "서울", "12345"}
    };
    
    cout << "이름: " << person.name << endl;
    cout << "나이: " << person.age << endl;
    cout << "주소: " << person.address.street << ", " 
         << person.address.city << " " << person.address.zipCode << endl;
    
    // 구조체 포인터
    cout << "\n=== 구조체 포인터 ===" << endl;
    Point* ptr = &p1;
    cout << "포인터로 접근: (" << ptr->x << ", " << ptr->y << ")" << endl;
    cout << "또는: (" << (*ptr).x << ", " << (*ptr).y << ")" << endl;
    
    // 구조체 복사
    cout << "\n=== 구조체 복사 ===" << endl;
    Point p3 = p1;  // 복사
    p3.x = 100;
    cout << "p1: (" << p1.x << ", " << p1.y << ")" << endl;
    cout << "p3: (" << p3.x << ", " << p3.y << ")" << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 좌표 거리 계산
    double distance = sqrt((p2.x - p1.x) * (p2.x - p1.x) + 
                           (p2.y - p1.y) * (p2.y - p1.y));
    cout << "p1과 p2 사이의 거리: " << distance << endl;
    
    return 0;
}



