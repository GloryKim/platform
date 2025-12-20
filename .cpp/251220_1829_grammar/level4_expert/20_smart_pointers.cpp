/*
 * 4단계 예제 20: 스마트 포인터
 * 
 * 스마트 포인터는 자동 메모리 관리를 제공합니다.
 * 메모리 누수를 방지하고 안전한 메모리 관리를 가능하게 합니다.
 */

#include <iostream>
#include <memory>
using namespace std;

class Resource {
private:
    string name;

public:
    Resource(string n) : name(n) {
        cout << "Resource 생성: " << name << endl;
    }
    
    ~Resource() {
        cout << "Resource 소멸: " << name << endl;
    }
    
    void use() {
        cout << "Resource 사용: " << name << endl;
    }
};

int main() {
    // unique_ptr
    cout << "=== unique_ptr ===" << endl;
    {
        unique_ptr<Resource> ptr1(new Resource("Resource1"));
        ptr1->use();
        
        // unique_ptr<Resource> ptr2 = ptr1;  // 에러! 복사 불가
        unique_ptr<Resource> ptr2 = move(ptr1);  // 이동 가능
        ptr2->use();
    }  // 자동 소멸
    
    // make_unique (C++14)
    auto ptr3 = make_unique<Resource>("Resource2");
    ptr3->use();
    
    // shared_ptr
    cout << "\n=== shared_ptr ===" << endl;
    {
        shared_ptr<Resource> shared1 = make_shared<Resource>("Shared1");
        {
            shared_ptr<Resource> shared2 = shared1;  // 참조 카운트 증가
            cout << "참조 카운트: " << shared1.use_count() << endl;
        }  // shared2 소멸, 참조 카운트 감소
        cout << "참조 카운트: " << shared1.use_count() << endl;
    }  // shared1 소멸, Resource 소멸
    
    // weak_ptr
    cout << "\n=== weak_ptr ===" << endl;
    shared_ptr<Resource> shared = make_shared<Resource>("Shared2");
    weak_ptr<Resource> weak = shared;
    
    if (auto locked = weak.lock()) {
        locked->use();
        cout << "참조 카운트: " << shared.use_count() << endl;
    }
    
    shared.reset();  // Resource 소멸
    if (weak.expired()) {
        cout << "weak_ptr이 만료되었습니다." << endl;
    }
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. unique_ptr: 단일 소유권" << endl;
    cout << "2. shared_ptr: 공유 소유권" << endl;
    cout << "3. weak_ptr: 순환 참조 방지" << endl;
    cout << "4. make_unique/make_shared 권장" << endl;
    cout << "5. new/delete 직접 사용 지양" << endl;
    
    return 0;
}


