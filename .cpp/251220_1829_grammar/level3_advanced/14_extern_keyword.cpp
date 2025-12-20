/*
 * 3단계 예제 14: extern 키워드
 * 
 * extern은 다른 파일에 정의된 변수나 함수를 선언할 때 사용합니다.
 * 여러 파일 간 변수/함수 공유에 사용됩니다.
 */

#include <iostream>
using namespace std;

// 다른 파일에 정의된 변수 선언
extern int globalVariable;

// 다른 파일에 정의된 함수 선언
extern void externalFunction();

// 현재 파일의 전역 변수
int currentFileVariable = 42;

// extern "C" 링키지 (C 함수 호출 시)
extern "C" {
    // C 함수 선언
    // void cFunction();
}

int main() {
    // extern 변수 사용
    cout << "=== extern 변수 사용 ===" << endl;
    // cout << "globalVariable: " << globalVariable << endl;
    // 주의: 실제로는 다른 파일에 정의되어 있어야 함
    
    // extern 함수 호출
    cout << "\n=== extern 함수 호출 ===" << endl;
    // externalFunction();
    // 주의: 실제로는 다른 파일에 정의되어 있어야 함
    
    // 현재 파일 변수
    cout << "\n=== 현재 파일 변수 ===" << endl;
    cout << "currentFileVariable: " << currentFileVariable << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    cout << "extern은 여러 파일로 나뉜 프로젝트에서 사용됩니다." << endl;
    cout << "1. 헤더 파일에 extern 선언" << endl;
    cout << "2. 소스 파일에 실제 정의" << endl;
    cout << "3. 링커가 연결" << endl;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. extern은 선언이지 정의가 아님" << endl;
    cout << "2. 다른 파일에 실제 정의가 있어야 함" << endl;
    cout << "3. 초기화와 함께 사용하면 정의가 됨" << endl;
    cout << "4. C 함수 호출 시 extern \"C\" 사용" << endl;
    
    return 0;
}

/*
 * 실제 사용 예제 구조:
 * 
 * file1.cpp:
 *   int globalVariable = 100;
 *   void externalFunction() { ... }
 * 
 * file2.cpp:
 *   extern int globalVariable;
 *   extern void externalFunction();
 *   int main() {
 *       cout << globalVariable << endl;
 *       externalFunction();
 *   }
 */



