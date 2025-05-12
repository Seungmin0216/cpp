#pragma once
#include "Canvas.h"  // Canvas 클래스 포함 (화면 출력용)
#include "Monster.h" // Monster 클래스 포함
#include <chrono>         // chrono를 포함하여 시간을 다룰 수 있게 함
#include <thread>         // this_thread를 포함하여 스레드를 제어할 수 있게 함
#define DIM  40       // 맵의 크기 (40x40)
#define MAXMONS 5     // 최대 몬스터 수 (5마리까지)

class MonsterWorld {
    int map[DIM][DIM];    // 게임 맵
    int xMax, yMax;       // 맵의 크기 (너비, 높이)
    int nMon, nMove;      // 몬스터 수, 이동 횟수
    Monster* mon[MAXMONS]; // 몬스터 포인터 배열 (동적 할당)
    Canvas canvas;        // 화면에 그릴 Canvas 객체

    // 맵의 특정 위치에 접근하는 함수 (x, y 좌표)
    int& Map(int x, int y) { return map[y][x]; }

    // 게임 종료 여부 확인 (맵에 아이템이 남아있는지 확인)
    bool isDone() { return countItems() == 0; }

    // 맵에 남아 있는 아이템의 개수를 세는 함수
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

    // 화면에 게임 상태를 출력하는 함수
    void print() {
        canvas.clear();  // 화면을 비움
        // 맵에 있는 아이템을 그리기
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "◆"); // 아이템 표시 (◆ 기호 사용)

        // 몬스터들을 그리기
        for (int i = 0; i < nMon; i++)
            mon[i]->draw(canvas);  // 각 몬스터의 위치를 화면에 출력

        canvas.print("[ Monster World (몬스터 월드 전투) ]"); // 게임 제목 출력

        cout << " 총 이동 횟수 = " << nMove << endl; // 이동 횟수 출력
        cout << " 남은 아이템 개수 = " << countItems() << endl; // 남은 아이템 개수 출력
        // 각 몬스터의 상태 출력
        for (int i = 0; i < nMon; i++)
            mon[i]->print(); 
    }

    // 굶어 죽은 몬스터 확인 및 처리
    void checkStarvation() {
        for (int i = 0; i < nMon; i++) {
            if (mon[i]->getEnergy() <= 0) { // 에너지가 0인 몬스터가 있으면
                cout << "⚠️ " << mon[i]->getIcon() << " 몬스터가 굶어 죽었습니다." << endl;
                delete mon[i];  // 해당 몬스터를 동적으로 해제
                for (int j = i; j < nMon - 1; j++) {
                    mon[j] = mon[j + 1]; // 몬스터 배열에서 해당 몬스터를 삭제
                }
                nMon--;  // 몬스터 수 감소
                i--;  // 인덱스를 하나 감소시켜서 뒤의 몬스터를 검사하도록 함
            }
        }
    }

public:
    // 생성자: 게임 맵 크기와 초기화
    MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;  // 초기 몬스터 수
        nMove = 0; // 초기 이동 횟수
        // 맵을 모두 1로 초기화 (아이템이 존재하는 곳으로 표시)
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }

    ~MonsterWorld() { 
        for (int i = 0; i < nMon; i++) {
            delete mon[i];  // 몬스터 객체 동적 해제
        }
    }

    // 몬스터를 게임에 추가하는 함수
    void add(Monster* m) {
        if (nMon < MAXMONS) mon[nMon++] = m;  // 몬스터 배열에 추가
    }

    // 게임을 실행하는 함수 (maxwalk: 최대 이동 횟수, wait: 이동 간 대기 시간)
    void play(int maxwalk, int wait) {
        print();  // 게임 상태 출력
        cout << " 전투 시작 중...";  // `cerr` -> `cout` 변경
        getchar();  // 사용자가 엔터 키를 누를 때까지 대기

        for (int i = 0; i < maxwalk; i++) {
            // 각 몬스터가 이동하는 부분
            for (int k = 0; k < nMon; k++) {
                mon[k]->move(map, xMax, yMax); // 몬스터 이동
                mon[k]->reduceEnergy(); // 이동 후 에너지 차감
            }
            nMove++;  // 이동 횟수 증가
            print();   // 게임 상태 출력

            checkStarvation();  // 에너지 0인 몬스터 확인

            if (isDone()) break;  // 아이템이 모두 사라졌으면 게임 종료
            
            // 대기 시간 적용
            this_thread::sleep_for(chrono::milliseconds(wait));
        }
    }
};