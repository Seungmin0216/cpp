#pragma once
#include "Monster.h"

// 기본 좀비 클래스
class Zombie : public Monster {
public:
	Zombie(string n = "좀비", string i = "🧟", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

// 뱀파이어 클래스: 상하좌우 이동
class Vampire : public Monster {
public:
	Vampire(string n = "뱀파이어", string i = "🧛", int x = 0, int y = 0)
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

// 한국 귀신: 무작위 위치 순간이동
class KGhost : public Monster {
public:
	KGhost(string n = "한국 귀신", string i = "👻", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(int** map, int maxx, int maxy) override {
		x = rand() % maxx;
		y = rand() % maxy;
		clip(maxx, maxy);
		eat(map);
	}
};

// 강시: 수평 또는 수직 점프 이동
class Jiangshi : public Monster {
protected:
	bool bHori; // 수평 이동이면 true
public:
	Jiangshi(string n = "강시", string i = "🧞", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	virtual void move(int** map, int maxx, int maxy) override {
		int dir = rand() % 2;
		int jump = rand() % 2 + 1;
		if (bHori)
			x += (dir == 0) ? -jump : jump;
		else
			y += (dir == 0) ? -jump : jump;

		clip(maxx, maxy);
		eat(map);
	}
};

// 1. 스몸비(Smombi): 대각선으로만 이동
class Smombi : public Monster {
public:
	Smombi(string n = "스몸비", string i = "📱", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Smombi() { cout << " Smombi"; }

	void move(int** map, int maxx, int maxy) override {
		int dir = rand() % 4;
		switch (dir) {
		case 0: x--; y--; break; // 좌상
		case 1: x++; y--; break; // 우상
		case 2: x--; y++; break; // 좌하
		case 3: x++; y++; break; // 우하
		}
		clip(maxx, maxy);
		eat(map);
	}
};

// 2. 샹시(Siangshi): 일정 주기로 방향 전환하는 슈퍼 강시
class Siangshi : public Jiangshi {
	int counter = 0;           // 이동 횟수 카운터
	int toggleInterval = 20;   // 방향 변경 주기
public:
	Siangshi(string n = "샹시", string i = "🧞‍♂️", int x = 0, int y = 0, bool bH = true)
		: Jiangshi(n, i, x, y, bH) {}
	~Siangshi() { cout << " Siangshi"; }

	void move(int** map, int maxx, int maxy) override {
		counter++;
		if (counter % toggleInterval == 0)
			bHori = !bHori; // 방향 전환
		Jiangshi::move(map, maxx, maxy);
	}
};

// 3. 사용자 정의 몬스터: 텔레포트 + 아이템 두 배 먹기
class GhostThief : public KGhost {
public:
	GhostThief(string n = "도둑 귀신", string i = "🦹", int x = 0, int y = 0)
		: KGhost(n, i, x, y) {}
	~GhostThief() { cout << " GhostThief"; }

	void move(int** map, int maxx, int maxy) override {
		x = rand() % maxx;
		y = rand() % maxy;
		if (map[y][x] == 1) {
			map[y][x] = 0;
			nItem += 2; // 두 개 먹은 효과
		}
	}
};
