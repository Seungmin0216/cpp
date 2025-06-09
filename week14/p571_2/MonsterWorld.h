#pragma once
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "Matrix.h"
#include <windows.h>
#define MAXMONS 8  // 최대 몬스터 수

// MonsterWorld 클래스: 몬스터와 인간이 활동하는 월드 관리
class MonsterWorld {
	Matrix world;             // 게임 맵 (아이템이 존재하는 위치를 저장)
	int xMax, yMax;           // 맵의 너비와 높이
	int nMon, nMove;          // 몬스터 수, 전체 이동 횟수
	Monster* pMon[MAXMONS];   // 몬스터 포인터 배열
	Canvas canvas;            // 화면 출력용 캔버스

	// 맵에서 특정 좌표의 아이템 값에 접근
	int& Map(int x, int y) { return world.elem(x, y); }

	// 모든 아이템을 먹었는지 확인
	bool isDone() { return countItems() == 0; }

	// 맵에 남아 있는 아이템 개수 계산
	int countItems() {
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}

	// 화면에 현재 상태 출력
	void print() {
		canvas.clear();
		
		// 아이템 표시 (아이콘: ●)
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "●");

		// 각 몬스터 출력
		for (int i = 0; i < nMon; i++)
			pMon[i]->draw(canvas);

		canvas.print("[ Monster World (아이템을 모두 수집하세요) ]");

		// 콘솔 정보 출력 (이동 횟수, 남은 아이템 수, 각 몬스터 상태)
		cerr << " 총 이동 횟수 = " << nMove << endl;
		cerr << " 남은 아이템 수 = " << countItems() << endl;
		for (int i = 0; i < nMon; i++)
			pMon[i]->print();
	}

public:
	// 생성자: 맵 사이즈 설정 및 아이템 초기화 (전부 1)
	MonsterWorld(int w, int h) 
		: world(h, w), canvas(w, h), xMax(w), yMax(h) {
		nMon = 0;
		nMove = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				Map(x, y) = 1;  // 모든 칸에 아이템 초기화
	}

	// 소멸자: 동적으로 할당된 몬스터 객체 삭제
	~MonsterWorld() { 
		for (int i = 0; i < nMon; i++)
			delete pMon[i];
	}

	// 몬스터 추가
	void add(Monster* m) {
		if (nMon < MAXMONS)
			pMon[nMon++] = m;
	}

	// 게임 실행: maxwalk 만큼 반복하며 각 몬스터 이동 → 출력 → 종료 조건 체크
	void play(int maxwalk, int wait) {
		print();
		cerr << " 아무 키나 누르면 시작합니다...";
		getchar();

		for (int i = 0; i < maxwalk; i++) {
			for (int k = 0; k < nMon; k++)
				pMon[k]->move(world.Data(), xMax, yMax);

			nMove++;      // 전체 이동 횟수 증가
			print();      // 화면 출력

			if (isDone()) break; // 아이템 다 먹으면 종료
			Sleep(wait);         // 일정 시간 대기
		}
	}
};
