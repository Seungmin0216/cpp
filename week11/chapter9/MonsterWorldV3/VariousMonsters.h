#pragma once
#include "Monster.h"

// 좀비: 기본 몬스터, 랜덤 이동은 부모 클래스 Monster의 move() 그대로 사용
class Zombie : public Monster {
public:
	Zombie(string n = "좀비", string i = "🧟", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

// 뱀파이어: 상하좌우 방향으로만 이동
class Vampire : public Monster {
public:
	Vampire(string n = "뱀파이어", string i = "🧛", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(int** map, int maxx, int maxy) override {
		int dir = rand() % 4;
		if (dir == 0) x--;        // 왼쪽
		else if (dir == 1) x++;   // 오른쪽
		else if (dir == 2) y--;   // 위쪽
		else y++;                 // 아래쪽

		clip(maxx, maxy); // 경계 체크
		eat(map);         // 아이템 먹기
	}
};

// 한국 귀신: 텔레포트 이동 (맵 내 아무 위치로 순간이동)
class KGhost : public Monster {
public:
	KGhost(string n = "한국 귀신", string i = "👻", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(int** map, int maxx, int maxy) override {
		x = rand() % maxx; // 무작위 위치로 순간이동
		y = rand() % maxy;
		clip(maxx, maxy);
		eat(map);
	}
};

// 강시: 수평 or 수직 방향으로 점프 이동 (1~2칸)
class Jiangshi : public Monster {
	bool bHori; // true면 수평 이동, false면 수직 이동
public:
	Jiangshi(string n = "강시", string i = "🧞", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(int** map, int maxx, int maxy) override {
		int dir = rand() % 2;
		int jump = rand() % 2 + 1; // 1 또는 2칸 점프

		if (bHori)       // 수평 점프
			x += (dir == 0) ? -jump : jump;
		else             // 수직 점프
			y += (dir == 0) ? -jump : jump;

		clip(maxx, maxy);
		eat(map);
	}
};
