#include <iostream>
#include <chrono>         // chrono를 포함하여 시간을 다룰 수 있게 함
#include <thread>         // this_thread를 포함하여 스레드를 제어할 수 있게 함
#include "MonsterWorld.h"  // 몬스터 월드 클래스 포함
#include <ctime>             // 시간 관련 함수 포함 (난수 시드 설정용)

int main() {
    srand(static_cast<unsigned int>(time(NULL))); // 현재 시간을 기준으로 난수 시드 설정

    int w = 16, h = 8;  // 게임 맵의 너비와 높이 설정

    MonsterWorld game(w, h); // 너비와 높이로 게임 월드 생성

    // 몬스터 객체를 생성하여 게임에 추가 (이름, 심볼, x위치, y위치)
    Monster m("고블린", "👹", rand() % w, rand() % h); // 고블린
    game.add(m);

    game.add(Monster("트롤", "👺", rand() % w, rand() % h));      // 트롤
    game.add(Monster("슬라임", "🟢", rand() % w, rand() % h));    // 슬라임
    game.add(Monster("스켈레톤", "💀", rand() % w, rand() % h)); // 스켈레톤

    game.play(500, 10); // 500ms 간격으로 10번 턴 실행

    std::cout << "------몬스터 전투 종료-------------------\n"; // 게임 종료 메시지 출력
    return 0;  // main 함수에서 반환값을 0으로 수정
}
