#include <iostream>
#include <cstring>  

using namespace std;

class Sample {
    char* name; // 객체의 이름을 저장할 동적 문자열
    static int count; // Sample 객체의 전체 개수를 세는 정적 변수

public:
    // 기본 생성자
    Sample() {
        // name을 nullptr로 초기화
        // 이 기본 생성자는 문자열을 전달받지 않기 때문에, name을 nullptr로 초기화합니다.
        // 기본적으로 name을 nullptr로 두는 이유는, 동적 할당을 하지 않고도 객체가 유효한 상태를 만들기 위함입니다.
        name = nullptr;

        // 객체 생성 시 count 증가
        // 객체가 생성될 때마다 count를 증가시켜, 현재 존재하는 Sample 객체의 개수를 추적합니다.
        count++;
    }

    // 문자열 name을 받아서 초기화하는 생성자
    Sample(const char* name) {
        // 전달된 name 문자열 길이에 맞는 동적 메모리 할당
        // new 키워드로 필요한 메모리만큼 할당하여 name을 동적으로 저장합니다.
        // 이때, 문자열의 끝을 나타내는 null 문자('\0')도 포함시켜야 하므로 +1을 합니다.
        this->name = new char[strlen(name) + 1]; // +1 for null terminator

        // 전달된 문자열을 동적 메모리 영역에 복사
        // strcpy를 이용해 전달받은 name을 this->name에 복사합니다.
        // 이때 deep copy를 보장하기 위해서 새로운 메모리에 복사해야 합니다.
        strcpy(this->name, name);

        // 객체 생성 시 count 증가
        // 이 생성자도 객체를 생성할 때마다 count를 증가시킵니다.
        count++;
    }

    // 복사 생성자: 깊은 복사를 수행합니다.
    Sample(const Sample& other) {
        // 만약 다른 객체의 name이 유효하다면,
        // 다른 객체의 name이 nullptr이 아니면 메모리를 새로 할당하고 복사합니다.
        if (other.name) {
            // 다른 객체의 name 길이에 맞는 메모리 동적 할당
            // 다른 객체의 name을 복사하여 현재 객체의 name으로 할당합니다.
            this->name = new char[strlen(other.name) + 1]; // +1 for null terminator
            strcpy(this->name, other.name); // deep copy
        } else {
            // 다른 객체의 name이 nullptr이면 현재 객체의 name도 nullptr로 초기화
            this->name = nullptr;
        }

        // 객체가 복사되었으므로 count를 증가시킵니다.
        count++;
    }

    // 소멸자: 동적 할당된 메모리를 해제
    ~Sample() {
        // 동적 메모리 해제
        // 객체가 소멸될 때, 동적 할당한 메모리(name)를 해제해야 합니다.
        // delete[]를 사용하여 할당된 메모리를 해제합니다.
        delete[] name;
        name = nullptr; // 안전하게 nullptr로 초기화

        // 객체 소멸 시 count를 감소시켜, 현재 존재하는 Sample 객체의 개수를 추적합니다.
        count--;
    }

    // 현재 생성된 Sample 객체 수 출력 (정적 함수)
    static void printCount() {
        // 정적 변수 count의 값을 출력
        // 정적 변수는 객체가 아닌 클래스 자체에서 관리되므로, 클래스 이름으로 직접 접근 가능합니다.
        cout << "현재 Sample 객체 개수: " << count << endl;
    }

    // 객체의 이름 출력 (디버깅용)
    void printName() const {
        // name이 유효한 경우 출력
        // 만약 name이 nullptr이라면 "이름 없음"을 출력합니다.
        if (name)
            cout << "이름: " << name << endl;
        else
            cout << "이름 없음" << endl;
    }
};

// 정적 멤버 변수 정의 (클래스 외부에서 초기화)
// count는 클래스 수준에서 공유되므로, 외부에서 초기화해줘야 합니다.
int Sample::count = 0;

// 메인 함수: 테스트용
int main() {
    // 객체가 없으므로, count는 0이어야 합니다.
    Sample::printCount(); // 현재 Sample 객체 개수: 0

    // Sample 객체 a 생성
    Sample a("sample");
    a.printName(); // a 객체의 이름 출력: "sample"
    Sample::printCount(); // 현재 Sample 객체 개수: 1

    // Sample 객체 b 생성 (복사 생성자 호출)
    Sample b(a); // a 객체를 복사하여 b 객체를 생성
    b.printName(); // b 객체의 이름 출력: "sample"
    Sample::printCount(); // 현재 Sample 객체 개수: 2

    return 0; // main 함수 종료 시 a와 b 객체는 소멸되고 count가 감소
}