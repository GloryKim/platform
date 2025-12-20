/*
 * 4단계 예제 14: STL stack
 * 
 * stack은 LIFO(Last In First Out) 자료구조입니다.
 * 스택의 맨 위에서만 추가/삭제가 가능합니다.
 */

#include <iostream>
#include <stack>
using namespace std;

int main() {
    // stack 선언
    cout << "=== stack 선언 ===" << endl;
    stack<int> s;
    
    // 요소 추가
    cout << "\n=== 요소 추가 ===" << endl;
    s.push(10);
    s.push(20);
    s.push(30);
    
    cout << "스택 크기: " << s.size() << endl;
    
    // 요소 접근
    cout << "\n=== 요소 접근 ===" << endl;
    cout << "top: " << s.top() << endl;
    
    // 요소 삭제
    cout << "\n=== 요소 삭제 ===" << endl;
    while (!s.empty()) {
        cout << "제거: " << s.top() << endl;
        s.pop();
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 괄호 매칭
    stack<char> brackets;
    string expression = "((()))";
    bool balanced = true;
    
    for (char c : expression) {
        if (c == '(') {
            brackets.push(c);
        } else if (c == ')') {
            if (brackets.empty()) {
                balanced = false;
                break;
            }
            brackets.pop();
        }
    }
    
    if (balanced && brackets.empty()) {
        cout << "괄호가 올바르게 매칭되었습니다." << endl;
    } else {
        cout << "괄호가 올바르게 매칭되지 않았습니다." << endl;
    }
    
    return 0;
}


