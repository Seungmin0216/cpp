#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

// Matrix 클래스: 2차원 정수 행렬을 표현
class Matrix {
    int rows, cols;    // 행과 열의 수
    int** mat;         // 2차원 동적 배열

public:
    // 생성자: 주어진 행(r)과 열(c) 크기로 메모리 할당
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
        mat = new int*[rows];              // 행 포인터 배열 할당
        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols];        // 각 행에 열 배열 할당
    }

    // 소멸자: 동적으로 할당된 메모리 해제
    ~Matrix() {
        if (mat != NULL) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];           // 각 행 삭제
            delete[] mat;                  // 행 포인터 배열 삭제
        }
    }

    // 특정 위치(x, y)의 요소를 참조 반환 (x: 열, y: 행)
    int& elem(int x, int y) { 
        return mat[y][x]; 
    }

    // 행 개수 반환
    int Rows() { 
        return rows; 
    }

    // 열 개수 반환
    int Cols() { 
        return cols; 
    }

    // 행렬 데이터 포인터 반환 (2차원 배열 접근용)
    int** Data() { 
        return mat; 
    }

    // 행렬 출력 함수
    void print(char* str = (char*)"Mat") {
        cout << str << " " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << setw(4) << mat[i][j];   // 포맷 맞춰 출력
            cout << "\n";
        }
    }

    // 행렬에 난수 값 채우기 (기본 최대값 100)
    void setRand(int val = 100) {
        if (mat != NULL) {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    mat[i][j] = (rand() % val);
        }
    }
};
