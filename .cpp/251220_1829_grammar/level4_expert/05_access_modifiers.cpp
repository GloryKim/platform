/*
 * 4단계 예제 5: 접근 제어자
 * 
 * public, private, protected는 클래스 멤버의 접근 권한을 제어합니다.
 * 캡슐화를 구현하는 핵심 메커니즘입니다.
 */

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // private: 클래스 내부에서만 접근 가능
    double balance;
    string accountNumber;
    
protected:
    // protected: 클래스와 파생 클래스에서 접근 가능
    string ownerName;
    
public:
    // public: 어디서나 접근 가능
    BankAccount(string accNum, string owner, double initialBalance) 
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {}
    
    // 접근자
    double getBalance() const {
        return balance;
    }
    
    string getAccountNumber() const {
        return accountNumber;
    }
    
    string getOwnerName() const {
        return ownerName;
    }
    
    // 설정자
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << amount << "원 입금되었습니다." << endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << amount << "원 출금되었습니다." << endl;
            return true;
        }
        cout << "출금 실패: 잔액 부족" << endl;
        return false;
    }
    
    void display() const {
        cout << "계좌번호: " << accountNumber << endl;
        cout << "소유자: " << ownerName << endl;
        cout << "잔액: " << balance << "원" << endl;
    }
};

// 파생 클래스
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string owner, double balance, double rate)
        : BankAccount(accNum, owner, balance), interestRate(rate) {}
    
    void addInterest() {
        // protected 멤버 접근 가능
        double interest = getBalance() * interestRate;
        deposit(interest);
        cout << "이자 " << interest << "원 추가되었습니다." << endl;
    }
    
    void display() const {
        BankAccount::display();
        cout << "이자율: " << (interestRate * 100) << "%" << endl;
    }
};

int main() {
    // public 멤버 접근
    cout << "=== public 멤버 접근 ===" << endl;
    BankAccount account("123-456-789", "홍길동", 10000.0);
    account.display();
    account.deposit(5000.0);
    account.withdraw(2000.0);
    cout << "현재 잔액: " << account.getBalance() << "원" << endl;
    
    // private 멤버 접근 시도 (에러)
    // account.balance = 100000;  // 에러! private 멤버 접근 불가
    
    // protected 멤버 접근
    cout << "\n=== protected 멤버 접근 ===" << endl;
    SavingsAccount savings("987-654-321", "김철수", 50000.0, 0.05);
    savings.display();
    savings.addInterest();
    savings.display();
    
    // 접근 제어자 요약
    cout << "\n=== 접근 제어자 요약 ===" << endl;
    cout << "public: 어디서나 접근 가능" << endl;
    cout << "private: 클래스 내부에서만 접근 가능" << endl;
    cout << "protected: 클래스와 파생 클래스에서 접근 가능" << endl;
    
    return 0;
}


