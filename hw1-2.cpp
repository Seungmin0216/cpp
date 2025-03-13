#include <iostream>

int main() {
    for (int i = 1; i <= 5; i++) { // 5줄 출력
        for (int j = 5; j >= i; j--) { // 5부터 i까지 출력
            std::cout << j;
        }
        std::cout << std::endl; // 줄바꿈
    }
    return 0;
}