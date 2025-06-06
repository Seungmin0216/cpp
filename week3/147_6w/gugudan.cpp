#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>  // pow 함수 사용을 위한 헤더
#include "gugudan.h"  // 헤더 파일 포함

using namespace std;




// 구구단 게임
void playGuguOnce() {
    int a = rand() % 9 + 1;
    int b = rand() % 9 + 1;
    int answer;
    
    // 사용자가 정답을 맞힐 때까지 반복
    do {
        cout << a << " x " << b << " = ? ";
        cin >> answer;

        if (answer == a * b) {
            cout << "정답!\n";
        } else {
            cout << "틀렸습니다. 정답: " << a * b << "\n";
        }
    } while (answer != a * b);  // 정답을 맞힐 때까지 반복
}

// 두 자리 수 곱셈 게임
void playMultiplication() {
    int a = rand() % 90 + 10;  // 10~99 사이의 숫자
    int b = rand() % 90 + 10;  // 10~99 사이의 숫자
    int answer;

    // 사용자가 정답을 맞힐 때까지 반복
    do {
        cout << a << " x " << b << " = ? ";
        cin >> answer;

        if (answer == a * b) {
            cout << "정답!\n";
        } else {
            cout << "틀렸습니다. 정답: " << a * b << "\n";
        }
    } while (answer != a * b);  // 정답을 맞힐 때까지 반복
}

// 여러 자리 수 덧셈 게임
void playAddition(int digits) {
    int num1 = rand() % (int)pow(10, digits);  // digits 자리 수로 랜덤 숫자 생성
    int num2 = rand() % (int)pow(10, digits);  // digits 자리 수로 랜덤 숫자 생성
    int answer;

    // 사용자가 정답을 맞힐 때까지 반복
    do {
        cout << num1 << " + " << num2 << " = ? ";
        cin >> answer;

        if (answer == num1 + num2) {
            cout << "정답!\n";
        } else {
            cout << "틀렸습니다. 정답: " << num1 + num2 << "\n";
        }
    } while (answer != num1 + num2);  // 정답을 맞힐 때까지 반복
}

// 게임 시작 함수
void startGame() {
    srand(time(0));  // 랜덤 시드 설정
    int choice;

    cout << "게임을 선택하세요: \n";
    cout << "1: 구구단 게임\n";
    cout << "2: 두 자리 수 곱셈\n";
    cout << "3~9: 해당 자리 수 덧셈\n";
    cin >> choice;

    if (choice == 1) {
        playGuguOnce();
    } else if (choice == 2) {
        playMultiplication();
    } else if (choice >= 3 && choice <= 9) {
        playAddition(choice);
    } else {
        cout << "잘못된 선택입니다.\n";
    }
}

// main 함수
int main() {
    startGame();  // 게임 시작
    return 0;
}