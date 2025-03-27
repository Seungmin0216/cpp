// 5x5 크기의 2차원 배열에 0과 1을 임의로 채우는 함수를 구현하라.
#include <iostream>
#include <cstdlib>  // rand() 함수 사용을 위해
#include <ctime>    // srand() 함수 사용을 위해

using namespace std;

// 0과 1을 임의로 채우는 함수
void randomFill(int map[5][5]) {
    // 랜덤 시드 초기화
    srand(static_cast<unsigned int>(time(0)));
    
    // 배열을 랜덤한 0 또는 1로 채우기
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            map[row][col] = rand() % 2;  // 0 또는 1을 무작위로 할당
        }
    }
}

// 보드 출력 함수
void printBoard(int map[5][5]) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            // 0과 1을 그대로 출력
            cout << map[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 5x5 크기의 체커 보드 배열
    int map[5][5];

    // randomFill 함수 호출하여 map 배열을 무작위로 0과 1로 채움
    randomFill(map);

    // 보드 출력
    printBoard(map);

    return 0;
}