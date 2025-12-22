/*
 * 4단계 예제 19: 예외 처리
 * 
 * try-catch를 사용하여 예외를 처리합니다.
 * 프로그램의 안정성을 높이고 에러를 체계적으로 관리합니다.
 */

#include <iostream>
#include <stdexcept>
using namespace std;

// 사용자 정의 예외
class DivisionByZeroException : public exception {
public:
    const char* what() const noexcept override {
        return "0으로 나눌 수 없습니다!";
    }
};

double divide(double a, double b) {
    if (b == 0) {
        throw DivisionByZeroException();
    }
    return a / b;
}

int main() {
    // 기본 예외 처리
    cout << "=== 기본 예외 처리 ===" << endl;
    try {
        double result = divide(10, 2);
        cout << "결과: " << result << endl;
        
        result = divide(10, 0);
        cout << "결과: " << result << endl;
    } catch (const DivisionByZeroException& e) {
        cout << "예외 발생: " << e.what() << endl;
    }
    
    // 여러 예외 처리
    cout << "\n=== 여러 예외 처리 ===" << endl;
    try {
        vector<int> v(5);
        // v.at(10) = 100;  // out_of_range 예외
        
        int* ptr = nullptr;
        // *ptr = 10;  // 예외 발생 가능
    } catch (const out_of_range& e) {
        cout << "범위 오류: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "일반 예외: " << e.what() << endl;
    } catch (...) {
        cout << "알 수 없는 예외" << endl;
    }
    
    // 예외 전파
    cout << "\n=== 예외 전파 ===" << endl;
    try {
        try {
            throw runtime_error("내부 예외");
        } catch (const runtime_error& e) {
            cout << "내부 처리: " << e.what() << endl;
            throw;  // 예외 재전파
        }
    } catch (const runtime_error& e) {
        cout << "외부 처리: " << e.what() << endl;
    }
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. 예외는 예외적인 상황에만 사용" << endl;
    cout << "2. 성능 오버헤드 있음" << endl;
    cout << "3. RAII 패턴과 함께 사용" << endl;
    cout << "4. 예외 안전성 보장" << endl;
    
    return 0;
}



