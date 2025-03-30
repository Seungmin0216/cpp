#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "puzzlegame4.h"  // 헤더 파일 포함

// 게임 관련 전역 변수들
int map[DIM][DIM];  
int x, y;           
int nMove;          
clock_t tStart;      // 시작 시간

PlayInfo MVP[NUM_MVP];  
int nMVP = NUM_MVP;

// 방향키를 나타내는 배열 (DirKey 배열)
static int DirKey[4] = { Left, Right, Up, Down };

void initRanking() {
    PlayInfo noname = { "C++게임", 1000, 1000.0 };
    for (int i = 0; i < nMVP; i++) {
        MVP[i] = noname;  
    }
}

void init() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;
    map[DIM - 1][DIM - 1] = 0;
    x = DIM - 1; y = DIM - 1;
    srand(time(NULL));  
    tStart = clock();   
    nMove = 0;          
}

void display() {
    system("cls");
    printf("\tFifteen Puzzle\n\t");
    printf("--------------\n\t");
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] > 0)
                printf("%3d", map[r][c]);
            else printf("   ");
        }
        printf("\n\t");
    }
    printf("--------------\n\t");
    clock_t t1 = clock();
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
    printf("\n\t이동 횟수:%6d\n\t경과 시간:%6.1f\n\n", nMove, d);
}

bool move(int dir) {
    if (dir == Right && x > 0) {
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    }
    else if (dir == Left && x < DIM - 1) {
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    }
    else if (dir == Up && y < DIM - 1) {
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    }
    else if (dir == Down && y > 0) {
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    }
    else return false;

    nMove++;
    return true;
}

void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        int key = DirKey[rand() % 4];
        if (move(key) == false) { i--; continue; }
        display();
        Sleep(50);
    }
}

bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}

// _getch()로 방향키를 입력받는 방식
int getDirKey() {
    return _getch();  // _getch()를 사용하여 방향키 입력 처리
}

int playFifteenPuzzle() {
    init();
    display();
    printRanking();
    printf("\n게임을 시작합니다(입력)...\n");
    getchar();
    shuffle(100);
    printf("\n게임을 시작합니다...\n");
    getchar();

    nMove = 0;
    tStart = clock();  
    while (!isDone()) {
        move(getDirKey());
        display();
    }

    clock_t t1 = clock();
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
    return addRanking(nMove, d);
}

void loadRanking(const char* fname) {
    FILE* fp = fopen(fname, "r");
    if (fp == NULL)
        initRanking();
    else {
        for (int i = 0; i < nMVP; i++)
            fscanf(fp, "%d%s%lf", &MVP[i].nMove, MVP[i].name, &MVP[i].tElapsed);
        fclose(fp);
    }
}

void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (fp == NULL) return;
    for (int i = 0; i < nMVP; i++)
        fprintf(fp, "  %4d  %-16s %-5.1f\n", MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
    fclose(fp);
}

void printRanking() {
    for (int i = 0; i < nMVP; i++)
        printf("  [%2d위]  %4d  %-16s %5.1f\n", i + 1, MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
}

int addRanking(int nMove, double tElap) {
    int index;
    for (index = 0; index < nMVP; index++) {
        if (nMove < MVP[index].nMove) break;
        if (nMove == MVP[index].nMove && tElap < MVP[index].tElapsed) break;
    }
    if (index == nMVP) return 0;
    for (int i = nMVP - 1; i > index; i--) MVP[i] = MVP[i - 1];
    MVP[index].nMove = nMove;
    MVP[index].tElapsed = tElap;
    printf("순위에 올랐습니다! 이름을 입력해주세요: ");
    getchar();
    fgets(MVP[index].name, sizeof(MVP[index].name), stdin);
    MVP[index].name[strlen(MVP[index].name) - 1] = '\0'; 
    return 1;
}

void saveGame(const char* filename) {
    std::ofstream out(filename, std::ios::binary);
    out.write(reinterpret_cast<char*>(map), sizeof(map));
    out.write(reinterpret_cast<char*>(&x), sizeof(x));
    out.write(reinterpret_cast<char*>(&y), sizeof(y));
    out.write(reinterpret_cast<char*>(&nMove), sizeof(nMove));
    out.write(reinterpret_cast<char*>(&tStart), sizeof(tStart));
    out.close();
}

void loadGame(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    in.read(reinterpret_cast<char*>(map), sizeof(map));
    in.read(reinterpret_cast<char*>(&x), sizeof(x));
    in.read(reinterpret_cast<char*>(&y), sizeof(y));
    in.read(reinterpret_cast<char*>(&nMove), sizeof(nMove));
    in.read(reinterpret_cast<char*>(&tStart), sizeof(tStart));
    in.close();
}

// 메인 함수 추가
int main() {
    // 시스템 명령어로 chcp 65001을 실행하여 터미널의 인코딩을 UTF-8로 설정
    system("chcp 65001");
    loadRanking("ranking.dat");
    int result = playFifteenPuzzle();
    if (result) {
        storeRanking("ranking.dat");
        printf("\n게임 종료! 순위에 올랐습니다.\n");
    } else {
        printf("\n게임 종료! 순위에 들지 않았습니다.\n");
    }
    return 0;
}