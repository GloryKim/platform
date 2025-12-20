/*
 * 2단계 예제 6: 중첩 루프
 * 
 * 루프 안에 루프를 넣는 중첩 루프를 학습합니다.
 * 2차원 데이터 처리에 유용합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 기본 중첩 for 루프
    cout << "=== 기본 중첩 for 루프 ===" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "(" << i << ", " << j << ") ";
        }
        cout << endl;
    }
    
    // 구구단 출력
    cout << "\n=== 구구단 출력 ===" << endl;
    for (int i = 2; i <= 9; i++) {
        cout << i << "단: ";
        for (int j = 1; j <= 9; j++) {
            cout << i << "x" << j << "=" << (i * j) << "\t";
        }
        cout << endl;
    }
    
    // 별 찍기 - 직각삼각형
    cout << "\n=== 별 찍기 - 직각삼각형 ===" << endl;
    int rows = 5;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    
    // 별 찍기 - 역직각삼각형
    cout << "\n=== 별 찍기 - 역직각삼각형 ===" << endl;
    for (int i = rows; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    
    // 별 찍기 - 피라미드
    cout << "\n=== 별 찍기 - 피라미드 ===" << endl;
    for (int i = 1; i <= rows; i++) {
        // 공백 출력
        for (int j = 1; j <= rows - i; j++) {
            cout << " ";
        }
        // 별 출력
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }
    
    // 2차원 배열 처리
    cout << "\n=== 2차원 배열 처리 ===" << endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    cout << "행렬 출력:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 행 합계 계산
    cout << "\n행 합계:" << endl;
    for (int i = 0; i < 3; i++) {
        int rowSum = 0;
        for (int j = 0; j < 4; j++) {
            rowSum += matrix[i][j];
        }
        cout << "행 " << i << "의 합: " << rowSum << endl;
    }
    
    // 열 합계 계산
    cout << "\n열 합계:" << endl;
    for (int j = 0; j < 4; j++) {
        int colSum = 0;
        for (int i = 0; i < 3; i++) {
            colSum += matrix[i][j];
        }
        cout << "열 " << j << "의 합: " << colSum << endl;
    }
    
    // 행렬 곱셈 (간단한 예제)
    cout << "\n=== 행렬 곱셈 (간단한 예제) ===" << endl;
    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int B[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int C[2][2] = {0};
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    cout << "행렬 곱셈 결과:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 소수 찾기 (에라토스테네스의 체 개념)
    cout << "\n=== 소수 찾기 (2~30) ===" << endl;
    for (int num = 2; num <= 30; num++) {
        bool isPrime = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << num << " ";
        }
    }
    cout << endl;
    
    // 중첩 while 루프
    cout << "\n=== 중첩 while 루프 ===" << endl;
    int i = 1;
    while (i <= 3) {
        int j = 1;
        while (j <= 3) {
            cout << i * j << " ";
            j++;
        }
        cout << endl;
        i++;
    }
    
    // break와 continue의 범위
    cout << "\n=== break와 continue의 범위 ===" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 3) {
                break;  // 내부 루프만 종료
            }
            cout << "(" << i << ", " << j << ") ";
        }
        cout << endl;
    }
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 표 형식 출력
    cout << "학생별 과목 점수:" << endl;
    string students[] = {"홍길동", "김철수", "이영희"};
    string subjects[] = {"수학", "영어", "과학"};
    int scores[3][3] = {
        {95, 87, 92},
        {88, 91, 85},
        {90, 89, 94}
    };
    
    cout << "\t";
    for (int j = 0; j < 3; j++) {
        cout << subjects[j] << "\t";
    }
    cout << "평균" << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << students[i] << "\t";
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            cout << scores[i][j] << "\t";
            sum += scores[i][j];
        }
        cout << sum / 3.0 << endl;
    }
    
    return 0;
}
