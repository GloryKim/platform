/*
 * 2단계 예제 12: 다차원 배열
 * 
 * 2차원 이상의 배열을 학습합니다.
 * 행렬이나 표 형태의 데이터를 표현할 때 유용합니다.
 */

#include <iostream>
using namespace std;

int main() {
    // 2차원 배열 선언 및 초기화
    cout << "=== 2차원 배열 선언 및 초기화 ===" << endl;
    
    // 방법 1: 초기화 리스트 사용
    int matrix1[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // 방법 2: 일차원으로 초기화
    int matrix2[2][3] = {1, 2, 3, 4, 5, 6};
    
    // 방법 3: 부분 초기화
    int matrix3[3][3] = {
        {1, 2},
        {4, 5, 6},
        {7}
    };
    
    // 2차원 배열 출력
    cout << "\n=== 2차원 배열 출력 ===" << endl;
    cout << "matrix1:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix1[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 배열 요소 접근
    cout << "\n=== 배열 요소 접근 ===" << endl;
    cout << "matrix1[0][0] = " << matrix1[0][0] << endl;
    cout << "matrix1[1][2] = " << matrix1[1][2] << endl;
    cout << "matrix1[2][3] = " << matrix1[2][3] << endl;
    
    // 배열 요소 수정
    matrix1[0][0] = 100;
    cout << "수정 후 matrix1[0][0] = " << matrix1[0][0] << endl;
    
    // 행 합계 계산
    cout << "\n=== 행 합계 계산 ===" << endl;
    for (int i = 0; i < 3; i++) {
        int rowSum = 0;
        for (int j = 0; j < 4; j++) {
            rowSum += matrix1[i][j];
        }
        cout << "행 " << i << "의 합: " << rowSum << endl;
    }
    
    // 열 합계 계산
    cout << "\n=== 열 합계 계산 ===" << endl;
    for (int j = 0; j < 4; j++) {
        int colSum = 0;
        for (int i = 0; i < 3; i++) {
            colSum += matrix1[i][j];
        }
        cout << "열 " << j << "의 합: " << colSum << endl;
    }
    
    // 전체 합계 계산
    cout << "\n=== 전체 합계 계산 ===" << endl;
    int total = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            total += matrix1[i][j];
        }
    }
    cout << "전체 합계: " << total << endl;
    
    // 최대값, 최소값 찾기
    cout << "\n=== 최대값, 최소값 찾기 ===" << endl;
    int max = matrix1[0][0];
    int min = matrix1[0][0];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix1[i][j] > max) {
                max = matrix1[i][j];
            }
            if (matrix1[i][j] < min) {
                min = matrix1[i][j];
            }
        }
    }
    
    cout << "최대값: " << max << endl;
    cout << "최소값: " << min << endl;
    
    // 행렬 전치 (Transpose)
    cout << "\n=== 행렬 전치 ===" << endl;
    int original[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    cout << "원본 행렬:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << original[i][j] << "\t";
        }
        cout << endl;
    }
    
    cout << "전치 행렬:" << endl;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 2; i++) {
            cout << original[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 3차원 배열
    cout << "\n=== 3차원 배열 ===" << endl;
    int cube[2][2][2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    
    cout << "3차원 배열:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                cout << "cube[" << i << "][" << j << "][" << k << "] = " 
                     << cube[i][j][k] << endl;
            }
        }
    }
    
    // 실제 사용 예제 1: 성적표
    cout << "\n=== 실제 사용 예제 1: 성적표 ===" << endl;
    int scores[3][4] = {
        {95, 87, 92, 88},
        {78, 85, 90, 82},
        {88, 91, 85, 89}
    };
    string students[] = {"홍길동", "김철수", "이영희"};
    string subjects[] = {"수학", "영어", "과학", "사회"};
    
    cout << "\t";
    for (int j = 0; j < 4; j++) {
        cout << subjects[j] << "\t";
    }
    cout << "평균" << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << students[i] << "\t";
        int sum = 0;
        for (int j = 0; j < 4; j++) {
            cout << scores[i][j] << "\t";
            sum += scores[i][j];
        }
        cout << (double)sum / 4 << endl;
    }
    
    // 실제 사용 예제 2: 게임 보드
    cout << "\n=== 실제 사용 예제 2: 게임 보드 ===" << endl;
    char board[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'X', 'O', 'X'}
    };
    
    cout << "틱택토 보드:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
