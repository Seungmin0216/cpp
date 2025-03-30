#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>    // Sleep() 관련 헤더
#include <time.h>
#include "PuzzleGame.h"  // 헤더 파일 추가

#define DIM 4           // 4x4 퍼즐 게임

// 게임 관련 전역 변수들
// enum Direction은 이미 헤더에서 정의됨
static int DirKey[4] = { Left, Right, Up, Down };
static int map[DIM][DIM];  // 게임 맵
static int x, y;           // 빈 칸의 위치 (y, x)
static int nMove;          // 이동 횟수
static clock_t tStart;     // 시작 시간

// 랭킹 관련 구조체 및 변수
#define NUM_MVP 5
struct PlayInfo {
    char name[200];   // 플레이어 이름
    int nMove;        // 이동 횟수
    double tElapsed;  // 경과 시간
};
static PlayInfo MVP[NUM_MVP];  // MVP 배열

static int nMVP = NUM_MVP;  // MVP 배열 크기

// 랭킹 초기화 함수
void initRanking() {
    PlayInfo noname = { "C++게임", 1000, 1000.0 };
    for (int i = 0; i < nMVP; i++) {
        MVP[i] = noname;  // 기본값으로 초기화
    }
}

// 게임 초기화 함수
void init() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;
    map[DIM - 1][DIM - 1] = 0;
    x = DIM - 1; y = DIM - 1;
    srand(time(NULL));  // 난수 초기화
    tStart = clock();   // 시작 시간
    nMove = 0;          // 이동 횟수 초기화
}

// 게임 화면 출력 함수
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

// 퍼즐 이동 함수
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

// 퍼즐 섞기 함수
void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        int key = DirKey[rand() % 4];
        if (move(key) == false) { i--; continue; }
        display();
        Sleep(50);
    }
}

// 퍼즐 완료 여부 확인 함수
bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}

// 방향키 입력 받는 함수
int getDirKey() { return getchar(); }  // 수정된 부분

// 게임 실행 함수
int playFifteenPuzzle() {
    init();
    display();
    printRanking();  // 랭킹 출력
    printf("\n게임을 시작합니다(입력)...\n");
    getchar();
    shuffle(100);  // 퍼즐 섞기
    printf("\n게임을 시작합니다...\n");
    getchar();

    nMove = 0;
    tStart = clock();  // 게임 시작 시간 기록
    while (!isDone()) {
        move(getDirKey());  // 사용자 입력으로 이동
        display();           // 게임 화면 갱신
    }

    clock_t t1 = clock();
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
    return addRanking(nMove, d);  // 랭킹에 추가
}

// 랭킹 로드 함수
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

// 랭킹 저장 함수
void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (fp == NULL) return;
    for (int i = 0; i < nMVP; i++)
        fprintf(fp, "  %4d  %-16s %-5.1f\n", MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
    fclose(fp);
}

// 랭킹 출력 함수
void printRanking() {
    for (int i = 0; i < nMVP; i++)
        printf("  [%2d위]  %4d  %-16s %5.1f\n", i + 1, MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
}

// 랭킹에 추가 함수
int addRanking(int nMove, double tElap) {
    if (nMove < MVP[nMVP - 1].nMove) {
        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nMove >= MVP[pos - 1].nMove) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nMove = nMove;
        MVP[pos].tElapsed = tElap;
        printf(" %d위 입니다. 이름을 입력하세요: ", pos + 1);
        scanf("%s", MVP[pos].name);
        return pos + 1;
    }
    return 0;
}

// 메인 함수
int main() {
    // 시스템 명령어로 chcp 65001을 실행하여 터미널의 인코딩을 UTF-8로 설정
    system("chcp 65001");

    // 나머지 게임 코드나 다른 기능들
    loadRanking("ranking.txt");  // 랭킹 로드
    int rank = playFifteenPuzzle();  // 게임 실행
    printf("현재 랭킹: %d위\n", rank);  // 현재 랭킹 출력
    printRanking();  // 현재 랭킹 출력
    storeRanking("ranking.txt");  // 랭킹 저장
    return 0;
}