/*
 * 5단계 예제 10: 초기화 리스트
 * 
 * initializer_list는 중괄호 초기화를 지원합니다.
 * 컨테이너와 사용자 정의 타입에 유용합니다.
 */

#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

// initializer_list를 받는 함수
void printNumbers(initializer_list<int> numbers) {
    cout << "숫자: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
}

// initializer_list를 받는 클래스
class MyContainer {
private:
    vector<int> data;

public:
    MyContainer(initializer_list<int> init) : data(init) {}
    
    void display() const {
        cout << "컨테이너: ";
        for (int num : data) {
            cout << num << " ";
        }
        cout << endl;
    }
};

int main() {
    // 함수에 전달
    cout << "=== 함수에 전달 ===" << endl;
    printNumbers({1, 2, 3, 4, 5});
    printNumbers({10, 20, 30});
    
    // 클래스 초기화
    cout << "\n=== 클래스 초기화 ===" << endl;
    MyContainer container = {1, 2, 3, 4, 5};
    container.display();
    
    // vector 초기화
    cout << "\n=== vector 초기화 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5};
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 배열 초기화
    cout << "\n=== 배열 초기화 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}



