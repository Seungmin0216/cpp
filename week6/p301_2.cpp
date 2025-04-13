#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define MAXWORDS 100  // 저장할 수 있는 최대 단어 수

// 1) WordPair 구조체 정의
struct WordPair {
    string eng;
    string kor;
};

// 2) MyDic 클래스 정의 (배열 버전)
class MyDic {
    WordPair words[MAXWORDS];
    int nWords = 0;  // 현재 저장된 단어 수

public:
    // 단어 추가
    inline void add(const WordPair& wp) {
        if (nWords < MAXWORDS) {
            words[nWords++] = wp;
        } else {
            cerr << "단어장이 가득 찼습니다!" << endl;
        }
    }

    // 단어장 파일에서 단어 읽기
    inline void load(const string& filename) {
        ifstream fin(filename);
        if (!fin) {
            cerr << "파일을 열 수 없습니다: " << filename << endl;
            return;
        }

        nWords = 0;  // 기존 데이터 초기화
        string line;
        while (getline(fin, line) && nWords < MAXWORDS) {
            stringstream ss(line);
            string eng, kor;
            if (getline(ss, eng, ',') && getline(ss, kor)) {
                words[nWords].eng = eng;
                words[nWords].kor = kor;
                nWords++;
            }
        }

        fin.close();
    }

    // 단어장을 파일에 저장
    inline void store(const string& filename) {
        ofstream fout(filename);
        if (!fout) {
            cerr << "파일을 저장할 수 없습니다: " << filename << endl;
            return;
        }

        for (int i = 0; i < nWords; ++i) {
            fout << words[i].eng << "," << words[i].kor << endl;
        }

        fout.close();
    }

    // 단어장 출력
    inline void print() {
        cout << "====== 나의 단어장 ======" << endl;
        for (int i = 0; i < nWords; ++i) {
            cout << i << ": " << words[i].eng << " - " << words[i].kor << endl;
        }
    }

    // 특정 단어 반환
    inline string getEng(int id) {
        if (id >= 0 && id < nWords)
            return words[id].eng;
        else
            return "";
    }

    inline string getKor(int id) {
        if (id >= 0 && id < nWords)
            return words[id].kor;
        else
            return "";
    }
};

// 3) main 함수
int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");  // 한국어 로케일로 설정
    MyDic dic;

    // 단어 추가
    dic.add({ "apple", "사과" });
    dic.add({ "banana", "바나나" });
    dic.add({ "computer", "컴퓨터" });

    // 단어장 출력
    dic.print();

    // 파일에 저장
    dic.store("mydic.txt");

    // 새로운 객체로 다시 읽기
    MyDic dic2;
    dic2.load("mydic.txt");
    dic2.print();

    // 단일 단어 확인
    cout << "첫 번째 단어 영어: " << dic2.getEng(0) << endl;
    cout << "첫 번째 단어 한글: " << dic2.getKor(0) << endl;

    return 0;
}