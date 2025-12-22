/*
 * 1단계 예제 16: 난수 생성
 * 
 * C++에서 난수를 생성하는 방법을 학습합니다.
 * <cstdlib>와 <ctime> 또는 <random> 헤더를 사용합니다.
 */

#include <iostream>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <random>   // C++11 난수 생성기 (더 권장)
using namespace std;

int main() {
    // 방법 1: C 스타일 난수 (rand, srand)
    cout << "=== C 스타일 난수 (rand, srand) ===" << endl;
    
    srand(time(0));  // 시드 설정 (현재 시간 사용)
    
    // 0부터 RAND_MAX까지의 난수
    int random1 = rand();
    cout << "rand(): " << random1 << endl;
    
    // 0부터 9까지의 난수
    int random2 = rand() % 10;
    cout << "rand() % 10: " << random2 << endl;
    
    // 1부터 6까지의 난수 (주사위)
    int dice = rand() % 6 + 1;
    cout << "주사위: " << dice << endl;
    
    // 10부터 20까지의 난수
    int random3 = rand() % 11 + 10;  // (20-10+1) = 11개, 시작값 10
    cout << "10~20 사이 난수: " << random3 << endl;
    
    // 여러 개의 난수 생성
    cout << "\n10개의 난수 (1~100):" << endl;
    for (int i = 0; i < 10; i++) {
        cout << rand() % 100 + 1 << " ";
    }
    cout << endl;
    
    // 방법 2: C++11 스타일 난수 (권장)
    cout << "\n=== C++11 스타일 난수 (권장) ===" << endl;
    
    random_device rd;              // 하드웨어 기반 난수 생성기
    mt19937 gen(rd());             // 메르센 트위스터 엔진
    uniform_int_distribution<> dis(1, 6);  // 1부터 6까지 균등 분포
    
    cout << "주사위 (C++11): ";
    for (int i = 0; i < 10; i++) {
        cout << dis(gen) << " ";
    }
    cout << endl;
    
    // 다양한 범위의 난수
    uniform_int_distribution<> dis1(0, 9);      // 0~9
    uniform_int_distribution<> dis2(10, 20);     // 10~20
    uniform_int_distribution<> dis3(1, 100);     // 1~100
    
    cout << "\n다양한 범위:" << endl;
    cout << "0~9: " << dis1(gen) << endl;
    cout << "10~20: " << dis2(gen) << endl;
    cout << "1~100: " << dis3(gen) << endl;
    
    // 실수 난수
    uniform_real_distribution<double> disReal(0.0, 1.0);  // 0.0~1.0
    cout << "\n실수 난수 (0.0~1.0): " << disReal(gen) << endl;
    
    uniform_real_distribution<double> disReal2(10.5, 20.5);  // 10.5~20.5
    cout << "실수 난수 (10.5~20.5): " << disReal2(gen) << endl;
    
    // 정규 분포 (가우시안 분포)
    normal_distribution<double> disNormal(50.0, 10.0);  // 평균 50, 표준편차 10
    cout << "\n정규 분포 난수 (평균 50, 표준편차 10): " << disNormal(gen) << endl;
    
    // 실제 사용 예제
    cout << "\n=== 실제 사용 예제 ===" << endl;
    
    // 로또 번호 생성 (1~45, 중복 없이 6개)
    cout << "로또 번호 (1~45, 6개): ";
    bool used[46] = {false};
    int count = 0;
    uniform_int_distribution<> lotto(1, 45);
    
    while (count < 6) {
        int num = lotto(gen);
        if (!used[num]) {
            used[num] = true;
            cout << num << " ";
            count++;
        }
    }
    cout << endl;
    
    // 동전 던지기 시뮬레이션
    uniform_int_distribution<> coin(0, 1);
    int heads = 0, tails = 0;
    for (int i = 0; i < 1000; i++) {
        if (coin(gen) == 0) heads++;
        else tails++;
    }
    cout << "\n동전 1000번 던지기:" << endl;
    cout << "앞면: " << heads << ", 뒷면: " << tails << endl;
    
    return 0;
}



