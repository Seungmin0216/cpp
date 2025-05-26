#pragma once
#include "Monster.h"

// 좀비 클래스: 기본 랜덤 이동
class Zombie : public Monster {
public:
	Zombie(string n = "좀비", string i = "좀", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

// 뱀파이어 클래스: 상하좌우 4방향 중 하나로 이동
class Vampire : public Monster {
public:
	Vampire(string n = "뱀파이어", string i = "뱀", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(int** map, int maxx, int maxy) override {
		int dir = rand() % 4;
		if (dir == 0) x--;
		else if (dir == 1) x++;
		else if (dir == 2) y--;
		else y++;
		clip(maxx, maxy);
		eat(map);
	}
};

// 도깨비 클래스: 순간이동형 몬스터
class KGhost : public Monster {
public:
	KGhost(string n = "도깨비", string i = "도", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(int** map, int maxx, int maxy) override {
		x = rand() % maxx;
		y = rand() % maxy;
		clip(maxx, maxy);
		eat(map);
	}
};

// 강시 클래스: 가로 또는 세로로 점프 이동
class Jiangshi : public Monster {
	bool bHori;  // true: 가로 방향, false: 세로 방향
public:
	Jiangshi(string n = "강시", string i = "시", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(int** map, int maxx, int maxy) override {
		int dir = rand() % 2;
		int jump = rand() % 2 + 1; // 1~2칸 점프
		if (bHori)
			x += ((dir == 0) ? -jump : jump);
		else
			y += ((dir == 0) ? -jump : jump);
		clip(maxx, maxy);
		eat(map);
	}
};
