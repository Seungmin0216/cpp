// MyTime.h
#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>

class MyTime {
private:
    int hours, minutes;
    double seconds;  // 초는 double로 처리

public:
    // 기본 생성자
    MyTime(int h = 0, int m = 0, double s = 0.0);

    // 초 단위 실수 값을 시간으로 변환하는 함수
    void convert(double duration);

    // 시간 출력 함수 (자릿수 0으로 채우기)
    void print() const;

    // 사용자로부터 시간을 입력 받는 함수
    void read();

    // 다른 MyTime 객체와 덧셈하는 함수
    MyTime add(MyTime t);

    // 객체 초기화 함수
    void reset();

private:
    // 변환된 시간 객체를 반환하는 함수 (내부에서만 사용)
    MyTime convertAndReturn(double totalSeconds);
};

#endif // MYTIME_H