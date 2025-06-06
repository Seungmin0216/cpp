// reverse.cpp
#include <iostream>   // 입력과 출력을 처리
#include <string>     // 문자열을 다루기 위한 클래스와 함수들 제공
#include <algorithm>  // std::reverse 와 같은 함수 제공
#include "reverse.h"  // 헤더 파일 포함

int reverse(int num) {
    // 숫자를 문자열로 변환
    std::string strNum = std::to_string(num);
    
    // 문자열을 뒤집기
    std::reverse(strNum.begin(), strNum.end());
    
    // 뒤집은 문자열을 다시 정수로 변환하여 반환
    return std::stoi(strNum);
}

int main() {
    int number;
    std::cout << "정수를 입력하세요: ";
    std::cin >> number;
    
    int reversed = reverse(number);
    std::cout << "숫자의 역순: " << reversed << std::endl;
    
    return 0;
}