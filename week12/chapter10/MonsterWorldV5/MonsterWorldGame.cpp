#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;
	MonsterWorld game(w, h);

	// 몬스터 추가 (이름, 아이콘, 랜덤 위치)
	game.add(new Zombie("좀비 아저씨", "좀", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어", "뱀", rand() % w, rand() % h));
	game.add(new KGhost("도깨비", "도", rand() % w, rand() % h));
	game.add(new Jiangshi("강시(점프형)", "강", rand() % w, rand() % h, true));
	game.add(new Jiangshi("강시(걷는형)", "시", rand() % w, rand() % h, false));
	game.add(new Human("이로운 인간", "인", rand() % w, rand() % h));

	// 게임 실행 (최대 500턴, 이동 간격 10ms)
	game.play(500, 10);

	printf("------게임 종료-------------------\n");
	getchar(); // 일시정지용 입력
	getchar();
	return 0;
}
