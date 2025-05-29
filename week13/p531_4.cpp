#include <iostream>
#include <cstdlib>  // rand()
#include <ctime>    // time()
#include <stdexcept>  // out_of_range
using namespace std;

class Samplelist {
    int list[100];  // 크기 100의 정수형 배열

public:
    // 생성자: 배열을 0~999 사이의 난수로 초기화
    Samplelist() {
        for (int x = 0; x < 100; x++) {
            list[x] = rand() % 1000;
        }
    }

    // 1. 인덱스 연산자 중복: s[10]처럼 사용 가능 (참조자 반환)
    int& operator[](int index) {
        if (index < 0 || index >= 100) {
            throw out_of_range("Index out of range");
        }
        return list[index];
    }

    // 2. 함수 호출 연산자 중복: s(10)처럼 사용 가능 (참조자 반환)
    int& operator()(int index) {
        if (index < 0 || index >= 100) {
            throw out_of_range("Index out of range");
        }
        return list[index];
    }

    // 3. 함수 호출 연산자 중복 (두 수를 곱한 인덱스를 이용): s(2, 5) → list[10]
    int& operator()(int a, int b) {
        int index = a * b;
        if (index < 0 || index >= 100) {
            throw out_of_range("Index out of range");
        }
        return list[index];
    }

    // 리스트 출력용 함수 (확인용)
    void print() const {
        for (int i = 0; i < 100; i++) {
            cout << list[i] << " ";
        }
        cout << endl;
    }
};

// 메인 함수: 연산자 중복 기능 테스트
int main() {
    // 난수 시드 초기화
    srand(static_cast<unsigned int>(time(0)));

    Samplelist s;

    // 배열 출력 (선택)
    cout << "== 초기 배열 ==" << endl;
    s.print();

    // 1. 인덱스 연산자 사용 예시
    cout << "\n== 인덱스 연산자 [] ==" << endl;
    cout << "s[10] = " << s[10] << endl;
    s[10] = 777;  // 값 수정
    cout << "s[10] (수정 후) = " << s[10] << endl;

    // 2. 함수 호출 연산자 사용 (한 개의 인자)
    cout << "\n== 함수 호출 연산자 (하나의 인자) ==" << endl;
    cout << "s(20) = " << s(20) << endl;

    // 3. 함수 호출 연산자 사용 (두 개의 인자)
    cout << "\n== 함수 호출 연산자 (두 개의 인자) ==" << endl;
    cout << "s(2, 5) = " << s(2, 5) << endl;
    s(2, 5) = 888;  // list[10]에 해당하는 항목 변경
    cout << "s[10] (s(2, 5) = 888 후) = " << s[10] << endl;

    return 0;
}