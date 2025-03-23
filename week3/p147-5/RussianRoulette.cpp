#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

// 함수 선언
int playRussianRoulette(int nTurns, int nBullets);

// 러시안 룰렛 게임 실행 함수 정의
int playRussianRoulette(int nTurns, int nBullets) {
    // 총알을 담을 벡터. 각 총알의 위치를 기록
    std::vector<bool> chamber(6, false);  // 6개의 탄창
    std::queue<int> participants;  // 참가자들 (원형으로 진행)
    
    // 참가자들을 큐에 추가
    for (int i = 0; i < nTurns; ++i) {
        participants.push(i + 1);  // 참가자 번호 (1번, 2번, ...)
    }

    // 총알을 nBullets만큼 랜덤하게 배치
    for (int i = 0; i < nBullets; ++i) {
        int pos = rand() % 6;  // 6개의 탄창 중 무작위로 위치를 설정
        chamber[pos] = true;  // 총알이 위치한 곳을 true로 설정
    }

    std::cout << "\n게임을 시작합니다!\n";

    // 게임 진행: 모든 총알이 발사될 때까지
    int shotsFired = 0;
    while (shotsFired < nBullets) {
        // 현재 참가자가 격발
        int currentPlayer = participants.front();
        participants.pop();  // 참가자가 격발 후 다음 참가자에게로 이동

        // 랜덤한 탄창 위치 선택
        int pos = rand() % 6;
        std::cout << "[" << currentPlayer << "번] 탄창을 돌렸습니다. 위치: " << pos + 1 << "\n";
        std::cout << "\t엔터를 누르면 격발됩니다...";
        std::cin.get();  // 엔터 입력 기다림

        if (chamber[pos]) {
            // 총알이 발사되면 게임 종료
            std::cout << "\t빵~~~~~~~~~!!! " << currentPlayer << "번 참가자가 총에 맞았습니다.\n";
            shotsFired++;
        } else {
            std::cout << "\t휴~~~ 살았습니다!!!\n";
        }

        // 참가자가 살아남으면 다시 뒤로 보내기
        if (shotsFired < nBullets) {
            participants.push(currentPlayer);  // 죽지 않았다면 다시 차례가 오도록 큐 뒤에 추가
        }
    }

    // 게임 종료 후 총알에 맞은 참가자 출력
    std::cout << "\n-----> 게임 종료! 총알을 맞은 참가자는 총 " << nBullets << "명입니다.\n";
    return 0;
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

    // 게임 실행
    playRussianRoulette(nTurn, nBullets);  
    return 0;
}