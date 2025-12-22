/*
 * 3단계 예제 19: 메모리 레이아웃
 * 
 * 프로그램의 메모리 구조를 이해합니다.
 * 스택, 힙, 데이터 영역의 차이를 학습합니다.
 */

#include <iostream>
using namespace std;

// 전역 변수 (데이터 영역)
int globalVar = 100;
const int globalConst = 200;

// 정적 변수 (데이터 영역)
static int staticVar = 300;

void demonstrateMemory() {
    // 지역 변수 (스택)
    int localVar = 10;
    int localArray[5] = {1, 2, 3, 4, 5};
    
    // 동적 할당 (힙)
    int* heapVar = new int(42);
    int* heapArray = new int[10];
    
    cout << "=== 메모리 레이아웃 ===" << endl;
    cout << "전역 변수 주소: " << &globalVar << " (데이터 영역)" << endl;
    cout << "정적 변수 주소: " << &staticVar << " (데이터 영역)" << endl;
    cout << "지역 변수 주소: " << &localVar << " (스택)" << endl;
    cout << "지역 배열 주소: " << localArray << " (스택)" << endl;
    cout << "힙 변수 주소: " << heapVar << " (힙)" << endl;
    cout << "힙 배열 주소: " << heapArray << " (힙)" << endl;
    
    // 메모리 해제
    delete heapVar;
    delete[] heapArray;
}

int main() {
    demonstrateMemory();
    
    // 메모리 영역 설명
    cout << "\n=== 메모리 영역 설명 ===" << endl;
    cout << "1. 코드 영역: 프로그램 코드 저장" << endl;
    cout << "2. 데이터 영역: 전역/정적 변수 저장" << endl;
    cout << "3. 스택: 지역 변수, 함수 호출 정보" << endl;
    cout << "4. 힙: 동적 할당 메모리" << endl;
    
    // 스택 vs 힙
    cout << "\n=== 스택 vs 힙 ===" << endl;
    cout << "스택:" << endl;
    cout << "  - 빠른 할당/해제" << endl;
    cout << "  - 크기 제한 있음" << endl;
    cout << "  - 자동 관리" << endl;
    cout << "  - 지역 변수" << endl;
    
    cout << "\n힙:" << endl;
    cout << "  - 느린 할당/해제" << endl;
    cout << "  - 큰 메모리 가능" << endl;
    cout << "  - 수동 관리 (new/delete)" << endl;
    cout << "  - 동적 할당" << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 스택 사용
    int stackArray[1000];  // 스택에 할당
    cout << "스택 배열 크기: " << sizeof(stackArray) << " 바이트" << endl;
    
    // 힙 사용
    int* heapArray = new int[1000000];  // 힙에 할당
    cout << "힙 배열 할당 완료" << endl;
    delete[] heapArray;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 스택 오버플로우 주의 (큰 배열)" << endl;
    cout << "2. 힙 메모리 누수 방지 (delete 필수)" << endl;
    cout << "3. 스택은 함수 종료 시 자동 해제" << endl;
    cout << "4. 힙은 수동으로 해제해야 함" << endl;
    
    return 0;
}



