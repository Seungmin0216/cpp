#include <iostream>
#include <cmath>
using namespace std;

class MyTime {
private:
    int hours, minutes;
    double seconds;  // 초는 double로 처리

public:
    // 기본 생성자
    inline MyTime(int h = 0, int m = 0, double s = 0.0) : hours(h), minutes(m), seconds(s) {}

    // 초 단위 실수 값을 시간으로 변환하는 함수
    inline void convert(double duration) {
        hours = static_cast<int>(duration) / 3600;
        duration = fmod(duration, 3600);
        minutes = static_cast<int>(duration) / 60;
        seconds = fmod(duration, 60);
    }

    // 시간 출력 함수
    inline void print() const {
        cout << hours << " 시간 " << minutes << " 분 " << seconds << " 초" << endl;
    }

    // 다른 MyTime 객체와 덧셈하는 함수
    inline MyTime add(MyTime t) {
        double totalSeconds = hours * 3600 + minutes * 60 + seconds + t.hours * 3600 + t.minutes * 60 + t.seconds;
        return MyTime::convertAndReturn(totalSeconds);
    }

    // 객체 초기화 함수
    inline void reset() {
        hours = minutes = 0;
        seconds = 0.0;
    }

private:
    // 변환된 시간 객체를 반환하는 함수 (내부에서만 사용)
    inline MyTime convertAndReturn(double totalSeconds) {
        int h = static_cast<int>(totalSeconds) / 3600;
        totalSeconds = fmod(totalSeconds, 3600);
        int m = static_cast<int>(totalSeconds) / 60;
        double s = fmod(totalSeconds, 60);
        return MyTime(h, m, s);
    }
};

int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");  // 한국어 로케일로 설정

    double inputSeconds;

    // 사용자로부터 초 단위 실수 입력 받기
    cout << "초 단위로 시간을 입력하세요 (예: 3671.78): ";
    cin >> inputSeconds;

    // 초 단위 실수를 MyTime으로 변환
    MyTime time1;
    time1.convert(inputSeconds);
    cout << "변환된 시간: ";
    time1.print();

    // 예시로 고정된 time2 설정
    MyTime time2;
    time2.convert(9930.3);  // 예시로 9930.3초로 설정

    // 1. 덧셈 결과 (반환 방식)
    MyTime result1 = time1.add(time2);
    cout << "덧셈 결과 (반환 방식): ";
    result1.print();

    // 2. 덧셈 결과 (참조 방식)
    MyTime result2;
    result2 = time1.add(time2);
    cout << "덧셈 결과 (참조 방식): ";
    result2.print();

    // 3. 덧셈 결과 (포인터 방식)
    MyTime result3;
    result3 = time1.add(time2);
    cout << "덧셈 결과 (포인터 방식): ";
    result3.print();

    return 0;
}