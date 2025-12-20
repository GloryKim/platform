/*
 * 2단계 예제 11: 배열 기본
 * 
 * 같은 타입의 여러 데이터를 저장하는 배열을 학습합니다.
 * 배열은 연속된 메모리 공간에 저장됩니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 배열 선언 및 초기화
    cout << "=== 배열 선언 및 초기화 ===" << endl;
    
    // 방법 1: 크기 지정 후 초기화
    int arr1[5] = {1, 2, 3, 4, 5};
    
    // 방법 2: 크기 자동 추론
    int arr2[] = {10, 20, 30, 40, 50};
    
    // 방법 3: 부분 초기화 (나머지는 0)
    int arr3[5] = {1, 2};  // {1, 2, 0, 0, 0}
    
    // 방법 4: 모두 0으로 초기화
    int arr4[5] = {0};
    
    // 배열 요소 접근
    cout << "\n=== 배열 요소 접근 ===" << endl;
    cout << "arr1[0] = " << arr1[0] << endl;
    cout << "arr1[2] = " << arr1[2] << endl;
    cout << "arr1[4] = " << arr1[4] << endl;
    
    // 배열 요소 수정
    arr1[0] = 100;
    cout << "수정 후 arr1[0] = " << arr1[0] << endl;
    
    // 배열 전체 출력
    cout << "\n=== 배열 전체 출력 ===" << endl;
    cout << "arr1: ";
    for (int i = 0; i < 5; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    // 배열 크기 계산
    cout << "\n=== 배열 크기 계산 ===" << endl;
    int size = sizeof(arr1) / sizeof(arr1[0]);
    cout << "arr1의 크기: " << size << endl;
    cout << "배열 전체 크기: " << sizeof(arr1) << " 바이트" << endl;
    cout << "요소 하나 크기: " << sizeof(arr1[0]) << " 바이트" << endl;
    
    // 범위 기반 for 루프 (C++11)
    cout << "\n=== 범위 기반 for 루프 ===" << endl;
    cout << "arr2: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    // 배열 복사 (요소별)
    cout << "\n=== 배열 복사 ===" << endl;
    int source[] = {1, 2, 3, 4, 5};
    int dest[5];
    
    for (int i = 0; i < 5; i++) {
        dest[i] = source[i];
    }
    
    cout << "복사된 배열: ";
    for (int num : dest) {
        cout << num << " ";
    }
    cout << endl;
    
    // 배열 합계 계산
    cout << "\n=== 배열 합계 계산 ===" << endl;
    int numbers[] = {10, 20, 30, 40, 50};
    int sum = 0;
    
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    cout << "합계: " << sum << endl;
    cout << "평균: " << (double)sum / 5 << endl;
    
    // 최대값, 최소값 찾기
    cout << "\n=== 최대값, 최소값 찾기 ===" << endl;
    int scores[] = {85, 92, 78, 96, 88};
    int max = scores[0];
    int min = scores[0];
    
    for (int i = 1; i < 5; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
        if (scores[i] < min) {
            min = scores[i];
        }
    }
    
    cout << "최대값: " << max << endl;
    cout << "최소값: " << min << endl;
    
    // 배열 검색
    cout << "\n=== 배열 검색 ===" << endl;
    int target = 30;
    bool found = false;
    int index = -1;
    
    for (int i = 0; i < 5; i++) {
        if (numbers[i] == target) {
            found = true;
            index = i;
            break;
        }
    }
    
    if (found) {
        cout << target << "을(를) " << index << "번째 위치에서 찾았습니다." << endl;
    } else {
        cout << target << "을(를) 찾을 수 없습니다." << endl;
    }
    
    // 문자 배열 (문자열)
    cout << "\n=== 문자 배열 (문자열) ===" << endl;
    char str1[] = "Hello";
    char str2[10] = "World";
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    
    // 문자 배열 출력 (문자별)
    cout << "str1 문자별: ";
    for (int i = 0; str1[i] != '\0'; i++) {
        cout << str1[i] << " ";
    }
    cout << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 학생 점수 관리
    int studentScores[] = {95, 87, 92, 78, 88};
    string studentNames[] = {"홍길동", "김철수", "이영희", "박민수", "최지영"};
    
    cout << "학생 점수:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << studentNames[i] << ": " << studentScores[i] << "점" << endl;
    }
    
    // 평균 계산
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += studentScores[i];
    }
    cout << "평균 점수: " << (double)total / 5 << "점" << endl;
    
    return 0;
}


