/*
 * 3단계 예제 16: 공용체 (Unions)
 * 
 * 공용체는 여러 멤버가 같은 메모리 공간을 공유합니다.
 * 메모리 효율적이지만 한 번에 하나의 멤버만 사용할 수 있습니다.
 */

#include <iostream>
using namespace std;

// 기본 공용체
union Data {
    int intValue;
    double doubleValue;
    char charValue;
};

// 태그가 있는 공용체 (안전한 사용)
struct TaggedData {
    enum Type { INT, DOUBLE, CHAR } type;
    union {
        int intValue;
        double doubleValue;
        char charValue;
    } data;
};

// 실제 사용 예제: 타입 변환
union Converter {
    int intValue;
    float floatValue;
    unsigned char bytes[4];
};

int main() {
    // 기본 공용체 사용
    cout << "=== 기본 공용체 사용 ===" << endl;
    Data d;
    
    d.intValue = 42;
    cout << "intValue: " << d.intValue << endl;
    
    d.doubleValue = 3.14;
    cout << "doubleValue: " << d.doubleValue << endl;
    cout << "intValue (덮어씌워짐): " << d.intValue << endl;
    
    // 태그가 있는 공용체
    cout << "\n=== 태그가 있는 공용체 ===" << endl;
    TaggedData td;
    
    td.type = TaggedData::INT;
    td.data.intValue = 100;
    cout << "타입: INT, 값: " << td.data.intValue << endl;
    
    td.type = TaggedData::DOUBLE;
    td.data.doubleValue = 3.14159;
    cout << "타입: DOUBLE, 값: " << td.data.doubleValue << endl;
    
    // 타입 변환
    cout << "\n=== 타입 변환 ===" << endl;
    Converter c;
    c.floatValue = 3.14159f;
    
    cout << "float 값: " << c.floatValue << endl;
    cout << "바이트: ";
    for (int i = 0; i < 4; i++) {
        cout << (int)c.bytes[i] << " ";
    }
    cout << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 다양한 타입 저장 (한 번에 하나만)
    union Variant {
        int i;
        double d;
        bool b;
    };
    
    Variant v;
    v.i = 42;
    cout << "정수: " << v.i << endl;
    
    v.d = 3.14;
    cout << "실수: " << v.d << endl;
    
    v.b = true;
    cout << "불리언: " << v.b << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 한 번에 하나의 멤버만 유효" << endl;
    cout << "2. 어떤 멤버를 사용 중인지 추적 필요" << endl;
    cout << "3. 메모리 효율적이지만 타입 안전성 낮음" << endl;
    cout << "4. C++에서는 variant나 클래스 사용 권장" << endl;
    
    return 0;
}



