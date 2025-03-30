#ifndef _PUZZLEGAME_H
#define _PUZZLEGAME_H

#include <time.h>

// 퍼즐 게임 크기
#define DIM 4           // 4x4 퍼즐 게임

// 방향키 정의 (문자로 수정)
enum Direction { Left = 'a', Right = 'd', Up = 'w', Down = 's' };

// 퍼즐 게임 함수들
void init();                      // 게임 초기화
void display();                   // 게임 화면 출력
bool move(int dir);               // 퍼즐 이동 함수
void shuffle(int nShuffle);       // 퍼즐 섞기
bool isDone();                    // 퍼즐 완료 여부 체크
int getDirKey();                  // 방향키 입력 받기 (수정된 함수)
int playFifteenPuzzle();          // 게임 실행

// 랭킹 관리 관련 함수들
void loadRanking(const char* fname);     // 랭킹 로드
void storeRanking(const char* fname);    // 랭킹 저장
void printRanking();                   // 랭킹 출력
int addRanking(int nMove, double tElap);  // 랭킹 추가

#endif // _PUZZLEGAME_H