#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// 사용자 정의 예외 클래스
class AccountException : public exception {
    string message;
    int amount;
public:
    AccountException(const string& msg, int amt)
        : message(msg), amount(amt) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    int getAmount() const { return amount; }
};

// CustomerAccount 클래스
class CustomerAccount {
    int balance;
public:
    CustomerAccount(int b = 0) {
        if (b < 0) throw AccountException("초기 잔고는 음수일 수 없습니다.", b);
        balance = b;
    }

    int getBalance() const { return balance; }

    int deposit(int amount) {
        if (amount <= 0)
            throw AccountException("입금 금액은 0보다 커야 합니다.", amount);
        balance += amount;
        return balance;
    }

    int withdraw(int amount) {
        if (amount > balance)
            throw AccountException("잔고보다 많은 금액은 출금할 수 없습니다.", amount);
        balance -= amount;
        return balance;
    }
};

// main 함수에서 예외 테스트
int main() {
    try {
        CustomerAccount acc(10000); // 정상 생성

        cout << "현재 잔고: " << acc.getBalance() << "원" << endl;

        acc.deposit(5000); // 정상 입금
        cout << "입금 후 잔고: " << acc.getBalance() << "원" << endl;

        acc.withdraw(20000); // 출금 실패 (예외 발생)
    }
    catch (const AccountException& e) {
        cout << "예외 발생: " << e.what() << " (금액: " << e.getAmount() << "원)" << endl;
    }

    try {
        CustomerAccount badAcc(-100); // 음수 잔고로 계좌 생성 → 예외 발생
    }
    catch (const AccountException& e) {
        cout << "예외 발생: " << e.what() << " (금액: " << e.getAmount() << "원)" << endl;
    }

    return 0;
}
