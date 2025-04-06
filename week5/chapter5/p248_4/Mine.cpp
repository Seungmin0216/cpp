#include "Mine.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define MAX_ROWS 40
#define MAX_COLS 80

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };

static int MineMapMask[MAX_ROWS][MAX_COLS];        // Hide, Open, Flag 상태
static int MineMapLabel[MAX_ROWS][MAX_COLS];       // 0~8 (주변 폭탄 개수), 9 (폭탄) 상태
static int nx = 9, ny = 9;                         // 기본 게임판 크기 (9x9)
static int nBomb = 9;                              // 기본 폭탄 개수 (9개)

// 게임판을 출력하는 함수
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }  // 유효한 좌표인지 체크
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }     // 폭탄이 있는지 체크
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }   // 빈 칸인지 체크

// (x, y) 위치를 공개하는 함수
static void dig(int x, int y) {
    if (isValid(x, y) && mask(x, y) != Open) {
        mask(x, y) = Open;
        if (label(x, y) == 0) {
            // 주변 8개 칸을 재귀적으로 공개
            dig(x - 1, y - 1);
            dig(x - 1, y);
            dig(x - 1, y + 1);
            dig(x, y - 1);
            dig(x, y + 1);
            dig(x + 1, y - 1);
            dig(x + 1, y);
            dig(x + 1, y + 1);
        }
    }
}

// (x, y) 위치에 플래그를 설정하는 함수
static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;  // 숨김 상태인 곳에만 플래그 설정
}

// 현재 게임판에서 플래그가 설정된 개수를 세는 함수
static int getBombCount() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;  // Flag가 설정된 위치마다 카운트
    return count;
}

// 게임판을 출력하는 함수
static void print() {
    system("cls");
    printf("   Flag: %2d   Total: %2d\n", getBombCount(), nBomb);
    printf("   게임판\n");

    // 가로 축 번호 출력
    printf("     ");
    for (int x = 0; x < nx; x++) {
        printf("%2d ", x + 1);  // 열 번호 (1부터 출력)
    }
    printf("\n");

    // 세로 축과 게임판 출력
    for (int y = 0; y < ny; y++) {
        printf("   %2c ", 'A' + y);  // 행 번호 (A부터 출력)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == Hide)    printf("■");        // 숨김 상태
            else if (mask(x, y) == Flag) printf("★");    // 플래그 상태
            else {                                    // 공개 상태
                if (isBomb(x, y)) printf("☠");        // 9: 폭탄!!
                else if (isEmpty(x, y)) printf("  ");    // 0: 빈 칸
                else printf("%2d", label(x, y));        // 1~8: 주변 폭탄 개수
            }
        }
        printf("\n");
    }
}

// (x, y) 주변의 폭탄 개수를 세는 함수
static int countNbrBombs(int x, int y) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == Bomb)  // 주변 8개의 칸을 체크하여 폭탄 개수 세기
                count++;
    return count;
}

// 게임판 초기화 함수
static void init(int total = 9) {
    srand((unsigned int)time(NULL));  // 난수 초기화
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            mask(x, y) = Hide;  // 모든 칸을 숨김 상태로 초기화
            label(x, y) = 0;     // 빈 칸으로 초기화
        }
    nBomb = total;  // 폭탄 개수 설정
    for (int i = 0; i < nBomb; i++) {  // 지뢰 배치
        int x, y;
        do {
            x = rand() % nx;  // 무작위 x 좌표
            y = rand() % ny;  // 무작위 y 좌표
        } while (label(x, y) != Empty);  // 이미 폭탄이 배치된 곳은 제외
        label(x, y) = Bomb;  // 폭탄 배치
    }
    // 각 칸에 대해 주변 폭탄 개수 계산
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);  // 빈 칸 주변의 폭탄 개수 계산
}

// 사용자로부터 위치 입력 받는 함수
static bool getPos(int& x, int& y) {
    printf("\n위치를 선택하세요 (A-I)와 (1-9)\n      입력 --> ");
    y = toupper(getchar()) - 'A';  // 세로 축은 A부터 시작
    x = getchar() - '1';            // 가로 축은 1부터 시작
    return false;  // 단순히 클릭한 위치가 폭탄인지 아닌지 판단하는 것에는 사용하지 않음
}

// 게임이 종료되었는지 확인하는 함수
static int checkDone() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) count++;  // 아직 열리지 않은 칸 수 카운트
            else if (isBomb(x, y)) return -1;  // 폭탄을 터뜨린 경우
        }
    return (count == nBomb) ? 1 : 0;  // 모든 폭탄을 찾은 경우 승리
}

// 실제 게임을 진행하는 함수
void playMineSweeper(int total) {
    int x, y, status;
    init(total);  // 게임판 초기화
    do {
        print();  // 게임판 출력
        bool isBomb = getPos(x, y);  // 사용자로부터 위치 입력 받기
        if (isBomb) mark(x, y);  // 폭탄일 경우 플래그 설정
        else dig(x, y);  // 아니면 공개
        status = checkDone();  // 게임 종료 여부 확인
    } while (status == 0);  // 게임이 끝날 때까지 반복
    print();
    if (status < 0)
        printf("\n게임 오버: 폭탄을 밟았습니다!!!\n\n");  // 폭탄을 밟은 경우
    else
        printf("\n게임 승리: 모두 찾았습니다!!!\n\n");  // 모든 폭탄을 찾은 경우
}

// 메인 함수
int main() {
    system("chcp 65001");  // 한글 출력 설정
    int total;
    printf(" <Mine Sweeper>\n");
    printf(" 총 게임판의 가로 크기 (1-80): ");
    scanf("%d", &nx);  // 게임판 가로 크기 입력 받기
    if (nx > 80) nx = 80;  // 최대 80칸까지

    printf(" 총 게임판의 세로 크기 (1-40): ");
    scanf("%d", &ny);  // 게임판 세로 크기 입력 받기
    if (ny > 40) ny = 40;  // 최대 40칸까지

    printf(" 총 폭탄 개수를 입력하세요: ");
    scanf("%d", &total);  // 폭탄 개수 입력 받기
    if (total > nx * ny) total = nx * ny;  // 폭탄 개수가 게임판 크기를 초과하지 않도록 설정

    playMineSweeper(total);  // 게임 진행
}