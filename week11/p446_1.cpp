#include <iostream>

// Point 클래스 선언
class Point {
protected:
    int x, y;

public:
    // 기본 생성자: 초기화 리스트를 이용해 x, y를 0으로 초기화
    Point() : x(0), y(0) {}

    // 사용자 입력 함수
    void input() {
        std::cout << "x 좌표를 입력하세요: ";
        std::cin >> x;
        std::cout << "y 좌표를 입력하세요: ";
        std::cin >> y;
    }

    // draw 함수에 virtual 키워드를 붙여서 '재정의' 가능하게 설정
    virtual void draw() {
        std::cout << x << "," << y << "에 점을 그려라.\n";
    }
};

// Point를 상속한 Rectangle 클래스
class Rectangle : public Point {
private:
    int width, height;

public:
    // 기본 생성자: 초기화 리스트로 width, height를 0으로 초기화
    Rectangle() : width(0), height(0) {}

    // 사용자 입력 함수 (부모 클래스의 input도 호출)
    void input() {
        Point::input();  // x, y 입력 받기
        std::cout << "가로 길이를 입력하세요: ";
        std::cin >> width;
        std::cout << "세로 길이를 입력하세요: ";
        std::cin >> height;
    }

    // 부모의 draw()를 재정의 (오버라이딩)
    void draw() override {
        std::cout << x << "," << y
                  << "에 가로 " << width
                  << " 세로 " << height
                  << "인 사각형을 그려라.\n";
    }
};

// 메인 함수
int main() {
    // Point 객체 생성 및 사용
    Point p;
    p.input();
    p.draw();  // Point::draw() 호출

    std::cout << "\n";

    // Rectangle 객체 생성 및 사용
    Rectangle r;
    r.input();
    r.draw();  // Rectangle::draw() 호출 (Point의 draw를 재정의)

    return 0;
}
// protected 키워드를 private로 바꾸면 자식클래스에서 
//접근이 불가해서 오류가 발생한다.