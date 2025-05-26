#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <time.h>

int main() {
	srand((unsigned int)time(NULL));  // 난수 초기화

	int w = 16, h = 8;
	MonsterWorld game(w, h);

	// 기존 몬스터들
	game.add(new Zombie("좀비 대장", "🧟", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어", "🧛", rand() % w, rand() % h));
	game.add(new KGhost("한국 귀신", "👻", rand() % w, rand() % h));
	game.add(new Jiangshi("강시 형님", "🧞", rand() % w, rand() % h, true));
	game.add(new Jiangshi("강시 동생", "🧞", rand() % w, rand() % h, false));

	// 새로운 몬스터들
	game.add(new Smombi("스몸비", "📱", rand() % w, rand() % h));                      // 대각선 이동
	game.add(new Siangshi("슈퍼 강시", "🧞‍♂️", rand() % w, rand() % h, true));       // 방향 바꾸는 강시
	game.add(new GhostThief("도둑 귀신", "🦹", rand() % w, rand() % h));              // 텔레포트 + 2개 아이템

	game.play(500, 10);  // 게임 실행

	printf("------ 게임 종료 -------------------\n");
	return 0;
}
