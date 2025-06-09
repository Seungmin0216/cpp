#pragma once
#include "Monster.h"
#include <conio.h>  // _kbhit(), _getche() 등을 사용하기 위한 헤더

// 방향키 코드 정의 (ASCII 확장 코드 기준)
enum Direction { 
    Left = 75, 
    Right = 77, 
    Up = 72, 
    Down = 80 
};

// Human 클래스: Monster 클래스를 상속받는 사용자 조작 가능한 몬스터
class Human : public Monster {
public:
    // 생성자: 기본값은 이름 "이름없음", 이미지 "사람 얼굴", 좌표 (0, 0)
    Human(string n = "이름없음", string i = "🙂", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}

    // 소멸자: 디버깅용 메시지 출력
    ~Human() { 
        cout << " [Human   ]"; 
    }

    // 방향키 입력을 처리 (두 번의 getche 호출로 방향키 해석)
    int getDirKey() { 
        return getche() == 224 ? getche() : 0; 
    }

    // 사람이 키보드 입력으로 움직이는 함수
    void move(int** map, int maxx, int maxy) {
        if (kbhit()) {  // 키가 눌렸는지 확인
            char ch = getDirKey();  // 방향키 입력 받기

            // 방향에 따라 좌표 이동
            if (ch == Left) p[0]--;
            else if (ch == Right) p[0]++;
            else if (ch == Up) p[1]--;
            else if (ch == Down) p[1]++;
            else return;  // 방향키가 아니면 리턴

            clip(maxx, maxy);  // 맵 경계 안으로 위치 조정
            eat(map);          // 해당 위치에서 먹이 먹기 시도
        }
    }
};
