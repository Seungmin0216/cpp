#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include "Human.h"   // Human/Tuman 클래스 포함
#include <time.h>

int main() {
    srand((unsigned int)time(NULL));

    int w = 16, h = 8;
    MonsterWorld game(w, h);

    // 기존 몬스터들 추가
    game.add(new Zombie("좀비 대장", "🧟", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어", "🧛", rand() % w, rand() % h));
    game.add(new KGhost("한국 귀신", "👻", rand() % w, rand() % h));
    game.add(new Jiangshi("강시 형님", "🧞", rand() % w, rand() % h, true));
    game.add(new Jiangshi("강시 동생", "🧞", rand() % w, rand() % h, false));
    game.add(new Smombi("스몸비", "📱", rand() % w, rand() % h));
    game.add(new Siangshi("슈퍼 강시", "🧞‍♂️", rand() % w, rand() % h, true));
    game.add(new GhostThief("도둑 귀신", "🦹", rand() % w, rand() % h));

    // 플레이어 두 명 추가 (왼쪽, 오른쪽)
    game.add(new Tuman("왼쪽 사람", "좌", 0, h / 2));
    game.add(new Tuman("오른쪽 사람", "우", w - 1, h / 2));

    game.play(500, 10);

    printf("------ 게임 종료 -------------------\n");
    return 0;
}
