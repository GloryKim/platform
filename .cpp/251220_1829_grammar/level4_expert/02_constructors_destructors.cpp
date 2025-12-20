/*
 * 4단계 예제 2: 생성자와 소멸자
 * 
 * 생성자는 객체 생성 시 호출되고, 소멸자는 객체 소멸 시 호출됩니다.
 * 리소스 관리에 중요한 역할을 합니다.
 */

#include <iostream>
#include <string>
using namespace std;

class Resource {
private:
    string name;
    int* data;

public:
    // 기본 생성자
    Resource() : name("Default"), data(nullptr) {
        cout << "기본 생성자 호출" << endl;
    }
    
    // 매개변수 생성자
    Resource(string n, int size) : name(n) {
        cout << "생성자 호출: " << name << endl;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }
    
    // 복사 생성자
    Resource(const Resource& other) : name(other.name + "_copy") {
        cout << "복사 생성자 호출: " << name << endl;
        if (other.data != nullptr) {
            data = new int[5];  // 간단히 5로 고정
            for (int i = 0; i < 5; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    
    // 소멸자
    ~Resource() {
        cout << "소멸자 호출: " << name << endl;
        delete[] data;
        data = nullptr;
    }
    
    // 대입 연산자
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            cout << "대입 연산자 호출" << endl;
            name = other.name + "_assigned";
            delete[] data;
            if (other.data != nullptr) {
                data = new int[5];
                for (int i = 0; i < 5; i++) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }
    
    void display() const {
        cout << "Resource: " << name << endl;
    }
};

int main() {
    // 기본 생성자
    cout << "=== 기본 생성자 ===" << endl;
    Resource r1;
    r1.display();
    
    // 매개변수 생성자
    cout << "\n=== 매개변수 생성자 ===" << endl;
    Resource r2("Resource1", 5);
    r2.display();
    
    // 복사 생성자
    cout << "\n=== 복사 생성자 ===" << endl;
    Resource r3 = r2;
    r3.display();
    
    // 대입 연산자
    cout << "\n=== 대입 연산자 ===" << endl;
    Resource r4;
    r4 = r2;
    r4.display();
    
    // 스코프 종료 시 소멸자 호출
    cout << "\n=== 스코프 종료 ===" << endl;
    {
        Resource r5("Temporary", 3);
        r5.display();
    }  // r5 소멸자 호출
    
    cout << "\n메인 함수 종료 전" << endl;
    return 0;  // 모든 객체 소멸자 호출
}


