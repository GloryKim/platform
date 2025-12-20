/*
 * 1단계 예제 10: 변수 범위 (Scope)
 * 
 * 변수의 유효 범위를 학습합니다.
 * 변수는 선언된 블록 내에서만 사용할 수 있습니다.
 */

#include <iostream>
using namespace std;

int globalVar = 100;  // 전역 변수 (어디서든 사용 가능)

int main() {
    // 지역 변수 (main 함수 내에서만 사용 가능)
    int localVar = 50;
    
    cout << "전역 변수: " << globalVar << endl;
    cout << "지역 변수: " << localVar << endl;
    
    // 블록 스코프
    {
        int blockVar = 25;          // 이 블록 내에서만 사용 가능
        cout << "\n블록 내 변수: " << blockVar << endl;
        cout << "블록 내에서 전역 변수 접근: " << globalVar << endl;
        cout << "블록 내에서 지역 변수 접근: " << localVar << endl;
    }
    // cout << blockVar;  // 에러! 블록 밖에서는 사용 불가
    
    // 변수 이름 가리기 (Shadowing)
    int x = 10;
    cout << "\n변수 가리기 예제:" << endl;
    cout << "외부 x: " << x << endl;
    
    {
        int x = 20;                 // 외부 x를 가림
        cout << "내부 x: " << x << endl;
    }
    
    cout << "외부 x (변경 없음): " << x << endl;
    
    // 전역 변수 접근
    int globalVar = 200;            // 전역 변수를 가림
    cout << "\n전역 변수 가리기:" << endl;
    cout << "지역 globalVar: " << globalVar << endl;
    cout << "전역 globalVar: " << ::globalVar << endl;  // :: 연산자로 전역 접근
    
    // for 루프의 변수 스코프
    cout << "\nfor 루프 스코프:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "i = " << i << endl;
    }
    // cout << i;  // 에러! for 루프 밖에서는 i 사용 불가
    
    // 같은 이름의 변수는 같은 스코프에서 선언 불가
    // int localVar = 30;  // 에러! 이미 선언됨
    
    return 0;
}


