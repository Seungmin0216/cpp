#pragma once
#include <iostream>  // 입출력 라이브러리
#include <string>    // 문자열 처리 라이브러리
#define MAXLINES 100 // 캔버스에 표시할 최대 줄 수

using namespace std;

class Canvas {
    string line[MAXLINES]; // 화면에 그릴 수 있는 최대 줄 수 만큼의 문자열 배열
    int xMax, yMax;        // 캔버스의 크기 (너비, 높이)

public:
    // 생성자: 기본적으로 10x10 크기의 캔버스를 생성
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        // 각 줄을 공백으로 초기화
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, ' ');  // 2칸씩 띄워서 문자 배치
    }

    // 주어진 (x, y) 좌표에 val 값을 그리는 함수
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {  // 좌표가 유효한지 확인
            // 2칸씩 띄워서 문자 배치 (x * 2)
            line[y].replace(x * 2, val.size(), val);
        }
    }

    // 캔버스를 초기화하는 함수 (기본값은 ". "으로 초기화)
    void clear(string val = ". ") {
        for (int y = 0; y < yMax; y++) {    // 각 줄에 대해서
            for (int x = 0; x < xMax; x++) // 각 칸에 대해서
                draw(x, y, val);           // 기본값으로 초기화
        }
    }

    // 캔버스를 출력하는 함수
    void print(const char *title = "<My Canvas>") {
        // 화면 지우기 (운영체제에 맞춰 동작)
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");  // Windows에서 화면 지우기
        #else
            system("clear");  // Unix/Linux/Mac에서 화면 지우기
        #endif

        cout << title << endl;  // 제목 출력
        for (int y = 0; y < yMax; y++)  // 각 줄을 출력
            cout << line[y] << endl;
        cout << endl;  // 한 줄의 공백 출력
    }
};
