/*
 * 1단계 예제 3: 입출력 (cin, cout)
 * 
 * C++에서 데이터를 입력받고 출력하는 방법을 학습합니다.
 * cin: 입력 스트림 (키보드로부터 입력)
 * cout: 출력 스트림 (화면으로 출력)
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // 변수 선언
    int num;
    double price;
    string name;
    char grade;
    
    // 출력 후 입력받기
    cout << "이름을 입력하세요: ";
    cin >> name;                     // 문자열 입력
    
    cout << "나이를 입력하세요: ";
    cin >> num;                      // 정수 입력
    
    cout << "가격을 입력하세요: ";
    cin >> price;                    // 실수 입력
    
    cout << "등급을 입력하세요 (A-F): ";
    cin >> grade;                    // 문자 입력
    
    // 여러 값을 한 번에 입력받기
    int a, b, c;
    cout << "\n세 개의 정수를 입력하세요 (공백으로 구분): ";
    cin >> a >> b >> c;              // 여러 값 연속 입력
    
    // 결과 출력
    cout << "\n=== 입력된 정보 ===" << endl;
    cout << "이름: " << name << endl;
    cout << "나이: " << num << "세" << endl;
    cout << "가격: " << price << "원" << endl;
    cout << "등급: " << grade << endl;
    cout << "세 정수: " << a << ", " << b << ", " << c << endl;
    
    // getline으로 공백 포함 문자열 입력
    string fullName;
    cin.ignore();                    // 이전 입력 버퍼 비우기
    cout << "\n전체 이름을 입력하세요 (공백 포함): ";
    getline(cin, fullName);          // 공백 포함 문자열 입력
    cout << "전체 이름: " << fullName << endl;
    
    return 0;
}



