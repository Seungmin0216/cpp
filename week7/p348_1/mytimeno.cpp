#include <iostream>
#include <cmath>
using namespace std;

class MyTime {
public:
    int hours, minutes;
    double seconds;  // 초는 실수형
    int milliseconds;  // 밀리초는 정수형

    // 생성자: 초기화 리스트를 사용하지 않고 본문에서 멤버 변수에 값 할당
    MyTime(int h = 0, int m = 0, double s = 0.0, int ms = 0) {
        hours = h;  // hours 변수에 h 값을 할당
        minutes = m;  // minutes 변수에 m 값을 할당
        seconds = s;  // seconds 변수에 s 값을 할당
        milliseconds = ms;  // milliseconds 변수에 ms 값을 할당
    }

    // 시간 출력 함수
    void print() const {
        cout << hours << " 시간 " << minutes << " 분 " << seconds << " 초 " << milliseconds << " 밀리초" << endl;
    }
};

// 초 단위 실수 값을 MyTime 객체로 변환하는 함수
MyTime convertSecondsToMyTime(double totalSeconds) {
    int hours = static_cast<int>(totalSeconds) / 3600;  // 시간 계산
    totalSeconds = fmod(totalSeconds, 3600);  // 남은 초 계산
    int minutes = static_cast<int>(totalSeconds) / 60;  // 분 계산
    double seconds = fmod(totalSeconds, 60);  // 남은 초 계산

    // 밀리초를 계산하기 위해 초 부분의 소수점을 밀리초로 변환
    int milliseconds = static_cast<int>((seconds - static_cast<int>(seconds)) * 1000);

    return MyTime(hours, minutes, static_cast<int>(seconds), milliseconds);  // MyTime 객체로 반환
}

// 1. 두 시간을 더한 후 새로운 MyTime 객체를 반환
MyTime addTime(MyTime t1, MyTime t2) {
    // 각 시간, 분, 초, 밀리초를 초 단위로 환산하여 더하기
    double totalMilliseconds = (t1.hours * 3600 + t1.minutes * 60 + t1.seconds) * 1000 + t1.milliseconds +
                               (t2.hours * 3600 + t2.minutes * 60 + t2.seconds) * 1000 + t2.milliseconds;

    // 결과를 MyTime으로 변환하여 반환
    return convertSecondsToMyTime(totalMilliseconds / 1000.0);
}

// 2. 참조로 결과 전달
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    double totalMilliseconds = (t1.hours * 3600 + t1.minutes * 60 + t1.seconds) * 1000 + t1.milliseconds +
                               (t2.hours * 3600 + t2.minutes * 60 + t2.seconds) * 1000 + t2.milliseconds;

    t3 = convertSecondsToMyTime(totalMilliseconds / 1000.0);  // 참조를 통해 t3에 덧셈 결과 저장
}

// 3. 포인터로 결과 전달
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    double totalMilliseconds = (t1.hours * 3600 + t1.minutes * 60 + t1.seconds) * 1000 + t1.milliseconds +
                               (t2.hours * 3600 + t2.minutes * 60 + t2.seconds) * 1000 + t2.milliseconds;

    *pt = convertSecondsToMyTime(totalMilliseconds / 1000.0);  // 포인터를 통해 t3에 덧셈 결과 저장
}

int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");  // 한국어 로케일로 설정
    int inputHours, inputMinutes;
    double inputSeconds;
    int inputMilliseconds;

    // 사용자로부터 시간, 분, 초, 밀리초 입력 받기
    cout << "시간, 분, 초, 밀리초 형식으로 입력하세요 (예: 2 45 30.3 500): ";
    cin >> inputHours >> inputMinutes >> inputSeconds >> inputMilliseconds;

    // 입력받은 시간, 분, 초, 밀리초로 MyTime 객체 생성
    MyTime converted(inputHours, inputMinutes, inputSeconds, inputMilliseconds);
    cout << "입력된 시간: ";
    converted.print();  // 입력받은 시간 출력

    MyTime time1 = converted;  // 입력받은 값을 time1에 저장
    MyTime time2 = MyTime(2, 45, 30.3, 500);  // 예시 값으로 time2 설정 (2시간 45분 30.3초 500밀리초)

    // 1. 반환 방식으로 시간 더하기
    MyTime result1 = addTime(time1, time2);  // 반환값으로 덧셈 결과 받아옴
    cout << "덧셈 결과 (반환 방식): ";
    result1.print();  // 덧셈 결과 출력

    // 2. 참조 방식으로 시간 더하기
    MyTime result2;
    addTime(time1, time2, result2);  // 참조 방식으로 덧셈 결과를 result2에 저장
    cout << "덧셈 결과 (참조 방식): ";
    result2.print();  // 덧셈 결과 출력

    // 3. 포인터 방식으로 시간 더하기
    MyTime result3;
    addTime(time1, time2, &result3);  // 포인터 방식으로 덧셈 결과를 result3에 저장
    cout << "덧셈 결과 (포인터 방식): ";
    result3.print();  // 덧셈 결과 출력

    return 0;
}
