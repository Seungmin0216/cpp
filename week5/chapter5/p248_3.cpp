// 두 개의 시간을 더하는 다음 함수를 다음과 같이 세 방법으로 구현하라. 
// 각 방법의 차이를 설명하라.
#include <iostream>
using namespace std;

class MyTime {
public:
    int hours, minutes, seconds;

    // 기본 생성자
    MyTime(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}

    // 시간 값을 출력하는 함수
    void print() const {
        cout << hours << " hours " << minutes << " minutes " << seconds << " seconds" << endl;
    }
};

// 1. 두 시간을 더한 후 새로운 MyTime 객체를 반환
//장점: 직관적이고 함수 호출 후 반환된 객체를 직접 사용할 수 있어 코드가 깔끔하다.
//단점: 반환된 객체를 복사해야 하므로 '객체 복사 비용'이 발생할 수 있다.
MyTime addTime(MyTime t1, MyTime t2) {
    int totalSeconds = t1.hours * 3600 + t1.minutes * 60 + t1.seconds +
                       t2.hours * 3600 + t2.minutes * 60 + t2.seconds;

    int hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    return MyTime(hours, minutes, seconds);
}

// 2. 두 시간을 더한 후 참조를 통해 결과를 전달
//장점: 반환 값 없이 함수 내에서 객체를 수정하므로 '객체 복사 비용'이 없으며, t3 객체를 수정할 수 있다.
//단점: t3 객체가 함수 외부에서 미리 준비되어 있어야 하며, 호출 시 그 객체를 수정한다.
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    int totalSeconds = t1.hours * 3600 + t1.minutes * 60 + t1.seconds +
                       t2.hours * 3600 + t2.minutes * 60 + t2.seconds;

    t3.hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    t3.minutes = totalSeconds / 60;
    t3.seconds = totalSeconds % 60;
}

// 3. 두 시간을 더한 후 포인터를 통해 결과를 전달
//장점: 포인터를 사용해 객체를 수정하므로 '객체 복사 비용'이 없고, 참조와 유사하게 객체를 변경할 수 있습니다.
//단점: 포인터 사용 시 잘못된 포인터를 전달하거나 nullptr(null포인터상수)을 전달할 위험이 있을 수 있습니다. 코드가 더 복잡하고 안전성이 떨어질 수 있습니다.
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    int totalSeconds = t1.hours * 3600 + t1.minutes * 60 + t1.seconds +
                       t2.hours * 3600 + t2.minutes * 60 + t2.seconds;

    pt->hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    pt->minutes = totalSeconds / 60;
    pt->seconds = totalSeconds % 60;
}

int main() {
    MyTime time1(1, 30, 45);  // 1 hour, 30 minutes, 45 seconds
    MyTime time2(2, 45, 30);  // 2 hours, 45 minutes, 30 seconds

    // 1. addTime (MyTime t1, MyTime t2) 사용
    MyTime result1 = addTime(time1, time2);
    cout << "Result of addTime (by return): ";
    result1.print();

    // 2. addTime (MyTime t1, MyTime t2, MyTime& t3) 사용
    MyTime result2;
    addTime(time1, time2, result2);
    cout << "Result of addTime (by reference): ";
    result2.print();

    // 3. addTime (MyTime t1, MyTime t2, MyTime* pt) 사용
    MyTime result3;
    addTime(time1, time2, &result3);
    cout << "Result of addTime (by pointer): ";
    result3.print();

    return 0;
}