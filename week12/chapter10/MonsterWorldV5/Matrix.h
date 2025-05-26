#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix {
	int rows, cols;      // 행과 열의 크기
	int** mat;           // 2차원 배열로 행렬 저장
public:
	Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
		mat = new int*[rows];
		for (int i = 0; i < rows; i++)
			mat[i] = new int[cols];
	}

	~Matrix() {
		if (mat != NULL) {
			for (int i = 0; i < rows; i++)
				delete[] mat[i];
			delete[] mat;
		}
	}

	// (x, y) 위치의 요소에 접근
	int& elem(int x, int y) { return mat[y][x]; }

	// 행의 개수 반환
	int Rows() { return rows; }

	// 열의 개수 반환
	int Cols() { return cols; }

	// 행렬 데이터 반환
	int** Data() { return mat; }

	// 행렬 출력
	void print(char* str = "Mat") {
		cout << str << " " << rows << "x" << cols << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				cout << setw(4) << mat[i][j];
			cout << "\n";
		}
	}

	// 무작위 값으로 행렬 채우기 (기본 최대값 100)
	void setRand(int val = 100) {
		if (mat != NULL) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					mat[i][j] = (rand() % val);
		}
	}
};
