#include <iostream>
using namespace std;

class TimeHMS {
private:
    int hour, min, sec;

    // 시간, 분, 초를 정규화하는 함수
    // 초와 분이 60을 넘지 않도록 조정하며, 음수 시간도 0으로 보정
    void normalize() {
        int total = hour * 3600 + min * 60 + sec;
        if (total < 0) total = 0; // 음수 시간은 0으로 처리
        hour = total / 3600;
        total %= 3600;
        min = total / 60;
        sec = total % 60;
    }

public:
    // 생성자: 시, 분, 초를 받아 초기화하며 정규화 수행
    TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {
        normalize();
    }

    // (1) 시간 덧셈을 위한 + 연산자 중복
    TimeHMS operator+(const TimeHMS& t) const {
        return TimeHMS(hour + t.hour, min + t.min, sec + t.sec);
    }

    // (2) 시간 차이를 위한 - 연산자 중복
    TimeHMS operator-(const TimeHMS& t) const {
        int total1 = hour * 3600 + min * 60 + sec;
        int total2 = t.hour * 3600 + t.min * 60 + t.sec;
        int diff = total1 - total2;
        if (diff < 0) diff = 0;
        return TimeHMS(0, 0, diff);
    }

    // (3) 두 시간이 같은지 비교하는 == 연산자 중복
    bool operator==(const TimeHMS& t) const {
        return hour == t.hour && min == t.min && sec == t.sec;
    }

    // (4) 후위 증가 연산자 t++
    TimeHMS operator++(int) {
        TimeHMS temp = *this;
        sec++;
        normalize();
        return temp;
    }

    // (4) 전위 증가 연산자 ++t
    TimeHMS& operator++() {
        sec++;
        normalize();
        return *this;
    }

    // (5) 후위 감소 연산자 t--
    TimeHMS operator--(int) {
        TimeHMS temp = *this;
        sec--;
        normalize();
        return temp;
    }

    // (5) 전위 감소 연산자 --t
    TimeHMS& operator--() {
        sec--;
        normalize();
        return *this;
    }

    // (6) 배열처럼 접근하는 [] 연산자 중복 (0:시, 1:분, 2:초)
    int operator[](int index) const {
        switch (index) {
            case 0: return hour;
            case 1: return min;
            case 2: return sec;
            default: return -1;
        }
    }

    // (7) int 형 변환 연산자 중복 - 총 시간을 초로 반환
    operator int() const {
        return hour * 3600 + min * 60 + sec;
    }

    // (8) double 형 변환 연산자 중복 - 총 시간을 시간 단위로 반환
    operator double() const {
        return hour + min / 60.0 + sec / 3600.0;
    }

    // (9) * 연산자 중복 - 두 배 시간 반환 (단, 분/초는 0~59 사이로 보정)
    TimeHMS operator*(int n) const {
        int total = (hour * 3600 + min * 60 + sec) * n;
        return TimeHMS(0, 0, total);
    }

    // (10) 입력 연산자 >> 중복
    friend istream& operator>>(istream& in, TimeHMS& t) {
        in >> t.hour >> t.min >> t.sec;
        t.normalize();
        return in;
    }

    // (10) 출력 연산자 << 중복
    friend ostream& operator<<(ostream& out, const TimeHMS& t) {
        out << t.hour << "시간 " << t.min << "분 " << t.sec << "초";
        return out;
    }
};

// (11) 모든 연산자들이 제대로 작동하는지 테스트하는 main 함수
int main() {
    TimeHMS t1(1, 30, 20), t2(4, 35, 46), t3;

    // (1) 덧셈 연산
    t3 = t1 + t2;
    cout << "t1 + t2 = " << t3 << endl;

    // (2) 뺄셈 연산
    t3 = t2 - t1;
    cout << "t2 - t1 = " << t3 << endl;

    // (3) 비교 연산
    cout << "t1 == t2? " << (t1 == t2 ? "같다" : "다르다") << endl;

    // (4) 증가 연산
    cout << "t1++ = " << t1++ << endl;
    cout << "++t1 = " << ++t1 << endl;

    // (5) 감소 연산
    cout << "t2-- = " << t2-- << endl;
    cout << "--t2 = " << --t2 << endl;

    // (6) [] 연산자 테스트
    cout << "t1[0](시): " << t1[0] << ", t1[1](분): " << t1[1] << ", t1[2](초): " << t1[2] << endl;

    // (7) int 형 변환
    int totalSec = (int)t1;
    cout << "t1의 총 초 단위: " << totalSec << "초" << endl;

    // (8) double 형 변환
    double totalHour = (double)t1;
    cout << "t1의 총 시간 단위: " << totalHour << "시간" << endl;

    // (9) * 연산자 중복
    TimeHMS t4 = t1 * 2;
    cout << "t1의 두 배 시간: " << t4 << endl;

    // (10) 사용자 입력 테스트
    TimeHMS inputTime;
    cout << "시간을 입력하세요 (시 분 초): ";
    cin >> inputTime;
    cout << "입력한 시간: " << inputTime << endl;

    return 0;
}
