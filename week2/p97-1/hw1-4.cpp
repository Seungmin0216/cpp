#include <iostream>

int main() {
    int n = 5; // 총 줄 수

    for (int i = 1; i <= n; i++) {
        // 공백 출력 (오른쪽 정렬)
        for (int j = 1; j <= n - i; j++) {
            std::cout << " ";
        }
        // 왼쪽 부분 (내림차순 출력)
        for (int j = i; j >= 1; j--) {
            std::cout << j;
        }
        // 오른쪽 부분 (오름차순 출력, 2부터 시작)
        for (int j = 2; j <= i; j++) {
            std::cout << j;
        }
        std::cout << std::endl; // 줄바꿈
    }

    return 0;
}