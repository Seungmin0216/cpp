#pragma once
#define NOMINMAX        // optional but useful to avoid min/max macro pollution
#undef byte             // ⚠️ 반드시 windows.h 포함 전에 정의 제거
#include <windows.h>    // Windows API
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Matrix.h"

#define MAXMONS 8        // 최대 몬스터 수

class MonsterWorld {
	Matrix world;			 // 아이템이 배치된 맵을 나타내는 행렬
	int xMax, yMax;		 // 맵의 가로/세로 크기
	int nMon, nMove;		 // 현재 몬스터 수, 이동 횟수
	Monster* pMon[MAXMONS]; // 몬스터 객체 배열
	Canvas canvas;			 // 화면 출력용 캔버스

	// 맵에서 특정 좌표에 접근하기 위한 참조
	int& Map(int x, int y) { return world.elem(x, y); }

	// 아이템이 모두 사라졌는지 여부 확인
	bool isDone() { return countItems() == 0; }

	// 맵에 남아있는 아이템 개수 세기
	int countItems() {
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}

	// 현재 맵과 몬스터 상태를 출력
	void print() {
		canvas.clear();  // 캔버스를 초기화 (배경 설정)
		
		// 맵에 남은 아이템(1)을 "🍭"으로 출력
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "🍭");

		// 모든 몬스터 출력
		for (int i = 0; i < nMon; i++)
			pMon[i]->draw(canvas);

		canvas.print("[ Monster World (몬스터 먹기 대결) ]");

		// 상태 정보 출력
		cerr << " 전체 이동 횟수 = " << nMove << endl;
		cerr << " 남은 아이템 수 = " << countItems() << endl;
		for (int i = 0; i < nMon; i++)
			pMon[i]->print();
	}

public:
	// 생성자: 맵 생성 및 아이템 초기화
	MonsterWorld(int w, int h) 
		: world(h, w), canvas(w, h), xMax(w), yMax(h) {
		nMon = 0;
		nMove = 0;

		// 전체 맵에 아이템(1) 배치
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				Map(x, y) = 1;
	}

	// 소멸자: 동적 생성된 몬스터 객체 해제
	~MonsterWorld() { 
		for (int i = 0; i < nMon; i++)
			delete pMon[i];
	}

	// 몬스터 추가
	void add(Monster* m) {
		if (nMon < MAXMONS)
			pMon[nMon++] = m;
	}

	// 메인 루프: 몬스터가 이동하며 아이템을 먹는 게임 실행
	void play(int maxwalk, int wait) {
		print();
		cerr << " 아무 키나 누르면 시작합니다...";
		getchar();

		for (int i = 0; i < maxwalk; i++) {
			// 몬스터별 이동 (명시적 캐스팅 사용)
			((Zombie*)pMon[0])->move(world.Data(), xMax, yMax);
			((Vampire*)pMon[1])->move(world.Data(), xMax, yMax);
			((KGhost*)pMon[2])->move(world.Data(), xMax, yMax);
			((Jiangshi*)pMon[3])->move(world.Data(), xMax, yMax);
			((Jiangshi*)pMon[4])->move(world.Data(), xMax, yMax);

			nMove++;
			print();

			if (isDone()) break; // 아이템이 모두 사라지면 종료
			Sleep(wait);         // 일정 시간 대기
		}
	}
};