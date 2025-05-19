#pragma once
#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;

class Canvas {
	string line[MAXLINES];	// 화면에 출력할 문자열 배열
	int xMax, yMax;			// 캔버스의 가로(x), 세로(y) 크기

public:
	Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax * 2, ' ');	// 각 줄을 공백으로 초기화 (문자열 길이는 xMax * 2)
	}

	void draw(int x, int y, string val) {
		// 주어진 좌표(x, y)에 문자열 val을 그린다 (문자열 길이는 2)
		if (x >= 0 && y >= 0 && x < xMax && y < yMax)
			line[y].replace(x * 2, 2, val);	// x 좌표에 대응되는 인덱스는 x * 2
	}

	void clear(string val = ". ") {
		// 캔버스를 주어진 문자열로 채운다 (기본값은 ". ")
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				draw(x, y, val);
	}

	void print(const char *title = (char*)"<My Canvas>") {
		// 콘솔 화면을 지우고 캔버스를 출력한다
		system("cls");	// Windows 전용 콘솔 클리어
		cout << title << endl;
		for (int y = 0; y < yMax; y++)
			cout << line[y] << endl;
		cout << endl;
	}
};