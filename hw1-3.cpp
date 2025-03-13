#include <iostream>

int main() {
    int n = 5; // 총 줄 수

    for (int i = 1; i <= n; i++) { // 5줄 출력
        // 공백 출력
        for (int j = 1; j <= n - i; j++) {
            std::cout << " ";
        }
        // 숫자 출력 (거꾸로)
        for (int j = i; j >= 1; j--) {
            std::cout << j;
        }
        std::cout << std::endl; // 줄바꿈
    }
    return 0;
}