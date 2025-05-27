#pragma once
#include "Monster.h"
#include <conio.h>

// 방향키 상수 재정의 (이미 정의되어 있다면 주석 처리 가능)
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };

class Human : public Monster {
public:
    Human(string n = "이주인공", string i = "나", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}

    ~Human() { cout << " [Human   ]"; }

    int getDirKey() { return getche() == 224 ? getche() : 0; }

    void move(int** map, int maxx, int maxy) {
        if (kbhit()) {
            char ch = getDirKey();
            if (ch == Left) x--;
            else if (ch == Right) x++;
            else if (ch == Up) y--;
            else if (ch == Down) y++;
            else return;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// 3. Tuman 클래스 추가: Human 상속, moveHuman() 함수 구현
class Tuman : public Human {
public:
    Tuman(string n = "사람", string i = "🙂", int x = 0, int y = 0)
        : Human(n, i, x, y) {}

    // 입력 문자에 따라 움직이는 함수 (kbhit 미사용)
    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        // 왼쪽 사람(w,a,s,d), 오른쪽 사람(화살표)
        switch (ch) {
            // 왼쪽 사람 (w,a,s,d)
            case 'w': y--; break;
            case 's': y++; break;
            case 'a': x--; break;
            case 'd': x++; break;

            // 오른쪽 사람 (방향키, 224 이후 값)
            case 72: y--; break; // 위 화살표
            case 80: y++; break; // 아래 화살표
            case 75: x--; break; // 왼쪽 화살표
            case 77: x++; break; // 오른쪽 화살표
            default: break;
        }
        clip(maxx, maxy);
        eat(map);
    }
};