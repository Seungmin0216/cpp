#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix {
	int rows, cols;      // 행(row)과 열(column)의 크기
	int** mat;           // 2차원 정수 배열을 위한 포인터

public:
	// 생성자: 행과 열의 크기를 받아 동적 배열 생성
	Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
		mat = new int*[rows];               // 행 수만큼 포인터 배열 생성
		for (int i = 0; i < rows; i++)
			mat[i] = new int[cols];         // 각 행에 대해 열 수만큼 정수 배열 할당
	}

	// 소멸자: 동적으로 할당된 메모리 해제
	~Matrix() {
		if (mat != NULL) {
			for (int i = 0; i < rows; i++)
				delete[] mat[i];            // 각 행의 배열 삭제
			delete[] mat;                  // 행 포인터 배열 삭제
		}
	}

	// 원소 접근 함수 (x: 열 인덱스, y: 행 인덱스)
	int& elem(int x, int y) { return mat[y][x]; }

	// 행 개수 반환
	int Rows() { return rows; }

	// 열 개수 반환
	int Cols() { return cols; }

	// 전체 데이터 반환 (2차원 배열 포인터)
	int** Data() { return mat; };

	// 행렬 출력 함수
	void print(char *str = (char*)"Mat") {
		cout << str << " " << rows << "x" << cols << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				cout << setw(4) << mat[i][j];  // 각 원소를 4칸 너비로 출력
			cout << "\n";
		}
	}

	// 행렬의 각 원소를 0 ~ val-1 사이의 난수로 초기화
	void setRand(int val = 100) {
		if (mat != NULL) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					mat[i][j] = (rand() % val);
		}
	}
};