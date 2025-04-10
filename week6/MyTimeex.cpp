#include <iostream>
#include <cmath>
using namespace std;

class MyTime {
public:
    int hours, minutes;
    double seconds;  // double로 변경

    // 기본 생성자
    MyTime(int h = 0, int m = 0, double s = 0.0) : hours(h), minutes(m), seconds(s) {}

    // 시간 값을 출력하는 함수
    void print() const {
        cout << hours << " 시간 " << minutes << " 분 " << seconds << " 초" << endl;
    }
};

// 초 단위 실수 값을 MyTime으로 변환하는 함수
MyTime convertSecondsToMyTime(double totalSeconds) {
    int hours = static_cast<int>(totalSeconds) / 3600;
    totalSeconds = fmod(totalSeconds, 3600);
    int minutes = static_cast<int>(totalSeconds) / 60;
    double seconds = fmod(totalSeconds, 60);  // 소수 초 포함

    return MyTime(hours, minutes, seconds);
}

// 1. 두 시간을 더한 후 새로운 MyTime 객체를 반환
MyTime addTime(MyTime t1, MyTime t2) {
    double totalSeconds = t1.hours * 3600 + t1.minutes * 60 + t1.seconds +
                          t2.hours * 3600 + t2.minutes * 60 + t2.seconds;

    return convertSecondsToMyTime(totalSeconds);
}

// 2. 참조로 결과 전달
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    double totalSeconds = t1.hours * 3600 + t1.minutes * 60 + t1.seconds +
                          t2.hours * 3600 + t2.minutes * 60 + t2.seconds;

    t3 = convertSecondsToMyTime(totalSeconds);
}

// 3. 포인터로 결과 전달
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    double totalSeconds = t1.hours * 3600 + t1.minutes * 60 + t1.seconds +
                          t2.hours * 3600 + t2.minutes * 60 + t2.seconds;

    *pt = convertSecondsToMyTime(totalSeconds);
}

int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");  // 한국어 로케일로 설정
    double inputSeconds;

    // 사용자로부터 초 단위 실수 입력 받기
    cout << "초 단위로 시간을 입력하세요 (예: 3671.78): ";
    cin >> inputSeconds;

    // 초 단위 실수 입력을 MyTime으로 변환
    MyTime converted = convertSecondsToMyTime(inputSeconds);
    cout << "변환된 시간: ";
    converted.print();

    // 사용자 입력을 바탕으로 덧셈을 수행할 time1과 time2 생성
    MyTime time1 = convertSecondsToMyTime(inputSeconds);  // 사용자가 입력한 초로 time1 초기화
    MyTime time2 = MyTime(2, 45, 30.3);  // 예시로 고정된 값으로 time2 설정

    // 1. 반환 방식
    MyTime result1 = addTime(time1, time2);
    cout << "덧셈 결과 (반환 방식): ";
    result1.print();

    // 2. 참조 방식
    MyTime result2;
    addTime(time1, time2, result2);
    cout << "덧셈 결과 (참조 방식): ";
    result2.print();

    // 3. 포인터 방식
    MyTime result3;
    addTime(time1, time2, &result3);
    cout << "덧셈 결과 (포인터 방식): ";
    result3.print();

    return 0;
}