#pragma once
#include "Canvas.h"  // Canvas 클래스 포함 (화면 출력용)
#include <iostream>
#include <string>
using namespace std;

#define DIM 40  // 맵 크기 정의 (40x40)

class Monster {
    string name, icon;   // 몬스터의 이름과 아이콘 (예: '고블린', '👹')
    int x, y, nItem;     // 몬스터의 x, y 좌표와 먹은 아이템 수
    int nEnergy;         // 몬스터의 에너지 (처음엔 100으로 설정)

    // 몬스터가 맵의 범위를 벗어나지 않도록 위치를 제한하는 함수
    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;  // x좌표가 0보다 작으면 0으로 설정
        if (x >= maxx) x = maxx - 1;  // x좌표가 맵의 너비보다 크면 최대값으로 설정
        if (y < 0) y = 0;  // y좌표가 0보다 작으면 0으로 설정
        if (y >= maxy) y = maxy - 1;  // y좌표가 맵의 높이보다 크면 최대값으로 설정
    }

    // 몬스터가 아이템을 먹을 때 호출되는 함수
    void eat(int map[DIM][DIM]) {
        if (map[y][x] == 1) {  // 만약 해당 위치에 아이템이 있다면 (아이템의 값이 1일 때)
            map[y][x] = 0;      // 아이템을 먹은 후, 그 위치를 비움 (아이템 값 0으로 설정)
            nItem++;             // 먹은 아이템 수 증가
            nEnergy += 8;        // 아이템을 먹으면 에너지가 8 증가
        } else {
            nEnergy -= 1;        // 아이템을 못 먹으면 에너지가 1 감소
            if (nEnergy < 0) nEnergy = 0; // 에너지는 0 이하로 내려가지 않도록 제한
        }
    }

public:
    // 생성자: 몬스터의 이름, 아이콘, 초기 위치와 에너지 설정
    Monster(string n = "고블린", string i = "👹", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { // 에너지 초기값을 100으로 설정
        // name: 몬스터의 이름 (기본값: "고블린")
        // icon: 몬스터의 아이콘 (기본값: "👹")
        // x, y: 몬스터의 초기 위치 (기본값: (0, 0))
        // nItem: 몬스터가 먹은 아이템 수 (기본값: 0)
        // nEnergy: 몬스터의 에너지 (기본값: 100)
    }

    // 소멸자: 몬스터가 죽을 때 이름과 아이콘을 출력
    ~Monster() {}

    // 복사 생성자: 다른 Monster 객체를 복사하여 새 객체를 생성
    Monster(const Monster& other) 
        : name(other.name), icon(other.icon), x(other.x), y(other.y), 
          nItem(other.nItem), nEnergy(other.nEnergy) {}  // 복사된 몬스터의 속성들을 그대로 복사

    // 몬스터를 화면에 그리는 함수
    void draw(Canvas &canvas) { 
        canvas.draw(x, y, icon);  // 몬스터의 아이콘을 주어진 (x, y) 좌표에 출력
    }

    // 몬스터가 이동하는 함수
    void move(int map[DIM][DIM], int maxx, int maxy) {
        switch (rand() % 8) {  // 8방향으로 랜덤 이동
        case 0: y--; break;    // 위로 이동
        case 1: x++; y--; break;  // 오른쪽 위로 이동
        case 2: x++; break;    // 오른쪽으로 이동
        case 3: x++; y++; break;  // 오른쪽 아래로 이동
        case 4: y++; break;    // 아래로 이동
        case 5: x--; y++; break;  // 왼쪽 아래로 이동
        case 6: x--; break;    // 왼쪽으로 이동
        case 7: x--; y--; break;  // 왼쪽 위로 이동
        }
        clip(maxx, maxy);  // 이동 후, 맵의 범위를 벗어나지 않도록 조정
        eat(map);           // 이동한 후 아이템을 먹었는지 확인하고, 에너지 갱신
    }

    // 몬스터의 상태 (이름, 아이콘, 먹은 아이템 수, 에너지 레벨) 출력
    void print() { 
        cout << "\t" << name << icon << ":" << nItem << " 아이템, 에너지: " << nEnergy << endl; 
        // 몬스터의 이름, 아이콘, 먹은 아이템 수, 에너지 출력
    }
}; 
