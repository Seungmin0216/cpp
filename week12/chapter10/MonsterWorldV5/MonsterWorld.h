#pragma once
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "Matrix.h"
#include <windows.h>
#define MAXMONS 8

class MonsterWorld {
	Matrix world;
	int xMax, yMax, nMon, nMove;
	Monster* pMon[MAXMONS];
	Canvas canvas;

	int& Map(int x, int y) { return world.elem(x, y); }

	// 모든 아이템을 다 먹었는지 확인
	bool isDone() { return countItems() == 0; }

	// 남은 아이템 수 계산
	int countItems() {
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}

	// 화면 출력
	void print() {
		canvas.clear();
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "먹");

		for (int i = 0; i < nMon; i++)
			pMon[i]->draw(canvas);

		canvas.print("[ Monster World (몬스터와 인간의 전쟁) ]");

		cerr << " 전체 이동 횟수 = " << nMove << endl;
		cerr << " 남은 먹이 개수 = " << countItems() << endl;
		for (int i = 0; i < nMon; i++)
			pMon[i]->print();
	}

public:
	// 생성자: 월드 크기 설정 및 먹이 초기화
	MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h) {
		nMon = 0;
		nMove = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++) Map(x, y) = 1; // 먹이 초기화
	}

	// 소멸자: 동적으로 할당된 몬스터 해제
	~MonsterWorld() { 
		for (int i = 0; i < nMon; i++)
			delete pMon[i];
	}

	// 몬스터 추가
	void add(Monster* m) {
		if (nMon < MAXMONS)
			pMon[nMon++] = m;
	}

	// 메인 게임 루프
	void play(int maxwalk, int wait) {
		print();
		cerr << " 아무 키나 누르세요...";
		getchar();

		for (int i = 0; i < maxwalk; i++) {
			for (int k = 0; k < nMon; k++)
				pMon[k]->move(world.Data(), xMax, yMax);

			nMove++;
			print();

			if (isDone()) break;
			Sleep(wait);
		}
	}
};
