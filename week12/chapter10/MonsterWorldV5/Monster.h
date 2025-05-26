#pragma once
#include "Canvas.h"
#define DIM 40

class Monster {
protected:
	string name, icon;   // 몬스터 이름과 화면 상의 아이콘
	int x, y, nItem;     // 현재 위치와 획득한 아이템 수

	// 화면 범위를 벗어나지 않도록 위치 제한
	void clip(int maxx, int maxy) {
		if (x < 0) x = 0;
		if (x >= maxx) x = maxx - 1;
		if (y < 0) y = 0;
		if (y >= maxy) y = maxy - 1;
	}

	// 해당 위치에 아이템이 있으면 먹고 카운트 증가
	void eat(int** map) {
		if (map[y][x] == 1) {
			map[y][x] = 0;
			nItem++;
		}
	}

public:
	// 기본 생성자: 이름은 "괴물", 아이콘은 "몬"
	Monster(string n = "괴물", string i = "몬", int px = 0, int py = 0)
		: name(n), icon(i), x(px), y(py), nItem(0) {}

	virtual ~Monster() {
		cout << "\t" << name << icon << " 사라집니다~~~\n";
	}

	// 캔버스에 몬스터 그리기
	void draw(Canvas& canvas) { canvas.draw(x, y, icon); }

	// 기본 이동 로직: 8방향 중 랜덤 이동
	virtual void move(int** map, int maxx, int maxy) {
		switch (rand() % 8) {
			case 0: y--; break;
			case 1: x++; y--; break;
			case 2: x++; break;
			case 3: x++; y++; break;
			case 4: y++; break;
			case 5: x--; y++; break;
			case 6: x--; break;
			case 7: x--; y--; break;
		}
		clip(maxx, maxy); // 화면 안으로 위치 제한
		eat(map);         // 아이템 먹기
	}

	// 몬스터 정보 출력
	void print() {
		cout << "\t" << name << icon << " : " << nItem << endl;
	}
};
