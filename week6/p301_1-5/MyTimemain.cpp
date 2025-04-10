// main.cpp
#include <iostream>
#include "MyTime.h"

int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");  // 한국어 로케일로 설정

    MyTime time1;

    // 사용자로부터 시간 정보를 입력 받기
    time1.read();
    std::cout << "입력된 시간: ";
    time1.print();

    // 예시로 고정된 time2 설정
    MyTime time2;
    time2.convert(9930.3);  // 예시로 9930.3초로 설정

    // 1. 덧셈 결과 (반환 방식)
    MyTime result1 = time1.add(time2);
    std::cout << "덧셈 결과 (반환 방식): ";
    result1.print();

    // 2. 덧셈 결과 (참조 방식)
    MyTime result2;
    result2 = time1.add(time2);
    std::cout << "덧셈 결과 (참조 방식): ";
    result2.print();

    // 3. 덧셈 결과 (포인터 방식)
    MyTime result3;
    result3 = time1.add(time2);
    std::cout << "덧셈 결과 (포인터 방식): ";
    result3.print();

    return 0;
}