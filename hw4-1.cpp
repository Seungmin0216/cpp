#include <iostream>
#include <conio.h>  // getch() 사용을 위해 필요
using namespace std;

int main() {
    int n, min = 1, max = 99, input, i;
    char a, b;

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
    for (i = 0; i < 10; i++) {
        cout << "[" << i + 1 << "회] " << min << " ~ " << max << " 사이의 값 예측 => ";

        input = 0;  // 입력값 초기화

        // 숫자 입력받기 (한 자리씩 입력하면서 '*' 출력)
        char ch;
        while (true) {
            ch = getch();
            if (ch == '\r') break; // Enter 키 입력 시 종료
            
            if (ch >= '0' && ch <= '9') { // 숫자만 허용
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

    cout << "  " << ((n == input) ? "성공" : "실패") << " !!!  정답은 " << n << endl;
    cout << "  최종 점수 = " << 10 * (10 - i) << endl;

    return 0;
}