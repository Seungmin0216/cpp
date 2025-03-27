#include <iostream>
using namespace std;

int main() {
    // 5x5 체커 보드 출력
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            // 행과 열의 인덱스의 합이 짝수일 때 흰색, 홀수일 때 검은색
            if ((row + col) % 2 == 0) {
                cout << "W ";  // W는 흰색을 의미
            } else {
                cout << "B ";  // B는 검은색을 의미
            }
        }
        cout << endl;
    }
    return 0;
}