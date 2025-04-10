#include <iostream>
#include <cmath>
#include <iomanip>  // 입출력 조작자를 사용하기 위한 헤더
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

    // 시간 출력 함수 (자릿수 0으로 채우기)
    inline void print() const {
        cout << setfill('0')  // 빈 자리를 0으로 채운다.
             << setw(2) << hours << " 시간 "    // 2자리로 출력
             << setw(2) << minutes << " 분 "   // 2자리로 출력
             << fixed << setprecision(2)  // 소수점 2자리까지 출력
             << setw(5) << seconds << " 초"  // 초는 5자리로 맞추기 (소수점 포함)
             << endl;
    }

    // 사용자로부터 시간을 입력 받는 함수
    inline void read() {
        cout << "시간을 입력하세요 (시간, 분, 초 순으로 입력): ";
        cin >> hours >> minutes >> seconds;
        // 입력 값이 올바른 범위에 있는지 확인
        if (hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
            cout << "입력값이 잘못되었습니다. 시간은 0 이상, 분과 초는 0~59 사이여야 합니다." << endl;
            reset();  // 잘못된 입력을 받으면 초기화
        }
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

    MyTime time1;

    // 사용자로부터 시간 정보를 입력 받기
    time1.read();
    cout << "입력된 시간: ";
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