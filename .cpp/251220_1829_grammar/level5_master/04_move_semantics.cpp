/*
 * 5단계 예제 4: 이동 의미론
 * 
 * 이동 의미론은 불필요한 복사를 피하고 성능을 향상시킵니다.
 * rvalue 참조와 이동 생성자를 사용합니다.
 */

#include <iostream>
#include <vector>
using namespace std;

class Resource {
private:
    int* data;
    int size;

public:
    // 생성자
    Resource(int s) : size(s) {
        data = new int[size];
        cout << "생성자 호출" << endl;
    }
    
    // 복사 생성자
    Resource(const Resource& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "복사 생성자 호출" << endl;
    }
    
    // 이동 생성자
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "이동 생성자 호출" << endl;
    }
    
    // 복사 대입 연산자
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            cout << "복사 대입 연산자 호출" << endl;
        }
        return *this;
    }
    
    // 이동 대입 연산자
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "이동 대입 연산자 호출" << endl;
        }
        return *this;
    }
    
    ~Resource() {
        delete[] data;
    }
};

Resource createResource() {
    return Resource(10);  // 임시 객체 반환
}

int main() {
    // 복사 vs 이동
    cout << "=== 복사 vs 이동 ===" << endl;
    Resource r1(5);
    Resource r2 = r1;  // 복사 생성자
    
    Resource r3 = createResource();  // 이동 생성자 (RVO)
    
    r2 = createResource();  // 이동 대입 연산자
    
    // std::move
    cout << "\n=== std::move ===" << endl;
    Resource r4(5);
    Resource r5 = move(r4);  // 명시적 이동
    
    // vector와 이동
    cout << "\n=== vector와 이동 ===" << endl;
    vector<Resource> resources;
    resources.push_back(Resource(3));  // 이동 생성자
    resources.push_back(move(r5));     // 명시적 이동
    
    return 0;
}



