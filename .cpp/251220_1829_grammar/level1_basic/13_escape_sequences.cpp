/*
 * 1단계 예제 13: 이스케이프 시퀀스 (Escape Sequences)
 * 
 * 특수 문자를 표현하기 위한 이스케이프 시퀀스를 학습합니다.
 * 백슬래시(\)로 시작하는 특수 문자입니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 이스케이프 시퀀스
    cout << "=== 기본 이스케이프 시퀀스 ===" << endl;
    
    // \n: 새 줄 (줄바꿈)
    cout << "첫 번째 줄\n두 번째 줄\n세 번째 줄" << endl;
    
    // \t: 탭 (수평 탭)
    cout << "\n탭 사용:\n이름\t나이\t직업" << endl;
    cout << "홍길동\t25\t학생" << endl;
    cout << "김철수\t30\t개발자" << endl;
    
    // \\: 백슬래시 자체
    cout << "\n백슬래시: C:\\Users\\Documents\\file.txt" << endl;
    
    // \": 큰따옴표
    cout << "문자열: \"Hello World\"" << endl;
    
    // \': 작은따옴표 (문자열에서는 선택적)
    cout << "문자: \'A\'" << endl;
    
    // \0: 널 문자 (문자열 종료)
    char str[] = "Hello\0World";
    cout << "\n널 문자: " << str << endl;  // "Hello"만 출력됨
    
    // \a: 경고음 (벨)
    // cout << "\a";  // 시스템에 따라 소리 발생
    
    // \b: 백스페이스
    cout << "백스페이스: ABC\bD" << endl;  // "ABD" 출력 (C가 지워짐)
    
    // \r: 캐리지 리턴 (줄의 시작으로 이동)
    cout << "캐리지 리턴: 12345\rABC" << endl;  // "ABC45" 출력
    
    // \v: 수직 탭
    cout << "수직 탭:\v테스트" << endl;
    
    // \f: 폼 피드 (페이지 나누기)
    // cout << "폼 피드\f다음 페이지" << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 파일 경로
    cout << "파일 경로: C:\\Program Files\\MyApp\\config.ini" << endl;
    
    // 여러 줄 문자열 (시각적)
    cout << "\n여러 줄 출력:" << endl;
    cout << "첫 번째 줄\n";
    cout << "\t들여쓰기된 두 번째 줄\n";
    cout << "\t\t더 들여쓰기된 세 번째 줄" << endl;
    
    // 테이블 형식 출력
    cout << "\n테이블 형식:" << endl;
    cout << "번호\t이름\t\t점수" << endl;
    cout << "1\t홍길동\t\t95" << endl;
    cout << "2\t김철수\t\t87" << endl;
    cout << "3\t이영희\t\t92" << endl;
    
    // 따옴표 포함 문자열
    cout << "\n따옴표 포함:" << endl;
    cout << "그가 말했다: \"안녕하세요!\"" << endl;
    cout << "문자열: 'Hello'" << endl;
    
    // 특수 문자 출력
    cout << "\n특수 문자:" << endl;
    cout << "백슬래시: \\" << endl;
    cout << "큰따옴표: \"" << endl;
    cout << "작은따옴표: \'" << endl;
    
    return 0;
}
