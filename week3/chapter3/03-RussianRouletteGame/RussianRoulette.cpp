#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RussianRoulette.h"

int playRussianRoulette(int nTurns, int nBullets) {
    int start = rand() % nTurns;
    std::cout << "\n총을 돌렸습니다. " << start + 1 << "번부터 시작합니다.\n";

    while (true) {
        int pos = rand() % 6;
        std::cout << "[" << start + 1 << "번] 탄창을 무작위로 돌렸습니다.\n";
        std::cout << "\t엔터를 누르면 격발됩니다...";
        std::cin.get();  // 엔터를 받기 위해

        if (pos < nBullets) {
            break;
        }
        std::cout << "\t휴~~~ 살았습니다!!!\n";
        start = (start + 1) % nTurns;
    }

    std::cout << "\t빵~~~~~~~~~!!!\n";
    return start + 1;
}

int main() {
    int nTurn, nBullets;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // 난수 시드 초기화

    std::cout << "게임 인원 (예: 2) ==> ";
    std::cin >> nTurn;
    std::cout << "총알 개수 (6미만) ==> ";
    std::cin >> nBullets;
    std::cin.ignore();  // 잉여 개행 문자 처리

    nTurn = (nTurn == 0) ? 2 : nTurn;  // 기본값 2
    nBullets = (nBullets == 0) ? 1 : nBullets;  // 기본값 1

    if (nBullets >= 6 || nBullets <= 0) {
        std::cout << "총알 개수는 1 이상 6 미만이어야 합니다.\n";
        return 1;
    }

    int bang = playRussianRoulette(nTurn, nBullets);  // 게임 실행
    std::cout << "\n -----> " << bang << "번 참가자가 총에 맞았습니다.\n";

    return 0;
}