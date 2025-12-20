/*
 * 3단계 예제 6: 동적 메모리
 * 
 * new와 delete를 사용한 동적 메모리 할당과 해제를 학습합니다.
 * 런타임에 메모리를 할당하고 해제할 수 있습니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 단일 변수 동적 할당
    cout << "=== 단일 변수 동적 할당 ===" << endl;
    int* ptr = new int(42);  // int를 동적 할당하고 42로 초기화
    cout << "*ptr = " << *ptr << endl;
    delete ptr;  // 메모리 해제
    ptr = nullptr;  // 널 포인터로 설정 (안전)
    
    // 배열 동적 할당
    cout << "\n=== 배열 동적 할당 ===" << endl;
    int size = 5;
    int* arr = new int[size];  // 5개 int 배열 할당
    
    // 배열 초기화
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }
    
    cout << "동적 배열: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;  // 배열 해제 ([] 필수!)
    arr = nullptr;
    
    // 2차원 배열 동적 할당
    cout << "\n=== 2차원 배열 동적 할당 ===" << endl;
    int rows = 3, cols = 4;
    int** matrix = new int*[rows];  // 행 포인터 배열
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];  // 각 행에 열 배열 할당
    }
    
    // 초기화
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    
    // 출력
    cout << "2차원 배열:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 해제 (할당의 역순)
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    // 동적 할당 실패 처리
    cout << "\n=== 동적 할당 실패 처리 ===" << endl;
    int* largeArray = nullptr;
    try {
        largeArray = new int[1000000000];  // 매우 큰 배열
        delete[] largeArray;
    } catch (bad_alloc& e) {
        cout << "메모리 할당 실패: " << e.what() << endl;
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 사용자 입력 크기로 배열 생성
    int userSize = 5;  // 시뮬레이션
    int* userArray = new int[userSize];
    
    for (int i = 0; i < userSize; i++) {
        userArray[i] = (i + 1) * 10;
    }
    
    cout << "사용자 배열: ";
    for (int i = 0; i < userSize; i++) {
        cout << userArray[i] << " ";
    }
    cout << endl;
    
    delete[] userArray;
    userArray = nullptr;
    
    // 주의사항
    cout << "\n=== 주의사항 ===" << endl;
    cout << "1. new로 할당한 메모리는 반드시 delete로 해제" << endl;
    cout << "2. 배열은 delete[] 사용 (delete 아님!)" << endl;
    cout << "3. 해제 후 포인터를 nullptr로 설정" << endl;
    cout << "4. 이미 해제된 메모리 다시 해제 금지" << endl;
    cout << "5. 메모리 누수 방지를 위해 RAII 패턴 사용 권장" << endl;
    
    return 0;
}



