/*
 * 3단계 예제 4: 재귀 함수
 * 
 * 함수가 자기 자신을 호출하는 재귀 함수를 학습합니다.
 * 복잡한 문제를 간단하게 해결할 수 있지만 주의가 필요합니다.
 */

#include <iostream>
using namespace std;

// 팩토리얼 계산
long long factorial(int n) {
    // 기본 경우 (Base Case)
    if (n <= 1) {
        return 1;
    }
    // 재귀 경우 (Recursive Case)
    return n * factorial(n - 1);
}

// 피보나치 수열
int fibonacci(int n) {
    // 기본 경우
    if (n <= 1) {
        return n;
    }
    // 재귀 경우
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 거듭제곱 계산
int power(int base, int exponent) {
    // 기본 경우
    if (exponent == 0) {
        return 1;
    }
    // 재귀 경우
    return base * power(base, exponent - 1);
}

// 최대공약수 (GCD)
int gcd(int a, int b) {
    // 기본 경우
    if (b == 0) {
        return a;
    }
    // 재귀 경우
    return gcd(b, a % b);
}

// 숫자 자릿수 합계
int sumOfDigits(int n) {
    // 기본 경우
    if (n == 0) {
        return 0;
    }
    // 재귀 경우
    return (n % 10) + sumOfDigits(n / 10);
}

// 배열 합계
int arraySum(int arr[], int size) {
    // 기본 경우
    if (size == 0) {
        return 0;
    }
    // 재귀 경우
    return arr[0] + arraySum(arr + 1, size - 1);
}

// 하노이 탑
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "원반 1을 " << from << "에서 " << to << "로 이동" << endl;
        return;
    }
    hanoi(n - 1, from, aux, to);
    cout << "원반 " << n << "을 " << from << "에서 " << to << "로 이동" << endl;
    hanoi(n - 1, aux, to, from);
}

int main() {
    // 팩토리얼
    cout << "=== 팩토리얼 ===" << endl;
    for (int i = 0; i <= 5; i++) {
        cout << i << "! = " << factorial(i) << endl;
    }
    
    // 피보나치 수열
    cout << "\n=== 피보나치 수열 ===" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "fibonacci(" << i << ") = " << fibonacci(i) << endl;
    }
    
    // 거듭제곱
    cout << "\n=== 거듭제곱 ===" << endl;
    cout << "2^10 = " << power(2, 10) << endl;
    cout << "3^5 = " << power(3, 5) << endl;
    
    // 최대공약수
    cout << "\n=== 최대공약수 ===" << endl;
    cout << "GCD(48, 18) = " << gcd(48, 18) << endl;
    cout << "GCD(17, 13) = " << gcd(17, 13) << endl;
    
    // 숫자 자릿수 합계
    cout << "\n=== 숫자 자릿수 합계 ===" << endl;
    cout << "sumOfDigits(12345) = " << sumOfDigits(12345) << endl;
    cout << "sumOfDigits(987) = " << sumOfDigits(987) << endl;
    
    // 배열 합계
    cout << "\n=== 배열 합계 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    cout << "배열 합계: " << arraySum(arr, 5) << endl;
    
    // 하노이 탑
    cout << "\n=== 하노이 탑 (3개 원반) ===" << endl;
    hanoi(3, 'A', 'C', 'B');
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 기본 경우(Base Case)가 반드시 있어야 함" << endl;
    cout << "2. 재귀 호출이 기본 경우로 수렴해야 함" << endl;
    cout << "3. 스택 오버플로우 주의 (깊은 재귀)" << endl;
    cout << "4. 반복문으로도 구현 가능한 경우가 많음" << endl;
    cout << "5. 메모이제이션으로 성능 개선 가능" << endl;
    
    return 0;
}



