#pragma once
#include <iostream>
#include <string>
using namespace std;

#define DIM 40  // 맵 크기 정의

class Monster {
    string name, icon;   // 몬스터의 이름과 아이콘
    int x, y, nItem;     // 몬스터의 x, y 좌표와 먹은 아이템 수

    // 몬스터가 맵의 범위를 벗어나지 않도록 위치를 제한하는 함수
    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

    // 몬스터가 아이템을 먹을 때 호출되는 함수
    void eat(int map[DIM][DIM]) {
        if (map[y][x] == 1) {  // 만약 해당 위치에 아이템이 있다면
            map[y][x] = 0;      // 아이템을 먹은 후, 그 위치를 비움
            nItem++;             // 아이템 개수 증가
        }
    }

public:
    // 생성자: 몬스터의 이름, 아이콘, 초기 위치를 설정
    Monster(string n = "고블린", string i = "👹", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}

    // 소멸자: 몬스터가 죽을 때 이름과 아이콘을 출력
    ~Monster() {}

    // 복사 생성자 (참조로 전달되는 Monster 객체를 복사)
    Monster(const Monster& other) 
        : name(other.name), icon(other.icon), x(other.x), y(other.y), nItem(other.nItem) {}

    // 몬스터를 화면에 그리는 함수
    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }

    // 몬스터가 이동하는 함수
    void move(int map[DIM][DIM], int maxx, int maxy) {
        switch (rand() % 8) {  // 8방향으로 랜덤 이동
        case 0: y--; break;    // 위
        case 1: x++; y--; break;  // 오른쪽 위
        case 2: x++; break;    // 오른쪽
        case 3: x++; y++; break;  // 오른쪽 아래
        case 4: y++; break;    // 아래
        case 5: x--; y++; break;  // 왼쪽 아래
        case 6: x--; break;    // 왼쪽
        case 7: x--; y--; break;  // 왼쪽 위
        }
        clip(maxx, maxy);  // 이동 후 범위 체크
        eat(map);           // 아이템 먹기
    }

    // 몬스터의 상태 (이름, 아이콘, 먹은 아이템 수) 출력
    void print() { cout << "\t" << name << icon << ":" << nItem << endl; }
};
