#include <iostream>

double calculatePi(int n) {
    double pi = 0.0;

    for (int i = 0; i < n; i++) {
        double term = 1.0 / (2 * i + 1); // 분모 값 계산
        if (i % 2 == 0) {
            pi += term; // 짝수 번째는 더하기
        } else {
            pi -= term; // 홀수 번째는 빼기
        }
    }
    
    return 4 * pi; // 최종적으로 4를 곱해서 반환
}

int main() {
    int n;
    std::cout << "정수 n을 입력하세요: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "n은 양의 정수여야 합니다." << std::endl;
        return 1;
    }

    double piApproximation = calculatePi(n);
    std::cout << "π의 근사값: " << piApproximation << std::endl;

    return 0;
}