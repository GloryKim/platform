/*
 * 1단계 예제 20: 타입 별칭 (typedef, using)
 * 
 * 복잡한 타입 이름을 간단한 별칭으로 정의하는 방법을 학습합니다.
 * typedef (C 스타일)과 using (C++11, 권장)을 사용합니다.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// typedef 사용 (C 스타일)
typedef int Age;
typedef double Price;
typedef string Name;

// 복잡한 타입에 대한 typedef
typedef vector<int> IntVector;
typedef vector<string> StringVector;

// 함수 포인터 typedef
typedef int (*MathFunc)(int, int);

// using 사용 (C++11, 권장)
using Score = double;
using ID = unsigned long long;
using Point = pair<int, int>;

// 템플릿 별칭
using IntPair = pair<int, int>;
using StringMap = map<string, string>;

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // 기본 타입 별칭 사용
    cout << "=== 기본 타입 별칭 ===" << endl;
    
    Age personAge = 25;
    Price itemPrice = 99.99;
    Name userName = "홍길동";
    
    cout << "나이: " << personAge << endl;
    cout << "가격: " << itemPrice << endl;
    cout << "이름: " << userName << endl;
    
    // 복잡한 타입 별칭 사용
    cout << "\n=== 복잡한 타입 별칭 ===" << endl;
    
    IntVector numbers = {1, 2, 3, 4, 5};
    cout << "정수 벡터: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    StringVector names = {"Alice", "Bob", "Charlie"};
    cout << "문자열 벡터: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    // using으로 정의한 별칭 사용
    cout << "\n=== using 별칭 ===" << endl;
    
    Score mathScore = 95.5;
    ID userId = 123456789012345;
    Point p1 = make_pair(10, 20);
    
    cout << "수학 점수: " << mathScore << endl;
    cout << "사용자 ID: " << userId << endl;
    cout << "점 좌표: (" << p1.first << ", " << p1.second << ")" << endl;
    
    // 함수 포인터 typedef 사용
    cout << "\n=== 함수 포인터 typedef ===" << endl;
    
    MathFunc func1 = add;
    MathFunc func2 = multiply;
    
    cout << "add(5, 3) = " << func1(5, 3) << endl;
    cout << "multiply(5, 3) = " << func2(5, 3) << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 좌표계 정의
    using Coordinate = pair<double, double>;
    Coordinate point1 = make_pair(1.5, 2.5);
    Coordinate point2 = make_pair(3.0, 4.0);
    
    cout << "점1: (" << point1.first << ", " << point1.second << ")" << endl;
    cout << "점2: (" << point2.first << ", " << point2.second << ")" << endl;
    
    // 학생 정보 구조체 (간단한 예제)
    struct Student {
        string name;
        int age;
        double score;
    };
    
    using StudentList = vector<Student>;
    StudentList students = {
        {"홍길동", 20, 95.5},
        {"김철수", 21, 87.3},
        {"이영희", 19, 92.1}
    };
    
    cout << "\n학생 목록:" << endl;
    for (const auto& student : students) {
        cout << "이름: " << student.name 
             << ", 나이: " << student.age 
             << ", 점수: " << student.score << endl;
    }
    
    // 타입 별칭의 장점
    cout << "\n=== 타입 별칭의 장점 ===" << endl;
    cout << "1. 코드 가독성 향상" << endl;
    cout << "2. 타입 변경 시 한 곳만 수정" << endl;
    cout << "3. 복잡한 타입을 간단하게 표현" << endl;
    cout << "4. 의도 명확화" << endl;
    
    return 0;
}
