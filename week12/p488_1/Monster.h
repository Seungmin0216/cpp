#pragma once
#include "Canvas.h"
#define DIM 40

class Monster {
protected:
	string name, icon;	// 몬스터 이름과 화면 출력용 아이콘
	int x, y, nItem;	// 현재 위치(x, y) 및 먹은 아이템 수

	// 화면 경계 벗어나지 않도록 위치 보정
	void clip(int maxx, int maxy) {
		if (x < 0) x = 0;
		if (x >= maxx) x = maxx - 1;
		if (y < 0) y = 0;
		if (y >= maxy) y = maxy - 1;
	}

	// 현재 위치에 아이템이 있다면 먹고 수를 증가시킴
	void eat(int** map) {
		if (map[y][x] == 1) {
			map[y][x] = 0;
			nItem++;
		}
	}

public:
	// 생성자: 이름, 아이콘, 시작 좌표 초기화
	Monster(string n = "몬스터", string i = "😈", int px = 0, int py = 0)
		: name(n), icon(i), x(px), y(py), nItem(0) {}

	// 소멸자: 종료 메시지 출력
	~Monster() {
		cout << "\t" << name << icon << " 퇴장합니다~~~\n";
	}

	// 몬스터를 캔버스에 그림
	void draw(Canvas &canvas) {
		canvas.draw(x, y, icon);
	}

	// 무작위 방향으로 이동 + 아이템 먹기
	virtual void move(int** map, int maxx, int maxy) {
		switch (rand() % 8) {
		case 0: y--; break;         // 위
		case 1: x++; y--; break;    // 오른쪽 위
		case 2: x++; break;         // 오른쪽
		case 3: x++; y++; break;    // 오른쪽 아래
		case 4: y++; break;         // 아래
		case 5: x--; y++; break;    // 왼쪽 아래
		case 6: x--; break;         // 왼쪽
		case 7: x--; y--; break;    // 왼쪽 위
		}
		clip(maxx, maxy);           // 경계 처리
		eat(map);                   // 아이템 먹기
	}

	// 상태 출력 (이름, 아이콘, 아이템 수)
	void print() {
		cout << "\t" << name << icon << " : " << nItem << endl;
	}
};
