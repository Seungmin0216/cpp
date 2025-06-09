#include "MonsterWorld.h"
#include "Human.h"
#include "RankingBoard.h"
#include <time.h>

// 게임 시작 함수
void main()
{
    RankingBoard rank;
    try {
        rank.load("MonsterWorld.rnk");
    }
    catch (FileException e) {
        char str[80];
        string passwd, correct = "123456";
        cout << "랭킹 파일을 열 수 없습니다. 관리자 비밀번호를 입력하세요: ";
        for (int i = 0;; i++) {
            str[i] = getch();
            putchar('*');
            if (str[i] == '\r') {
                str[i] = '\0';
                passwd = str;
                cout << "\n";
                break;
            }
        }
        if (passwd != correct) {
            cout << "비밀번호가 틀렸습니다. 프로그램을 종료합니다.\n\n";
            exit(0);
        }
        cout << "관리자 권한이 확인되었습니다.\n";
        // 기본 랭킹 초기화 또는 기타 처리 가능
    }
    rank.print("[랭킹 보드: 초기 상태]");

    srand((unsigned int)time(NULL));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    game.add(new Zombie("좀비", "좀", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어", "뱀", rand() % w, rand() % h));
    game.add(new KGhost("유령", "유", rand() % w, rand() % h));
    game.add(new Jiangshi("강시", "강", rand() % w, rand() % h, true));
    game.add(new Jiangshi("강시", "강", rand() % w, rand() % h, false));

    Human* human = new Human("인간플레이어", "인", rand() % w, rand() % h);
    game.add(human);
    game.play(500, 10);
    printf("------게임 종료-------------------\n");

    rank.add(human->nItem, human->nItem / human->total);
    rank.print("[랭킹 보드: 게임 종료 후]");

    try {
        rank.store("MonsterWorld.rnk");
    }
    catch (FileException e) {
        char str[80];
        string passwd, correct = "123456";

        cout << "랭킹 저장 파일을 열 수 없습니다. 관리자 비밀번호를 입력하세요: ";
        for (int i = 0;; i++) {
            str[i] = getch();
            putchar('*');
            if (str[i] == '\r') {
                str[i] = '\0';
                passwd = str;
                cout << "\n";
                break;
            }
        }

        if (passwd != correct) {
            cout << "비밀번호가 틀렸습니다. 프로그램을 종료합니다.\n\n";
            exit(0);
        }

        cout << "관리자 권한이 확인되었습니다.\n";
        cout << "저장할 파일명을 입력하세요: ";
        string newFilename;
        cin >> newFilename;

        try {
            rank.store(newFilename);
            cout << "랭킹을 " << newFilename << " 에 성공적으로 저장했습니다.\n";
        }
        catch (FileException e2) {
            cout << "파일 저장에 실패했습니다. 프로그램을 종료합니다.\n";
            exit(0);
        }
    }
}