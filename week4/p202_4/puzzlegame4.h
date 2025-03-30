#ifndef PUZZLEGAME4_H
#define PUZZLEGAME4_H

// 게임에 필요한 상수와 enum 정의
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };  // 헤더 파일에 정의

// 기타 정의 및 함수 선언
#define DIM 4
#define NUM_MVP 5

struct PlayInfo {
    char name[20];
    int nMove;
    double tElapsed;
};

// 게임 관련 함수 선언
void init();
void display();
bool move(int dir);
void shuffle(int nShuffle);
bool isDone();
int getDirKey();
int playFifteenPuzzle();
void loadRanking(const char* fname);
void storeRanking(const char* fname);
void printRanking();
int addRanking(int nMove, double tElap);
void saveGame(const char* filename);
void loadGame(const char* filename);
void initRanking();

#endif