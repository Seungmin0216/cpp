// 가로나 세로 또는 대각선이 모두 0이거나 1인 부분을 찾아 화면으로 출력하는 함수를 구현하라.
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

// printMap 함수: 0과 1을 그대로 출력하는 함수
void printMap(int map[5][5]) {
    cout << "체커 보드 출력:" << endl;

    // 체커 보드를 0과 1로 출력
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            cout << map[row][col] << " ";  // 0과 1을 그대로 출력
        }
        cout << endl;  // 각 행을 출력한 후 줄 바꿈
    }
}

// checkMap 함수: 가로, 세로, 대각선이 모두 0 또는 1인 부분을 찾아 출력하는 함수
void checkMap(int map[5][5]) {
    // 가로 체크
    for (int row = 0; row < 5; row++) {
        bool allZero = true;
        bool allOne = true;
        for (int col = 0; col < 5; col++) {
            if (map[row][col] != 0) {
                allZero = false;
            }
            if (map[row][col] != 1) {
                allOne = false;
            }
        }
        if (allZero) {
            cout << "가로로 0이 모두 있는 행: " << row + 1 << endl;
        }
        if (allOne) {
            cout << "가로로 1이 모두 있는 행: " << row + 1 << endl;
        }
    }

    // 세로 체크
    for (int col = 0; col < 5; col++) {
        bool allZero = true;
        bool allOne = true;
        for (int row = 0; row < 5; row++) {
            if (map[row][col] != 0) {
                allZero = false;
            }
            if (map[row][col] != 1) {
                allOne = false;
            }
        }
        if (allZero) {
            cout << "세로로 0이 모두 있는 열: " << col + 1 << endl;
        }
        if (allOne) {
            cout << "세로로 1이 모두 있는 열: " << col + 1 << endl;
        }
    }

    // 대각선 체크 (왼쪽 상단에서 오른쪽 하단)
    bool diagonalLeftToRightAllZero = true;
    bool diagonalLeftToRightAllOne = true;
    for (int i = 0; i < 5; i++) {
        if (map[i][i] != 0) {
            diagonalLeftToRightAllZero = false;
        }
        if (map[i][i] != 1) {
            diagonalLeftToRightAllOne = false;
        }
    }
    if (diagonalLeftToRightAllZero) {
        cout << "대각선(왼쪽 상단 -> 오른쪽 하단)으로 0이 모두 있습니다." << endl;
    }
    if (diagonalLeftToRightAllOne) {
        cout << "대각선(왼쪽 상단 -> 오른쪽 하단)으로 1이 모두 있습니다." << endl;
    }

    // 대각선 체크 (오른쪽 상단에서 왼쪽 하단)
    bool diagonalRightToLeftAllZero = true;
    bool diagonalRightToLeftAllOne = true;
    for (int i = 0; i < 5; i++) {
        if (map[i][4 - i] != 0) {
            diagonalRightToLeftAllZero = false;
        }
        if (map[i][4 - i] != 1) {
            diagonalRightToLeftAllOne = false;
        }
    }
    if (diagonalRightToLeftAllZero) {
        cout << "대각선(오른쪽 상단 -> 왼쪽 하단)으로 0이 모두 있습니다." << endl;
    }
    if (diagonalRightToLeftAllOne) {
        cout << "대각선(오른쪽 상단 -> 왼쪽 하단)으로 1이 모두 있습니다." << endl;
    }
}

int main() {
    // 5x5 크기의 체커 보드 배열
    int map[5][5];

    // randomFill 함수 호출하여 map 배열을 무작위로 0과 1로 채움
    randomFill(map);

    // printMap 함수 호출하여 배열 출력
    printMap(map);

    // checkMap 함수 호출하여 배열 검사
    checkMap(map);

    return 0;
}