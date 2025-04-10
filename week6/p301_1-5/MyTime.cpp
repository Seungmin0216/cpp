// MyTime.cpp
#include "MyTime.h"
#include <iomanip>  // 입출력 조작자를 사용하기 위한 헤더
#include <cmath>    // fmod 함수 사용을 위한 헤더

// 기본 생성자
MyTime::MyTime(int h, int m, double s) : hours(h), minutes(m), seconds(s) {}

// 초 단위 실수 값을 시간으로 변환하는 함수
void MyTime::convert(double duration) {
    hours = static_cast<int>(duration) / 3600;
    duration = fmod(duration, 3600);
    minutes = static_cast<int>(duration) / 60;
    seconds = fmod(duration, 60);
}

// 시간 출력 함수 (자릿수 0으로 채우기)
void MyTime::print() const {
    std::cout << std::setfill('0')  // 빈 자리를 0으로 채운다.
              << std::setw(2) << hours << " 시간 "    // 2자리로 출력
              << std::setw(2) << minutes << " 분 "   // 2자리로 출력
              << std::fixed << std::setprecision(2)  // 소수점 2자리까지 출력
              << std::setw(5) << seconds << " 초"  // 초는 5자리로 맞추기 (소수점 포함)
              << std::endl;
}

// 사용자로부터 시간을 입력 받는 함수
void MyTime::read() {
    std::cout << "시간을 입력하세요 (시간, 분, 초 순으로 입력): ";
    std::cin >> hours >> minutes >> seconds;
    // 입력 값이 올바른 범위에 있는지 확인
    if (hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
        std::cout << "입력값이 잘못되었습니다. 시간은 0 이상, 분과 초는 0~59 사이여야 합니다." << std::endl;
        reset();  // 잘못된 입력을 받으면 초기화
    }
}

// 다른 MyTime 객체와 덧셈하는 함수
MyTime MyTime::add(MyTime t) {
    double totalSeconds = hours * 3600 + minutes * 60 + seconds + t.hours * 3600 + t.minutes * 60 + t.seconds;
    return convertAndReturn(totalSeconds);
}

// 객체 초기화 함수
void MyTime::reset() {
    hours = minutes = 0;
    seconds = 0.0;
}

// 변환된 시간 객체를 반환하는 함수 (내부에서만 사용)
MyTime MyTime::convertAndReturn(double totalSeconds) {
    int h = static_cast<int>(totalSeconds) / 3600;
    totalSeconds = fmod(totalSeconds, 3600);
    int m = static_cast<int>(totalSeconds) / 60;
    double s = fmod(totalSeconds, 60);
    return MyTime(h, m, s);
}