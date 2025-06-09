#pragma once
#include <iostream>
#include <cmath>
using namespace std;

// Point 클래스: 2차원 좌표(x, y)를 표현하며 연산자 오버로딩 제공
class Point {
	int x, y;  // 멤버 변수: x좌표, y좌표

	// Monster, Canvas 클래스가 Point의 private 멤버에 접근할 수 있도록 friend 선언
	friend class Monster;
	friend class Canvas;

public:
	// 생성자: 기본값 (0, 0)
	Point(int xx = 0, int yy = 0) : x(xx), y(yy) { }

	// [] 연산자 오버로딩: 인덱스로 x 또는 y 반환
	int& operator[] (int id) {
		if (id == 0) return x;     // 0이면 x좌표 반환
		else if (id == 1) return y; // 1이면 y좌표 반환
		else exit(0);              // 그 외는 비정상 종료
	}

	// double형 변환 연산자: 원점으로부터의 거리 반환
	operator double() {
		return sqrt((double)x * x + y * y);
	}

	// () 연산자 오버로딩: 좌표 값을 주어진 최대값 내로 클리핑
	void operator()(int maxx, int maxy) {
		if (x < 0) x = 0;
		if (x >= maxx) x = maxx - 1;
		if (y < 0) y = 0;
		if (y >= maxy) y = maxy - 1;
	}

	// 단항 마이너스 연산자 오버로딩: 좌표 부호 반전
	Point operator- () {
		return Point(-x, -y);
	}

	// == 연산자: 좌표 값 비교 (같은 좌표인지)
	bool operator== (Point& p) {
		return x == p.x && y == p.y;
	}

	// != 연산자: 좌표 값 비교 (다른 좌표인지)
	bool operator!= (Point& p) {
		return x != p.x || y != p.y;
	}

	// - 연산자: 두 좌표 간 차이 반환
	Point operator- (Point& p) {
		return Point(x - p.x, y - p.y);
	}

	// + 연산자: 두 좌표 더하기
	Point operator+ (Point& p) {
		return Point(x + p.x, y + p.y);
	}

	// += 연산자: 현재 좌표에 다른 좌표 더하기
	void operator+= (Point& p) {
		x += p.x;
		y += p.y;
	}

	// -= 연산자: 현재 좌표에서 다른 좌표 빼기
	void operator-= (Point& p) {
		x -= p.x;
		y -= p.y;
	}
};
