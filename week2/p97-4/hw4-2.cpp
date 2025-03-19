#include <iostream>
#include <conio.h>
using namespace std;

// 자릿수 구하기 함수
int digitCount(int num) {
    int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

// 점수 계산 함수
int calculateScore(int attemptsUsed, int maxAttempts, int number) {
    int baseScore = 50;
    int digitBonus = digitCount(number) * 10;
    int remainingAttemptsBonus = (maxAttempts - attemptsUsed) * 5;
    return baseScore + digitBonus + remainingAttemptsBonus;
}

int main() {
    int n, min = 1, max = 99, input, i;
    char a, b;
    const int maxAttempts = 10;

    cout << "두 자리 수 입력(1~99): ";

    // 첫 번째 숫자 입력
    a = getch();
    cout << "*";

    // 두 번째 숫자 입력
    b = getch();
    cout << "*\n\n";

    // 입력한 숫자를 정수로 변환
    n = (a - '0') * 10 + (b - '0');

    // 숫자 맞히기 게임 시작
    for (i = 0; i < maxAttempts; i++) {
        cout << "[" << i + 1 << "회] " << min << " ~ " << max << " 사이의 값 예측 => ";

        input = 0;
        char ch;
        while (true) {
            ch = getch();
            if (ch == '\r') break; // Enter 입력 시 종료

            if (ch >= '0' && ch <= '9') {
                cout << "*";
                input = input * 10 + (ch - '0');
            }
        }
        cout << endl;

        if (n == input) break;
        else if (n > input) {
            cout << " 더 큰 숫자입니다!\n";
            min = input;
        }
        else {
            cout << " 더 작은 숫자입니다!\n";
            max = input;
        }
    }

    // 점수 계산
    int finalScore = calculateScore(i + 1, maxAttempts, n);

    cout << "  " << ((n == input) ? "성공" : "실패") << " !!!  정답은 " << n << endl;
    cout << "  최종 점수 = " << finalScore << endl;

    return 0;
}