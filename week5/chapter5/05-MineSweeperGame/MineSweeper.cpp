#include "MineSweeper.h"
#define DIM    9

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };
static int MineMapMask[DIM][DIM];        // Hide, Open, Flag
static int MineMapLabel[DIM][DIM];        // 0~8, 9(Bomb)
static int nx = DIM, ny = DIM;
static int nBomb = DIM;

// 게임 상태 출력 함수. 화면 갱신
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y) {            // (x, y) 위치를 공개하는 함수
    if (isValid(x, y) && mask(x, y) != Open) {
        mask(x, y) = Open;
        if (label(x, y) == 0) {
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
static void mark(int x, int y) {            // (x, y) 위치에 플래그를 설정하는 함수
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;
}
static int getBombCount() {                // 플래그 개수를 세는 함수
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;
    return count;
}
static void print() {                    // 게임 상태 출력 함수
    system("cls");
    printf("   Flag: %2d   Total: %2d\n", getBombCount(), nBomb);
    printf("   게임판\n");
    for (int y = 0; y < ny; y++) {
        printf("%2c ", 'A' + y);
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
static int countNbrBombs(int x, int y) {    // (x, y) 주변의 폭탄 개수를 세는 함수
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == Bomb)
                count++;
    return count;
}
static void init(int total = 9) {
    srand((unsigned int)time(NULL));
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {            // 지도를, 초기화
            mask(x, y) = Hide;
            label(x, y) = 0;
        }
    nBomb = total;
    for (int i = 0; i < nBomb; i++) {        // 폭탄 배치 (total 개수만큼)
        int x, y;
        do {
            x = rand() % nx;
            y = rand() % ny;
        } while (label(x, y) != Empty);
        label(x, y) = Bomb;
    }
    for (int y = 0; y < ny; y++)            // 주변 폭탄 개수 계산
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);
}
static bool getPos(int& x, int& y) {        // 사용자 입력을 받는 함수 
    printf("\n위치를 선택하세요 (A-I)와 (1-9)\n      입력 --> ");
    bool isBomb = false;
    y = toupper(getch()) - 'A';            // 'a' -> 'A' 'A' --> 0
    if (y == 'P' - 'A') {
        isBomb = true;
        y = toupper(getche()) - 'A';        // 'a' -> 'A' 'A' --> 0
    }
    x = getch() - '1';                    // '1' --> 1
    return isBomb;
}
static int checkDone() {                // 게임 종료 체크 함수
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) count++;
            else if (isBomb(x, y)) return -1;
        }
    return (count == nBomb) ? 1 : 0;
}
void playMineSweeper(int total) {        // 게임 진행 함수
    int x, y, status;
    init(total);                    // 게임판 초기화
    do {
        print();
        bool isBomb = getPos(x, y);    // 위치 입력
        if (isBomb) mark(x, y);        // 플래그 설정
        else          dig(x, y);        // 공개
        status = checkDone();        // 게임 종료 체크
    } while (status == 0);            // 게임이 끝날 때까지 반복
    print();
    if (status < 0)                 // 폭탄을 터뜨린 경우
        printf("\n게임 오버: 폭탄을 밟았습니다!!!\n\n");
    else    printf("\n게임 승리: 모두 찾았습니다!!!\n\n");
}

int main()
{
	system("chcp 65001");
    int total;
    printf(" <Mine Sweeper>\n");
    printf(" 총 폭탄 개수를 입력하세요: ");
    scanf("%d", &total);
    playMineSweeper(total);
}