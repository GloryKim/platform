/*
 * 1단계 예제 1: 변수 선언과 초기화
 * 
 * C++에서 변수를 선언하고 초기화하는 기본 방법을 학습합니다.
 * 변수는 데이터를 저장하는 메모리 공간의 이름입니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 정수형 변수 선언 및 초기화
    int age = 25;           // int: 정수형 (보통 4바이트)
    int height = 180;       // 변수 선언과 동시에 값을 할당
    
    // 변수 선언만 하고 나중에 값 할당
    int weight;
    weight = 75;            // 나중에 값 할당
    
    // 여러 변수를 한 번에 선언
    int x = 10, y = 20, z = 30;
    
    // 출력
    cout << "나이: " << age << endl;
    cout << "키: " << height << "cm" << endl;
    cout << "몸무게: " << weight << "kg" << endl;
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
    
    return 0;
}
