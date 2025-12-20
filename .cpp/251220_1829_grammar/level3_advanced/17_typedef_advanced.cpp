/*
 * 3단계 예제 17: typedef 고급
 * 
 * typedef로 복잡한 타입에 간단한 이름을 부여합니다.
 * 코드 가독성과 유지보수성을 높입니다.
 */

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 기본 typedef
typedef int Age;
typedef double Price;
typedef string Name;

// 포인터 typedef
typedef int* IntPtr;
typedef int** IntPtrPtr;

// 함수 포인터 typedef
typedef int (*MathFunc)(int, int);
typedef void (*PrintFunc)(string);

// 구조체 typedef
struct Point {
    int x, y;
};
typedef Point Coordinate;

// 복잡한 타입 typedef
typedef vector<int> IntVector;
typedef vector<string> StringVector;
typedef map<string, int> StringIntMap;

// 중첩 typedef
typedef vector<vector<int>> IntMatrix;

// 실제 사용 예제
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

void printMessage(string msg) {
    cout << msg << endl;
}

int main() {
    // 기본 typedef 사용
    cout << "=== 기본 typedef 사용 ===" << endl;
    Age personAge = 25;
    Price itemPrice = 99.99;
    Name userName = "홍길동";
    
    cout << "나이: " << personAge << endl;
    cout << "가격: " << itemPrice << endl;
    cout << "이름: " << userName << endl;
    
    // 포인터 typedef
    cout << "\n=== 포인터 typedef ===" << endl;
    int num = 42;
    IntPtr ptr = &num;
    cout << "*ptr = " << *ptr << endl;
    
    // 함수 포인터 typedef
    cout << "\n=== 함수 포인터 typedef ===" << endl;
    MathFunc func1 = add;
    MathFunc func2 = multiply;
    
    cout << "add(5, 3) = " << func1(5, 3) << endl;
    cout << "multiply(5, 3) = " << func2(5, 3) << endl;
    
    PrintFunc printFunc = printMessage;
    printFunc("typedef 함수 포인터");
    
    // 구조체 typedef
    cout << "\n=== 구조체 typedef ===" << endl;
    Coordinate coord = {10, 20};
    cout << "좌표: (" << coord.x << ", " << coord.y << ")" << endl;
    
    // 컨테이너 typedef
    cout << "\n=== 컨테이너 typedef ===" << endl;
    IntVector numbers = {1, 2, 3, 4, 5};
    StringVector names = {"Alice", "Bob", "Charlie"};
    
    cout << "숫자: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;
    
    cout << "이름: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    // 맵 typedef
    StringIntMap scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    
    cout << "\n점수:" << endl;
    for (const auto& pair : scores) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // 행렬 typedef
    cout << "\n=== 행렬 typedef ===" << endl;
    IntMatrix matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. typedef는 타입 별칭일 뿐" << endl;
    cout << "2. C++11의 using이 더 권장됨" << endl;
    cout << "3. 복잡한 타입을 간단하게 표현" << endl;
    cout << "4. 코드 가독성 향상" << endl;
    
    return 0;
}
