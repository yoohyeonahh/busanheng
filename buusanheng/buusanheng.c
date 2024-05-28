/*
[ �����Ȳ ]
2-1. ����(O)
2-2. �λ���(1)���� ����
    - �Ķ����(O)
    - �Է°� ó��(O)
    - ������ ü�� �߰�(O)
    - �ù�, ������ ��׷� �߰�()
    - sleep() ����
    - 2Phases()
2-3. <�̵�>()
2-4. <�ൿ>()

3-1. ��������()
3-2. ��������2:����()
3-3. ��������3:�ù�'��'()
3-4. ��������4:����()
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5
#define PROB_MIN 10 // Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0 // ��׷� ����
#define AGGRO_MAX 5

// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
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
    printf("| �������� �����ؼ� |\n");
    Sleep(800);
    printf("|    ����κ���     |\n");
    Sleep(800);
    printf("|   �ù��� ���Ѷ�   |\n");
    Sleep(800);
    system("cls");
}

void printTrain(int len, int C, int Z, int M) { // ���� ���� ���
    for (int i = 0; i < len; i++) {
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < len; i++) {
        if (i == 0 || i == len - 1) printf("#");
        else if (i == M) printf("M");           
        else if (i == Z) printf("Z"); 
        else if (i == C) printf("C");
        else printf(" ");  
    }
    printf("\n");

    for (int i = 0; i < len; i++) {
        printf("#");
    }
    printf("\n");
}

void printStatus(int cPos, int C, int zPos, int Z, int turn) { // �ù�, ���� ���� ���
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
            printf("zombie : stay %d\n\n", Z); // Ȧ�� ���� ��� ��ġ�� ���
        }
        else {
            printf("zombie : stay %d (cannot move)\n\n", Z); // ¦�� ���� ��� ��ġ�� cannot move ���
        }
    }
}

int citizenMove(int C, int p, int random) { // �ù��̵�
    if (random >= p) {
        if (C > 0) {
            C = C - 1;
        }
    }
    return C;
}

int zombieMove(int Z, int p, int random, int turn) { // �����̵�
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
        printf("Ż�� ����!\n");
        printf("�ù��� ����κ��� �����߽��ϴ�.\n");
    }
    if (C + 1 == Z) {
        printf("���� ����!\n");
        printf("�ù��� ���񿡰� ���Ƚ��ϴ�.\n");
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    int len = 0;
    int p = 0;
    int stm = 0;
    int turn = 1;

    intro();

    while (1) {
        printf("train length(15~50) >> ");
        scanf_s("%d", &len);

        if (LEN_MIN <= len && LEN_MAX >= len) {
            break;
        } 
        else if (LEN_MIN > len || LEN_MAX < len) {
            continue;
        }
    }
   
    while (1) {
        printf("madongseok stamina(0~5) >> ");
        scanf_s("%d", &stm);

        if (STM_MIN <= stm && STM_MAX >= stm) {
            break;
        }
        else if (STM_MIN > stm || STM_MAX < stm) {
            continue;
        }
    }

    while (1) {
        printf("percentile probability 'p' (10~90) >> ");
        scanf_s("%d", &p);

        if (PROB_MIN <= p && PROB_MAX >= p) {
            break;
        }
        else  if (PROB_MIN > p || PROB_MAX < p) {
            continue;
        }
    }

    // �ù�, ����, ������ �ʱ� ��ġ ����
    int C = len - 6;
    int Z = len - 3;
    int M = len - 2;

    printTrain(len, C, Z, M);

    while (1) {
        int cPos = C;
        int zPos = Z;
        int random = rand() % 100;

        C = citizenMove(C, p, random); //�ù��̵�
        Z = zombieMove(Z, p, random, turn);

        printTrain(len, C, Z, M);
        printStatus(cPos, C, zPos, Z, turn);
        Sleep(4000);

        if (C == 1) { // �ù��� ���� ���� ĭ�� ������ ��� ����
            break;
        }
        if (C + 1 == Z) { // �ù� �� ĭ�� ���� ������ ��� ����
            break;
        }
        turn++;
    }
    outro(C, Z);

    return 0;
}