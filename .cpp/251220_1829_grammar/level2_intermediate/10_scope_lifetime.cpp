/*
 * 2단계 예제 10: 스코프와 생명주기
 * 
 * 변수의 유효 범위(scope)와 생명주기(lifetime)를 학습합니다.
 * 변수는 선언된 블록 내에서만 존재합니다.
 */

#include <iostream>
using namespace std;

int globalVar = 100;  // 전역 변수 (프로그램 전체에서 유효)

void function1() {
    int localVar = 50;  // 지역 변수 (함수 내에서만 유효)
    cout << "함수 내 전역 변수: " << globalVar << endl;
    cout << "함수 내 지역 변수: " << localVar << endl;
    // 함수 종료 시 localVar는 소멸됨
}

int main() {
    cout << "=== 전역 변수와 지역 변수 ===" << endl;
    cout << "전역 변수: " << globalVar << endl;
    
    int localVar = 25;  // main 함수의 지역 변수
    cout << "main 함수의 지역 변수: " << localVar << endl;
    
    function1();
    
    // 블록 스코프
    cout << "\n=== 블록 스코프 ===" << endl;
    {
        int blockVar = 10;  // 이 블록 내에서만 유효
        cout << "블록 내 변수: " << blockVar << endl;
        cout << "블록 내에서 전역 변수 접근: " << globalVar << endl;
        cout << "블록 내에서 지역 변수 접근: " << localVar << endl;
    }
    // cout << blockVar;  // 에러! 블록 밖에서는 사용 불가
    
    // 변수 이름 가리기 (Shadowing)
    cout << "\n=== 변수 이름 가리기 ===" << endl;
    int x = 10;
    cout << "외부 x: " << x << endl;
    
    {
        int x = 20;  // 외부 x를 가림
        cout << "내부 x: " << x << endl;
    }
    
    cout << "외부 x (변경 없음): " << x << endl;
    
    // 전역 변수 접근
    int globalVar = 200;  // 전역 변수를 가림
    cout << "\n전역 변수 가리기:" << endl;
    cout << "지역 globalVar: " << globalVar << endl;
    cout << "전역 globalVar: " << ::globalVar << endl;  // :: 연산자로 전역 접근
    
    // for 루프의 변수 스코프
    cout << "\n=== for 루프 스코프 ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "i = " << i << endl;
    }
    // cout << i;  // 에러! for 루프 밖에서는 i 사용 불가
    
    // while 루프의 변수 스코프
    cout << "\n=== while 루프 스코프 ===" << endl;
    int count = 0;
    while (count < 3) {
        int temp = count * 2;  // 루프 내부 변수
        cout << "count = " << count << ", temp = " << temp << endl;
        count++;
        // temp는 각 반복마다 생성되고 소멸됨
    }
    
    // 정적 변수 (static)
    cout << "\n=== 정적 변수 (static) ===" << endl;
    for (int i = 0; i < 3; i++) {
        static int staticCount = 0;  // 한 번만 초기화, 값 유지
        staticCount++;
        cout << "staticCount = " << staticCount << endl;
    }
    
    // 자동 변수 (일반 지역 변수)
    cout << "\n=== 자동 변수 ===" << endl;
    for (int i = 0; i < 3; i++) {
        int autoCount = 0;  // 매번 초기화
        autoCount++;
        cout << "autoCount = " << autoCount << endl;
    }
    
    // 생명주기
    cout << "\n=== 생명주기 ===" << endl;
    {
        int lifeVar = 42;
        cout << "변수 생성: " << lifeVar << endl;
        // 블록 종료 시 lifeVar 소멸
    }
    // lifeVar는 더 이상 존재하지 않음
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 최대값 찾기
    int maxVal = 0;
    int numbers[] = {10, 5, 20, 15, 8};
    
    for (int i = 0; i < 5; i++) {
        if (numbers[i] > maxVal) {
            maxVal = numbers[i];
        }
    }
    cout << "최대값: " << maxVal << endl;
    
    // 합계 계산
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
    cout << "1부터 10까지의 합: " << sum << endl;
    
    // 중첩 스코프
    cout << "\n=== 중첩 스코프 ===" << endl;
    int outer = 100;
    {
        int middle = 200;
        {
            int inner = 300;
            cout << "inner: " << inner << endl;
            cout << "middle: " << middle << endl;
            cout << "outer: " << outer << endl;
            cout << "global: " << globalVar << endl;
        }
        // inner는 여기서 소멸
        cout << "middle: " << middle << endl;
        cout << "outer: " << outer << endl;
    }
    // middle은 여기서 소멸
    cout << "outer: " << outer << endl;
    
    return 0;
}


