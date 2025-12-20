/*
 * 5단계 예제 16: 파일시스템
 * 
 * <filesystem>은 파일과 디렉토리 작업을 제공합니다.
 * C++17에서 도입되었습니다.
 */

#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

int main() {
    // 경로 작업
    cout << "=== 경로 작업 ===" << endl;
    path p1("/usr/local/bin");
    path p2("file.txt");
    
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p1 / p2: " << p1 / p2 << endl;
    
    // 파일 존재 확인
    cout << "\n=== 파일 존재 확인 ===" << endl;
    path filePath("example.txt");
    if (exists(filePath)) {
        cout << "파일이 존재합니다." << endl;
    } else {
        cout << "파일이 존재하지 않습니다." << endl;
    }
    
    // 파일 정보
    cout << "\n=== 파일 정보 ===" << endl;
    if (exists(filePath)) {
        cout << "파일 크기: " << file_size(filePath) << " 바이트" << endl;
        cout << "절대 경로: " << absolute(filePath) << endl;
    }
    
    // 디렉토리 순회
    cout << "\n=== 디렉토리 순회 ===" << endl;
    path currentDir = current_path();
    cout << "현재 디렉토리: " << currentDir << endl;
    
    // 주의: 실제 파일시스템 접근은 환경에 따라 다를 수 있음
    cout << "\n주의: 실제 파일시스템 작업은 환경에 따라 다를 수 있습니다." << endl;
    
    return 0;
}


