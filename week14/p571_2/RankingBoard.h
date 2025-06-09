#pragma once
#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;

#define NUM_MVP 5  // 최대 랭킹 저장 개수

// 플레이 정보 구조체
struct PlayInfo {
	string name;         // 플레이어 이름
	int nItem;           // 획득한 아이템 개수
	double itemPerMove;  // 이동당 평균 아이템 획득 수

	// 생성자: 기본값 설정
	PlayInfo(string na = "플레이어", int ni = 0, double ipm = 0.0)
		: name(na), nItem(ni), itemPerMove(ipm) {}
};

// 랭킹 보드 클래스
class RankingBoard {
	PlayInfo MVP[NUM_MVP];  // 상위 NUM_MVP 플레이어 정보 배열
	int nMVP = NUM_MVP;     // 랭킹 저장 개수

public:
	// 랭킹 파일 불러오기
	void load(string filename) {
		ifstream is;
		is.open(filename);
		if (!is)
			throw(FileException(filename, true));  // 파일 읽기 실패 시 예외 발생

		for (int i = 0; i < nMVP; i++)
			is >> MVP[i].nItem >> MVP[i].name >> MVP[i].itemPerMove;

		is.close();
	}

	// 랭킹 파일 저장하기
	void store(string filename) {
		ofstream os;
		os.open(filename);
		if (!os)
			throw(FileException(filename, false));  // 파일 쓰기 실패 시 예외 발생

		for (int i = 0; i < nMVP; i++)
			os << MVP[i].nItem << " " << MVP[i].name << " "
			   << MVP[i].itemPerMove << "\n";

		os.close();
	}

	// 랭킹 출력하기
	void print(string title = "현재 랭킹") {
		cout << endl << title << endl;
		for (int i = 0; i < nMVP; i++)
			cout << "[" << i + 1 << "위] " << MVP[i].name << "\t"
			     << MVP[i].nItem << "개, 이동당 평균: "
			     << MVP[i].itemPerMove << "\n";

		cout << "계속하려면 아무 키나 누르세요.";
		getchar();
		cout << endl;
	}

	// 새로운 점수를 랭킹에 추가
	// 반환: 추가된 랭킹 위치 (1~NUM_MVP), 추가되지 않으면 0
	int add(int nItem, double ipm) {
		// 가장 낮은 순위보다 낮으면 추가하지 않음
		if (nItem <= MVP[nMVP - 1].nItem) return 0;

		int pos = nMVP - 1;

		// 내림차순 정렬 위치 탐색 및 자리 이동
		for (; pos > 0; pos--) {
			if (nItem <= MVP[pos - 1].nItem) break;
			MVP[pos] = MVP[pos - 1];  // 한 칸씩 뒤로 밀기
		}

		// 새로운 데이터 삽입
		MVP[pos].nItem = nItem;
		MVP[pos].itemPerMove = ipm;

		cout << "\n[" << pos + 1 << "위] 이름을 입력하세요: ";
		cin >> MVP[pos].name;

		return pos + 1;  // 등수 반환
	}
};
