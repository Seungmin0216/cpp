#include <iostream>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <conio.h>  // getch()
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
    const int maxAttempts = 10;

    // 랜덤 시드 설정
    srand(time(0));

    // 1~99 사이의 랜덤 숫자 생성
    n = rand() % 99 + 1;  

    // 숫자 맞히기 게임 시작
    for (i = 0; i < maxAttempts; i++) {
        cout << "[" << i + 1 << "회] " << min << " ~ " << max << " 사이의 값 예측 => ";

        input = 0;
        char ch;
        
        // 숫자 입력받기 (한 자리씩 입력하면서 '*' 출력)
        while (true) {
            ch = getch();
            if (ch == '\r') break; // Enter 입력 시 종료

            if (ch >= '0' && ch <= '9') {
                cout << "*";
                input = input * 10 + (ch - '0'); // 숫자 변환
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