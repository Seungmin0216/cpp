#pragma once
#define NOMINMAX        // optional but useful to avoid min/max macro pollution
#undef byte             // 반드시 windows.h 포함 전에 제거

#include <windows.h>    // Windows API
#include <conio.h>      // kbhit(), getche() 위해 반드시 포함
#include <iostream>     // cerr, endl
#include "Human.h"
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Matrix.h"

#define MAXMONS 8        // 최대 몬스터 수

class MonsterWorld {
    Matrix world;             // 아이템이 배치된 맵을 나타내는 행렬
    int xMax, yMax;           // 맵의 가로/세로 크기
    int nMon, nMove;          // 현재 몬스터 수, 이동 횟수
    Monster* pMon[MAXMONS];   // 몬스터 객체 배열
    Canvas canvas;            // 화면 출력용 캔버스

    int& Map(int x, int y) { return world.elem(x, y); }

    bool isDone() { return countItems() == 0; }

    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

    void print() {
        canvas.clear();

        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "🍭");

        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);

        canvas.print("[ Monster World (몬스터 먹기 대결) ]");

        std::cerr << " 전체 이동 횟수 = " << nMove << std::endl;
        std::cerr << " 남은 아이템 수 = " << countItems() << std::endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
    }

public:
    MonsterWorld(int w, int h);
    ~MonsterWorld();

    void add(Monster* m);
    void play(int maxwalk, int wait);  // 선언만
};
MonsterWorld::MonsterWorld(int w, int h)
    : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
    for (int y = 0; y < yMax; y++)
        for (int x = 0; x < xMax; x++)
            Map(x, y) = 1;
}

MonsterWorld::~MonsterWorld() {
    for (int i = 0; i < nMon; i++)
        delete pMon[i];
}

void MonsterWorld::add(Monster* m) {
    if (nMon < MAXMONS)
        pMon[nMon++] = m;
}

void MonsterWorld::play(int maxwalk, int wait) {
    print();
    std::cerr << " 아무 키나 누르면 시작합니다...";
    getchar();

    for (int i = 0; i < maxwalk; i++) {
        // 일반 몬스터들은 world.Data() 배열과 맵 크기를 넘겨서 움직임
        for (int k = 0; k < nMon - 2; k++) {
            pMon[k]->move(world.Data(), xMax, yMax);
        }

        if (kbhit()) {
            unsigned char ch = getche();
            if (ch == 224) { // 화살표 키 처리
                ch = getche();
                // 마지막 몬스터가 오른쪽 플레이어 (Tuman 객체)
                ((Tuman*)(pMon[nMon - 1]))->moveHuman(world.Data(), xMax, yMax, ch);
            }
            else {
                // 그 다음 몬스터가 왼쪽 플레이어 (Tuman 객체)
                ((Tuman*)(pMon[nMon - 2]))->moveHuman(world.Data(), xMax, yMax, ch);
            }
        }

        nMove++;
        print();

        if (isDone()) break;
        Sleep(wait);
    }
}
