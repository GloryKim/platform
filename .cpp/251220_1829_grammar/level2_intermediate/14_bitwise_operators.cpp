/*
 * 2단계 예제 14: 비트 연산자
 * 
 * 비트 단위로 연산하는 비트 연산자를 학습합니다.
 * 저수준 프로그래밍이나 성능 최적화에 유용합니다.
 */

#include <iostream>
#include <bitset>
using namespace std;

int main() {
    // 비트 연산자 종류
    cout << "=== 비트 연산자 종류 ===" << endl;
    int a = 5;   // 0101 (이진수)
    int b = 3;   // 0011 (이진수)
    
    cout << "a = " << a << " (" << bitset<4>(a) << ")" << endl;
    cout << "b = " << b << " (" << bitset<4>(b) << ")" << endl;
    
    // AND 연산 (&)
    cout << "\n=== AND 연산 (&) ===" << endl;
    int result_and = a & b;  // 0101 & 0011 = 0001
    cout << "a & b = " << result_and << " (" << bitset<4>(result_and) << ")" << endl;
    
    // OR 연산 (|)
    cout << "\n=== OR 연산 (|) ===" << endl;
    int result_or = a | b;  // 0101 | 0011 = 0111
    cout << "a | b = " << result_or << " (" << bitset<4>(result_or) << ")" << endl;
    
    // XOR 연산 (^)
    cout << "\n=== XOR 연산 (^) ===" << endl;
    int result_xor = a ^ b;  // 0101 ^ 0011 = 0110
    cout << "a ^ b = " << result_xor << " (" << bitset<4>(result_xor) << ")" << endl;
    
    // NOT 연산 (~)
    cout << "\n=== NOT 연산 (~) ===" << endl;
    int result_not = ~a;  // 비트 반전
    cout << "~a = " << result_not << " (" << bitset<8>(result_not) << ")" << endl;
    
    // 왼쪽 시프트 (<<)
    cout << "\n=== 왼쪽 시프트 (<<) ===" << endl;
    int left_shift = a << 1;  // 0101 << 1 = 1010 (2배)
    cout << "a << 1 = " << left_shift << " (" << bitset<4>(left_shift) << ")" << endl;
    cout << "a << 2 = " << (a << 2) << " (" << bitset<4>(a << 2) << ")" << endl;
    
    // 오른쪽 시프트 (>>)
    cout << "\n=== 오른쪽 시프트 (>>) ===" << endl;
    int right_shift = a >> 1;  // 0101 >> 1 = 0010 (절반)
    cout << "a >> 1 = " << right_shift << " (" << bitset<4>(right_shift) << ")" << endl;
    cout << "a >> 2 = " << (a >> 2) << " (" << bitset<4>(a >> 2) << ")" << endl;
    
    // 복합 할당 연산자
    cout << "\n=== 복합 할당 연산자 ===" << endl;
    int x = 5;
    x &= 3;  // x = x & 3
    cout << "x &= 3: " << x << endl;
    
    x = 5;
    x |= 3;  // x = x | 3
    cout << "x |= 3: " << x << endl;
    
    x = 5;
    x ^= 3;  // x = x ^ 3
    cout << "x ^= 3: " << x << endl;
    
    x = 5;
    x <<= 1;  // x = x << 1
    cout << "x <<= 1: " << x << endl;
    
    x = 5;
    x >>= 1;  // x = x >> 1
    cout << "x >>= 1: " << x << endl;
    
    // 실제 사용 예제 1: 짝수/홀수 판별
    cout << "\n=== 실제 사용 예제 1: 짝수/홀수 판별 ===" << endl;
    int num = 7;
    if (num & 1) {
        cout << num << "은(는) 홀수입니다." << endl;
    } else {
        cout << num << "은(는) 짝수입니다." << endl;
    }
    
    // 실제 사용 예제 2: 2의 거듭제곱 확인
    cout << "\n=== 실제 사용 예제 2: 2의 거듭제곱 확인 ===" << endl;
    int power = 8;
    if ((power & (power - 1)) == 0 && power != 0) {
        cout << power << "은(는) 2의 거듭제곱입니다." << endl;
    } else {
        cout << power << "은(는) 2의 거듭제곱이 아닙니다." << endl;
    }
    
    // 실제 사용 예제 3: 비트 플래그
    cout << "\n=== 실제 사용 예제 3: 비트 플래그 ===" << endl;
    const int FLAG_READ = 1;      // 0001
    const int FLAG_WRITE = 2;     // 0010
    const int FLAG_EXECUTE = 4;   // 0100
    
    int permissions = FLAG_READ | FLAG_WRITE;  // 읽기와 쓰기 권한
    
    if (permissions & FLAG_READ) {
        cout << "읽기 권한 있음" << endl;
    }
    if (permissions & FLAG_WRITE) {
        cout << "쓰기 권한 있음" << endl;
    }
    if (permissions & FLAG_EXECUTE) {
        cout << "실행 권한 있음" << endl;
    }
    
    // 실제 사용 예제 4: 빠른 곱셈/나눗셈
    cout << "\n=== 실제 사용 예제 4: 빠른 곱셈/나눗셈 ===" << endl;
    int value = 10;
    cout << value << " * 2 = " << (value << 1) << endl;  // 2배
    cout << value << " * 4 = " << (value << 2) << endl;  // 4배
    cout << value << " / 2 = " << (value >> 1) << endl;  // 절반
    cout << value << " / 4 = " << (value >> 2) << endl;  // 1/4
    
    // 실제 사용 예제 5: 비트 개수 세기
    cout << "\n=== 실제 사용 예제 5: 비트 개수 세기 ===" << endl;
    int number = 15;  // 1111
    int bitCount = 0;
    int temp = number;
    
    while (temp != 0) {
        if (temp & 1) {
            bitCount++;
        }
        temp >>= 1;
    }
    
    cout << number << "의 1 비트 개수: " << bitCount << endl;
    
    // 실제 사용 예제 6: 비트 토글
    cout << "\n=== 실제 사용 예제 6: 비트 토글 ===" << endl;
    int flags = 5;  // 0101
    int bitPos = 1;  // 두 번째 비트 토글
    
    flags ^= (1 << bitPos);  // 비트 토글
    cout << "토글 후: " << flags << " (" << bitset<4>(flags) << ")" << endl;
    
    return 0;
}



