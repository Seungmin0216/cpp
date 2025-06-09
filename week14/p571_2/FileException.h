#pragma once
#include <string>

using namespace std;

// 파일 예외를 나타내는 구조체
struct FileException {
    string filename;   // 예외가 발생한 파일 이름
    bool bRead;        // true이면 읽기 중 예외, false이면 쓰기 중 예외

    // 생성자: 파일 이름과 읽기 여부를 초기화
    FileException(string name, bool b) : filename(name), bRead(b) {}
};
