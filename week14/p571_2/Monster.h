#pragma once
#include "Canvas.h"
#include "Point.h"

// Monster 클래스: 게임의 기본 캐릭터 객체 (움직임, 아이템 수집, 피로 상태 포함)
class Monster {
public:
    string name, icon;  // 몬스터 이름과 화면에 출력될 아이콘
    int nItem;          // 수집한 아이템 개수

    Point q, p;         // q: 이전 위치, p: 현재 위치
    int nSleep;         // 잠자는 남은 턴 수 (피로 상태)
    double dist;        // 연속 움직임 거리
    double total;       // 총 이동 거리

    // 현재 위치가 맵 범위를 벗어나지 않도록 클리핑
    void clip(int maxx, int maxy) { 
        p(maxx, maxy);  // Point 클래스에 오버로딩된 연산자 ()가 있어야 함
    }

    // 아이템 먹기 동작 및 이동 거리 계산
    void eat(int** map) {
        if (map[p.y][p.x] == 1) {  // 해당 위치에 아이템(1)이 있다면
            map[p.y][p.x] = 0;     // 아이템 제거
            nItem++;               // 아이템 수 증가
        }
        dist += (double)(p - q);   // 직전 위치와의 거리 추가
        total += (double)(p - q);  // 누적 이동 거리 추가
        q = p;                     // 현재 위치를 이전 위치로 업데이트

        // 연속 이동 거리가 20을 넘으면 피로 상태로 전환
        if (dist > 20) {
            dist = 0;
            nSleep = 10;           // 10턴 동안 쉬게 됨
        }
    }

    // 잠자는 상태인지 확인
    bool isSleep() {
        if (nSleep > 0) {
            nSleep--;             // 잠에서 깨어나는 카운트 감소
            return true;          // 현재는 잠자는 상태
        }
        return false;             // 깨어 있음
    }

public:
    // 생성자: 이름, 아이콘, 초기 위치 설정
    Monster(string n = "이름없음몬스터", string i = "🐾", int x = 0, int y = 0)
        : name(n), icon(i), nItem(0),
          p(x, y), q(x, y), nSleep(0), dist(0.0), total(0.0) {}

    // 소멸자: 디버깅용 출력 (아이콘, 아이템 개수, 총 이동 거리)
    virtual ~Monster() {
        cout << icon << nItem << " 거리: " << total << endl;
    }

    // 캔버스에 몬스터 그리기
    void draw(Canvas &canvas) {
        canvas.draw(p, icon);
    }

    // 몬스터 자동 이동 (잠자는 상태 아니면 무작위 이동)
    virtual void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int num = rand() % 9 + 1; // 1~9 무작위 숫자
            p += Point(num % 3 - 1, num / 3 - 1); // 상하좌우 대각선 포함 8방향 이동
            clip(maxx, maxy);  // 경계 벗어나지 않게 조정
            eat(map);          // 아이템 먹기 시도
        }
    }

    // 몬스터 상태 출력
    void print() {
        cout << "\t" << name << " " << icon << " : 아이템 " << nItem << "개, 남은 휴식 " << nSleep << endl;
    }
};
