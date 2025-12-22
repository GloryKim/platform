/*
 * 1단계 예제 6: 논리 연산자
 * 
 * 논리 연산자 &&(AND), ||(OR), !(NOT)를 학습합니다.
 * 조건문과 함께 자주 사용됩니다.
 */

#include <iostream>
using namespace std;

int main() {
    bool a = true, b = false;
    
    cout << "a = " << a << ", b = " << b << endl << endl;
    
    // 논리 AND (&&)
    // 둘 다 true일 때만 true
    cout << "논리 AND (&&):" << endl;
    cout << "a && a: " << (a && a) << endl;      // true && true = true (1)
    cout << "a && b: " << (a && b) << endl;      // true && false = false (0)
    cout << "b && b: " << (b && b) << endl;      // false && false = false (0)
    
    // 논리 OR (||)
    // 하나라도 true이면 true
    cout << "\n논리 OR (||):" << endl;
    cout << "a || a: " << (a || a) << endl;      // true || true = true (1)
    cout << "a || b: " << (a || b) << endl;      // true || false = true (1)
    cout << "b || b: " << (b || b) << endl;      // false || false = false (0)
    
    // 논리 NOT (!)
    // true는 false로, false는 true로
    cout << "\n논리 NOT (!):" << endl;
    cout << "!a: " << (!a) << endl;              // !true = false (0)
    cout << "!b: " << (!b) << endl;              // !false = true (1)
    cout << "!!a: " << (!!a) << endl;            // !!true = true (1)
    
    // 실제 사용 예제
    int age = 20;
    bool hasLicense = true;
    bool hasInsurance = false;
    
    cout << "\n실제 사용 예제:" << endl;
    cout << "나이: " << age << ", 면허: " << hasLicense 
         << ", 보험: " << hasInsurance << endl;
    
    // 운전 가능 조건: 나이 18세 이상 AND 면허 있음
    bool canDrive = (age >= 18) && hasLicense;
    cout << "운전 가능: " << canDrive << endl;
    
    // 할인 조건: 나이 65세 이상 OR 보험 있음
    bool hasDiscount = (age >= 65) || hasInsurance;
    cout << "할인 가능: " << hasDiscount << endl;
    
    // 복합 조건
    bool complexCondition = (age >= 18 && age < 65) && (hasLicense || hasInsurance);
    cout << "복합 조건: " << complexCondition << endl;
    
    // 단락 평가 (Short-circuit evaluation)
    cout << "\n단락 평가 예제:" << endl;
    int x = 0;
    bool result1 = (x != 0) && (10 / x > 1);  // x != 0이 false이므로 나눗셈 수행 안 함
    cout << "result1: " << result1 << endl;    // 안전하게 false
    
    bool result2 = (x == 0) || (10 / x > 1);   // x == 0이 true이므로 나눗셈 수행 안 함
    cout << "result2: " << result2 << endl;    // 안전하게 true
    
    return 0;
}



