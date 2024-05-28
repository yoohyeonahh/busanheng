#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로 범위
#define AGGRO_MAX 5

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

void intro(void) {
    printf("                (@@@@@@)    (@@@@@@)\n");
    printf("            (@@@)  (@@@@)           (@@)\n");
    printf("         (@@)              (@@@)\n");
    printf("        .-.\n");
    printf("        ] [. - ._    .---- - .\n");
    printf("      .'   '''   '''' '''' | .--`\n");
    printf("     (:--: --: --: --: --: --: --: -| [___    .------------------------.\n");
    printf(" | C & amp; O: : : : : : [_9_] | '=' | .----------------------.|\n");
    printf("     /|.___________________________ | ___ | '--.___.--.___.--.___.-'|\n");
    printf("    / ||_.--.______.--.______.--._ | -- - \'--\-.-/==\-.-/==\-.-/-' / --\n");
    printf(" / __; ^= (== )======(== )======(== ) = ^ ~^ ^^^^^^(-) ^ ^^^(-) ^ ^^^(-) ^ ^^aac\n");
    printf(" ~~~^ ~~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~^ ~~~\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("| 마동석에 빙의해서 |\n");
    Sleep(800);
    printf("|    좀비로부터     |\n");
    Sleep(800);
    printf("|   시민을 지켜라   |\n");
    Sleep(800);
    system("cls");
}

void printTrain(int len, int C, int Z, int M) { // 기차 상태 출력
    for (int i = 0; i < len; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < len; i++) {
        if (i == 0 || i == len - 1) {
            printf("#");
        }
        else if (i == M) {
            printf("M");
        }
        else if (i == Z) {
            printf("Z");
        }
        else if (i == C) {
            printf("C");
        }
        else {
            printf(" ");
        }
    }
    printf("\n");

    for (int i = 0; i < len; i++) {
        printf("#");
    }
    printf("\n");
}

void printStatus(int cPos, int C, int zPos, int Z, int turn) { // 시민, 좀비 상태 출력
    if (cPos > C) {
        printf("\ncitizen : %d -> %d\n", cPos, C);
    }
    else {
        printf("\ncitizen : stay %d\n", C);
    }

    if (zPos > Z) {
        printf("zombie : %d -> %d\n\n", zPos, Z);
    }
    else {
        if (turn % 2 == 1) {
            printf("zombie : stay %d\n\n", Z); // 홀수 턴일 경우 위치만 출력
        }
        else {
            printf("zombie : stay %d (cannot move)\n\n", Z); // 짝수 턴일 경우 위치와 cannot move 출력
        }
    }
}

int citizenMove(int C, int p, int random) { // 시민이동
    if (random >= p) {
        if (C > 0) {
            C = C - 1;
        }
    }
    return C;
}

int zombieMove(int Z, int p, int random, int turn) { // 좀비이동
    if (turn % 2 == 1) {
        if (random < p) {
            if (Z > 0) {
                Z = Z - 1;
            }
        }
    }
    return Z;
}

void outro(int C, int Z) {
    if (C == 1) {
        printf("탈출 성공!\n");
        printf("시민이 좀비로부터 대피했습니다.\n");
    }
    if (C + 1 == Z) {
        printf("게임 오버!\n");
        printf("시민이 좀비에게 물렸습니다.\n");
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    int len = 0;
    int p = 0;
    int turn = 1;

    intro();

    printf("train length(15~50) >> ");
    scanf_s("%d", &len);

    if (LEN_MIN > len || LEN_MAX < len) {
        printf("잘못된 입력입니다. \n");
        return -1;
    }

    printf("percentile probability 'p' (10~90) >> ");
    scanf_s("%d", &p);

    if (PROB_MIN > p || PROB_MAX < p) {
        printf("잘못된 입력입니다. \n");
        return -1;
    }

    // 시민, 좀비, 마동석 초기 위치 정의
    int C = len - 6;
    int Z = len - 3;
    int M = len - 2;

    printTrain(len, C, Z, M);

    while (1) {
        int cPos = C;
        int zPos = Z;
        int random = rand() % 100;

        C = citizenMove(C, p, random); //시민이동
        Z = zombieMove(Z, p, random, turn);

        printTrain(len, C, Z, M);
        printStatus(cPos, C, zPos, Z, turn);
        Sleep(4000);

        if (C == 1) { // 시민이 가장 왼쪽 칸에 도착할 경우 성공
            break;
        }
        if (C + 1 == Z) { // 시민 옆 칸에 좀비가 도착할 경우 실패
            break;
        }
        turn++;
    }
    outro(C, Z);

    return 0;
}