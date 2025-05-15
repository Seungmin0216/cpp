#include <iostream>

class Point {
protected:
    int x, y;

public:
    // 기본 생성자 추가 (사용자 입력을 위해 필요함)
    Point() : x(0), y(0) {}

    // 사용자로부터 좌표를 입력받는 함수
    void input() {
        std::cout << "x 좌표를 입력하세요: ";
        std::cin >> x;
        std::cout << "y 좌표를 입력하세요: ";
        std::cin >> y;
    }

    void draw() {
        std::cout << x << "," << y << "에 점을 그려라.\n";
    }
};

// Point를 상속받은 Rectangle 클래스
class Rectangle : public Point {
private:
    int width, height;

public:
    Rectangle() : width(0), height(0) {}

    // 사용자로부터 모든 정보를 입력받는 함수
    void input() {
        // 부모 클래스의 좌표 입력
        Point::input();
        std::cout << "가로 길이를 입력하세요: ";
        std::cin >> width;
        std::cout << "세로 길이를 입력하세요: ";
        std::cin >> height;
    }

    void draw() {
        std::cout << x << "," << y
                  << "에 가로 " << width
                  << " 세로 " << height
                  << "인 사각형을 그려라.\n";
    }
};

int main() {
    // Point 예시
    Point p;
    p.input();   // 사용자로부터 x, y 입력 받음
    p.draw();    // 입력된 좌표에 점을 그림

    std::cout << "\n";

    // Rectangle 예시
    Rectangle r;
    r.input();   // 사용자로부터 x, y, width, height 입력 받음
    r.draw();    // 입력된 정보로 사각형을 그림

    return 0;
}
// protected 키워드를 private로 바꾸면 자식클래스에서 
//접근이 불가해서 오류가 발생한다.