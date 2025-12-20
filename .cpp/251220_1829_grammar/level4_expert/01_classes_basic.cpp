/*
 * 4단계 예제 1: 클래스 기본
 * 
 * 클래스는 객체지향 프로그래밍의 핵심입니다.
 * 데이터와 함수를 하나로 묶어 캡슐화를 구현합니다.
 */

#include <iostream>
#include <string>
using namespace std;

// 기본 클래스
class Student {
private:
    string name;
    int age;
    double score;

public:
    // 생성자
    Student(string n, int a, double s) : name(n), age(a), score(s) {}
    
    // 접근자 (Getter)
    string getName() const { return name; }
    int getAge() const { return age; }
    double getScore() const { return score; }
    
    // 설정자 (Setter)
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setScore(double s) { score = s; }
    
    // 멤버 함수
    void display() const {
        cout << "이름: " << name << ", 나이: " << age 
             << ", 점수: " << score << endl;
    }
    
    bool isPassing() const {
        return score >= 60.0;
    }
};

int main() {
    // 객체 생성
    cout << "=== 객체 생성 ===" << endl;
    Student student1("홍길동", 20, 95.5);
    Student student2("김철수", 21, 55.0);
    
    student1.display();
    student2.display();
    
    // 접근자 사용
    cout << "\n=== 접근자 사용 ===" << endl;
    cout << student1.getName() << "의 점수: " << student1.getScore() << endl;
    
    // 설정자 사용
    cout << "\n=== 설정자 사용 ===" << endl;
    student2.setScore(75.0);
    student2.display();
    
    // 멤버 함수 사용
    cout << "\n=== 멤버 함수 사용 ===" << endl;
    cout << student1.getName() << " 합격 여부: " 
         << (student1.isPassing() ? "합격" : "불합격") << endl;
    cout << student2.getName() << " 합격 여부: " 
         << (student2.isPassing() ? "합격" : "불합격") << endl;
    
    // 객체 배열
    cout << "\n=== 객체 배열 ===" << endl;
    Student students[] = {
        Student("이영희", 19, 88.5),
        Student("박민수", 20, 92.0),
        Student("최지영", 21, 78.5)
    };
    
    for (int i = 0; i < 3; i++) {
        students[i].display();
    }
    
    return 0;
}



