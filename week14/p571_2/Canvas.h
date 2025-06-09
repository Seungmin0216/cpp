#pragma once
#include <iostream>
#include <string>
#include "Point.h"            // Point 클래스 헤더 파일 포함
#define MAXLINES 100          // 최대 줄 수 정의

using namespace std;

// 캔버스 클래스 정의
class Canvas {
    string line[MAXLINES];    // 각 줄의 문자열을 저장할 배열
    int xMax, yMax;           // 캔버스의 너비(xMax)와 높이(yMax)

public:
    // 생성자: 기본 크기는 10x10, 캔버스를 공백 문자로 초기화
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, ' '); // 2칸씩 확보(간격용)
    }

    // 좌표 (x, y)에 문자열 val을 그림
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            line[y].replace(x * 2, 2, val);  // 2칸씩 간격 두고 그림
    }

    // Point 객체를 이용해 그림 (오버로딩)
    void draw(Point& p, string val) {
        draw(p.x, p.y, val);
    }

    // 캔버스를 초기화 (기본값 ". " 으로 채움)
    void clear(string val = ". ") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }

    // 캔버스를 화면에 출력
    void print(char* title = (char*)"<My Canvas>") {
        system("cls"); // 콘솔 화면 지우기 (Windows 전용)
        cout << title << endl;
        for (int y = 0; y < yMax; y++)
            cout << line[y] << endl;
        cout << endl;
    }
};
