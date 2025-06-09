#pragma once
#include "Monster.h"

class Zombie : public Monster {
public:
	// 좀비 몬스터 (느리게 움직임)
	Zombie(string n = "좀비", string i = "좀", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Vampire : public Monster {
public:
	// 뱀파이어 몬스터 (상하좌우 한 칸씩 이동)
	Vampire(string n = "뱀파이어", string i = "뱀", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(int** map, int maxx, int maxy) {
		if (!isSleep()) {
			int dir = rand() % 4;
			if (dir == 0) p[0]--;      // 왼쪽 이동
			else if (dir == 1) p[0]++; // 오른쪽 이동
			else if (dir == 2) p[1]--; // 위로 이동
			else p[1]++;               // 아래로 이동
			clip(maxx, maxy);
			eat(map);
		}
	}
};

class KGhost : public Monster {
public:
	// 유령 몬스터 (맵 내 임의 위치로 순간이동)
	KGhost(string n = "유령", string i = "유", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(int** map, int maxx, int maxy) {
		if (!isSleep()) {
			p = Point(rand() % maxx, rand() % maxy); // 임의 위치 이동
			clip(maxx, maxy);
			eat(map);
		}
	}
};

class Jiangshi : public Monster {
	bool bHori;  // 가로 이동 여부
public:
	// 강시 몬스터 (가로 또는 세로 방향으로 점프 이동)
	Jiangshi(string n = "강시", string i = "강", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(int** map, int maxx, int maxy) {
		if (!isSleep()) {
			int dir = rand() % 2;           // 이동 방향 결정 (0: 음수, 1: 양수)
			int jump = rand() % 2 + 1;      // 1칸 또는 2칸 점프
			if (bHori)
				p[0] += ((dir == 0) ? -jump : jump);  // 가로 점프 이동
			else
				p[1] += ((dir == 0) ? -jump : jump);  // 세로 점프 이동
			clip(maxx, maxy);
			eat(map);
		}
	}
};
