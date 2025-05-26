#pragma once
#include "Monster.h"
#include <conio.h>

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };

class Human : public Monster {
public:
	// 기본 생성자: 이름은 "이주인공", 아이콘은 "나", 초기 위치는 (0,0)
	Human(string n = "이주인공", string i = "나", int px = 0, int py = 0)
		: Monster(n, i, px, py) {}

	~Human() { cout << " [Human   ]"; }

	// 방향키 입력 처리 함수
	int getDirKey() { return getche() == 224 ? getche() : 0; }

	// 이동 처리 함수
	void move(int** map, int maxx, int maxy) {
		if (kbhit()) {
			char ch = getDirKey();
			if (ch == Left) x--;
			else if (ch == Right) x++;
			else if (ch == Up) y--;
			else if (ch == Down) y++;
			else return;
			clip(maxx, maxy); // 경계 처리
			eat(map);         // 먹이 먹기 처리
		}
	}
};