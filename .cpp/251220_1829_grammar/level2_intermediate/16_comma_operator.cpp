/*
 * 2단계 예제 16: 쉼표 연산자
 * 
 * 쉼표 연산자는 여러 표현식을 순차적으로 실행하고 마지막 값을 반환합니다.
 * 주로 for 루프에서 여러 변수를 초기화하거나 업데이트할 때 사용합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 쉼표 연산자
    cout << "=== 기본 쉼표 연산자 ===" << endl;
    int a = (1, 2, 3);  // 마지막 값인 3이 a에 할당됨
    cout << "a = (1, 2, 3): " << a << endl;
    
    int b = (10, 20, 30, 40);
    cout << "b = (10, 20, 30, 40): " << b << endl;
    
    // 표현식 순차 실행
    cout << "\n=== 표현식 순차 실행 ===" << endl;
    int x = 0, y = 0;
    int result = (x = 5, y = 10, x + y);  // x=5, y=10 실행 후 x+y 반환
    cout << "x = " << x << ", y = " << y << ", result = " << result << endl;
    
    // for 루프에서 사용
    cout << "\n=== for 루프에서 사용 ===" << endl;
    for (int i = 0, j = 10; i < 5; i++, j--) {
        cout << "i = " << i << ", j = " << j << endl;
    }
    
    // 여러 변수 초기화
    cout << "\n=== 여러 변수 초기화 ===" << endl;
    int i = 0, j = 0, k = 0;
    for (i = 0, j = 5, k = 10; i < 3; i++, j++, k++) {
        cout << "i=" << i << " j=" << j << " k=" << k << endl;
    }
    
    // 함수 호출과 함께 사용
    cout << "\n=== 함수 호출과 함께 사용 ===" << endl;
    auto print = [](int n) { cout << n << " "; };
    
    (print(1), print(2), print(3));  // 순차 실행
    cout << endl;
    
    // 조건문에서 사용
    cout << "\n=== 조건문에서 사용 ===" << endl;
    int num1 = 5, num2 = 10;
    int max = (num1 > num2) ? num1 : num2;
    cout << "max(" << num1 << ", " << num2 << ") = " << max << endl;
    
    // 실제 사용 예제 1: 변수 교환
    cout << "\n=== 실제 사용 예제 1: 변수 교환 ===" << endl;
    int a1 = 10, b1 = 20;
    cout << "교환 전: a=" << a1 << ", b=" << b1 << endl;
    
    // 쉼표 연산자로 교환 (일반적으로는 권장하지 않음)
    int temp = a1;
    a1 = b1, b1 = temp;
    cout << "교환 후: a=" << a1 << ", b=" << b1 << endl;
    
    // 실제 사용 예제 2: 배열 초기화
    cout << "\n=== 실제 사용 예제 2: 배열 초기화 ===" << endl;
    int arr[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = 0;
    }
    
    // 쉼표 연산자로 한 번에 초기화 (가독성 낮음)
    int arr2[5];
    for (int i = 0; i < 5; arr2[i] = 0, i++);
    
    cout << "배열 초기화 완료" << endl;
    
    // 실제 사용 예제 3: 복잡한 표현식
    cout << "\n=== 실제 사용 예제 3: 복잡한 표현식 ===" << endl;
    int val1 = 1, val2 = 2, val3 = 3;
    int sum = (val1++, val2++, val3++, val1 + val2 + val3);
    cout << "val1=" << val1 << ", val2=" << val2 << ", val3=" << val3 << endl;
    cout << "sum=" << sum << endl;
    
    // 실제 사용 예제 4: 디버깅 출력
    cout << "\n=== 실제 사용 예제 4: 디버깅 출력 ===" << endl;
    int debug1 = 10, debug2 = 20, debug3 = 30;
    (cout << "디버그: ", cout << debug1 << " ", cout << debug2 << " ", 
     cout << debug3 << endl);
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 쉼표 연산자는 우선순위가 매우 낮음" << endl;
    cout << "2. 괄호를 사용하여 의도를 명확히 해야 함" << endl;
    cout << "3. 가독성이 떨어질 수 있으므로 신중하게 사용" << endl;
    cout << "4. 대부분의 경우 여러 줄로 나누는 것이 더 명확함" << endl;
    
    // 우선순위 예제
    cout << "\n=== 우선순위 예제 ===" << endl;
    int p = 1, q = 2, r = 3;
    int result1 = p, q, r;  // 쉼표 연산자 (r만 할당)
    int result2 = (p, q, r);  // 명시적 괄호 (r만 할당)
    
    cout << "result1 = " << result1 << endl;
    cout << "result2 = " << result2 << endl;
    
    return 0;
}
