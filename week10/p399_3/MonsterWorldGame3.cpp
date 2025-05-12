#include "MonsterWorld.h"

int main() {
    srand(static_cast<unsigned int>(time(NULL)));  // 난수 생성기 초기화
    int w = 16, h = 8;  // 게임 맵의 크기

    MonsterWorld game(w, h);  // 게임 객체 생성

    // 몬스터들 추가 (이름, 아이콘, 초기 위치, 초기 에너지 등)
    game.add(new Monster("고블린", "👹", rand() % w, rand() % h, 10));
    game.add(new Monster("좀비", "💀", rand() % w, rand() % h, 5));
    game.add(new Monster("용", "🐉", rand() % w, rand() % h, 20));

    // 게임 시작 (최대 500번 이동, 100ms 대기)
    game.play(500, 100);

    return 0;  // 게임 종료
}