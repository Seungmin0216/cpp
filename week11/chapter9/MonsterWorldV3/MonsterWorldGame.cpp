#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <time.h>

// 메인 함수
int main() {
	srand((unsigned int)time(NULL));  // 난수 초기화 (현재 시간 기준)

	int w = 16, h = 8;                 // 맵 크기 설정
	MonsterWorld game(w, h);          // 게임 월드 생성

	// 몬스터 추가: 이름, 아이콘, 무작위 위치
	game.add(new Zombie("좀비 대장", "🧟", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어", "🧛", rand() % w, rand() % h));
	game.add(new KGhost("한국 귀신", "👻", rand() % w, rand() % h));
	game.add(new Jiangshi("강시 형님", "🧞", rand() % w, rand() % h, true));   // 빠른 강시
	game.add(new Jiangshi("강시 동생", "🧞", rand() % w, rand() % h, false));  // 느린 강시

	// 게임 실행 (최대 500번 이동, 각 이동 간 10ms 대기)
	game.play(500, 10);

	// 종료 메시지
	printf("------ 게임 종료 -------------------\n");

	return 0;
}
