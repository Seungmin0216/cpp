#pragma once
#include <iostream>
using namespace std;

class Canvas {
    int width, height;   // 캔버스의 너비와 높이
    char** canvas;       // 캔버스를 2D 배열로 저장 (각각의 문자를 저장)

public:
    // 생성자: 캔버스를 주어진 크기로 초기화
    Canvas(int w, int h) : width(w), height(h) {
        canvas = new char*[height];  // 각 행을 동적으로 할당
        for (int i = 0; i < height; i++) {
            canvas[i] = new char[width];  // 각 열을 동적으로 할당
            for (int j = 0; j < width; j++) {
                canvas[i][j] = '.';  // 캔버스를 공백으로 초기화
            }
        }
    }

    // 소멸자: 할당된 메모리를 해제
    ~Canvas() {
        for (int i = 0; i < height; i++) {
            delete[] canvas[i];  // 각 행을 해제
        }
        delete[] canvas;  // 2D 배열 자체를 해제
    }

    // 캔버스를 초기화하는 함수: 모든 칸을 공백('.')으로 설정
    void clear() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                canvas[i][j] = '.';  // 모든 칸을 공백으로 초기화
            }
        }
    }

    // 특정 위치(x, y)에 심볼을 그리는 함수
    void draw(int x, int y, const char* symbol) {
        canvas[y][x] = symbol[0];  // 심볼의 첫 번째 문자만 사용하여 해당 위치에 그리기
    }

    // 캔버스를 출력하는 함수
    void print(const char* title = "<My Canvas>") {
        cout << title << endl;  // 타이틀을 출력
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << canvas[i][j] << ' ';  // 각 칸을 공백과 함께 출력
            }
            cout << endl;  // 한 줄을 다 출력한 후에는 줄 바꿈
        }
    }
};