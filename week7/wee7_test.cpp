//종합 비교된 5가지 함수 구현하고 검증 
//a = 1+2i, b = 3+4i, c = ?
#include <iostream>
using namespace std;

// 1. 일반 함수 (void, 참조 전달)
// 두 개의 복소수를 더한 결과를 참조로 전달된 result 객체에 저장함.
// 반환값 없이 result 객체의 값을 변경함.
void add_void(const class Complex& a, const class Complex& b, class Complex& result);

// 2. 일반 함수 (return, 값 전달)
// 두 개의 복소수를 더한 결과를 새로운 Complex 객체로 반환함.
// 반환된 결과는 값 형태로 main 함수에서 받음.
class Complex add_return(const class Complex& a, const class Complex& b);

// 복소수 클래스 정의
class Complex {
public:
    double real;  // 실수부
    double imag;  // 허수부

    // 생성자: 실수부와 허수부 초기화
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 복소수 출력 함수
    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }

    // 3. 멤버 함수 (void, 참조 전달)
    // 자기 자신(this)과 other 객체를 더해 result에 저장함 (참조 전달).
    // 반환 없이 결과만 외부 객체에 저장.
    void add_void(const Complex& other, Complex& result) const {
        result.real = real + other.real;
        result.imag = imag + other.imag;
    }

    // 4. 멤버 함수 (return, 값 전달)
    // 자기 자신(this)과 other 객체를 더한 결과를 새로운 Complex 객체로 반환.
    // 값을 리턴해서 더 간결하게 사용할 수 있음.
    Complex add_return(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // 5. 연산자 오버로딩
    // '+' 연산자를 오버로딩하여 두 복소수를 더할 수 있게 함.
    // 사용자가 자연스럽게 a + b 형태로 사용할 수 있음.
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
};

// 1. 일반 함수 정의 (void, 참조 전달)
void add_void(const Complex& a, const Complex& b, Complex& result) {
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
}

// 2. 일반 함수 정의 (return, 값 전달)
Complex add_return(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

int main() {
    // a = 1 + 2i, b = 3 + 4i 정의
    Complex a(1, 2);
    Complex b(3, 4);
    Complex c; // 결과를 저장할 객체

    // 1. 일반 함수 (void, 참조 전달) 사용 예
    // a와 b를 더한 결과를 c에 저장 (함수가 c를 참조로 수정)
    add_void(a, b, c);
    cout << "1. 일반 함수 (void, 참조 전달): ";
    c.print();

    // 2. 일반 함수 (return, 값 전달) 사용 예
    // 함수가 반환한 Complex 객체를 c에 대입
    c = add_return(a, b);
    cout << "2. 일반 함수 (return, 값 전달): ";
    c.print();

    // 3. 멤버 함수 (void, 참조 전달) 사용 예
    // a 객체가 b와 더한 결과를 c에 저장 (a가 this 포인터 역할)
    a.add_void(b, c);
    cout << "3. 멤버 함수 (void, 참조 전달): ";
    c.print();

    // 4. 멤버 함수 (return, 값 전달) 사용 예
    // a 객체가 b와 더한 결과를 반환 → c에 대입
    c = a.add_return(b);
    cout << "4. 멤버 함수 (return, 값 전달): ";
    c.print();

    // 5. 연산자 오버로딩 사용 예
    // '+' 연산자를 이용해 자연스럽게 복소수 덧셈 수행
    c = a + b;
    cout << "5. 연산자 오버로딩: ";
    c.print();

    return 0;
}
