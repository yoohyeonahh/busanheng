/*
[ �����Ȳ ]
2-1. ����(O)
2-2. �λ���(1)���� ����
    - sleep() ����
2-3. <�̵�>()
        - ������ �ٵ��()
2-4. <�ൿ>()
    - ������ ���� ����()
    - ������ �ൿ ��Ģ()

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
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int CITIZEN_AGGRO = 1;
int DONGSEOK_AGGRO = 1;
int DONGSEOK_ACTION = 0;
int DONGSEOK_STAMINA = 0;

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

void printCitizenStatus(int cPos, int C, int aggro) { // �ù� ���� ���
    if (cPos > C) {
        if (aggro + 1 > AGGRO_MAX) {
            aggro = AGGRO_MAX;
        }
        else {
            aggro = CITIZEN_AGGRO + 1;
        }
        printf("\ncitizen : %d -> %d (aggro : %d -> %d)\n", cPos, C, CITIZEN_AGGRO, aggro);
        if (CITIZEN_AGGRO + 1 > AGGRO_MAX) {
            CITIZEN_AGGRO = AGGRO_MAX;
        }
        else {
            CITIZEN_AGGRO++;
        }
    }
    else {
        if (aggro - 1 < AGGRO_MIN) {
            aggro = AGGRO_MIN;
        }
        else {
            aggro = CITIZEN_AGGRO - 1;
        }
        printf("\ncitizen : stay %d (aggro : %d -> %d)\n", C, CITIZEN_AGGRO, aggro);
        if (CITIZEN_AGGRO - 1 < AGGRO_MIN) {
            CITIZEN_AGGRO = AGGRO_MIN;
        }
        else {
            CITIZEN_AGGRO--;
        }
    }
}

void printZombieStatus(int zPos, int Z, int turn) { // ���� ���� ���
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

void printDongseokStatus(int mPos, int M, int aggro) { // ������ ���� ���
    if (mPos > M) {
        if (aggro + 1 > AGGRO_MAX) {
            aggro = AGGRO_MAX;
        }
        else {
            aggro = DONGSEOK_AGGRO + 1;
        }
        printf("\nmadongseok : %d -> %d (aggro : %d -> %d, stamina : %d)\n", mPos, M, DONGSEOK_AGGRO, aggro, DONGSEOK_STAMINA);
        if (DONGSEOK_AGGRO + 1 > AGGRO_MAX) {
            DONGSEOK_AGGRO = AGGRO_MAX;
        }
        else {
            DONGSEOK_AGGRO++;
        }
    }
    else {
        if (aggro - 1 < AGGRO_MIN) {
            aggro = AGGRO_MIN;
        }
        else {
            aggro = DONGSEOK_AGGRO - 1;
        }
        printf("\nmadongseok : stay %d (aggro : %d -> %d, stamina : %d)\n", M, DONGSEOK_AGGRO, aggro, DONGSEOK_STAMINA);
        if (DONGSEOK_AGGRO - 1 < AGGRO_MIN) {
            DONGSEOK_AGGRO = AGGRO_MIN;
        }
        else {
            DONGSEOK_AGGRO--;
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

int zombieMove(int Z, int C, int M, int turn) { // �����̵�
    if (turn % 2 == 1) {
        if (DONGSEOK_ACTION != ACTION_PULL) {
            if (CITIZEN_AGGRO >= DONGSEOK_AGGRO) {
                if (C + 1 != Z) {
                    Z = Z - 1;
                }
            }
            else {
                if (M - 1 != Z) {
                    Z = Z + 1;
                }
            }
        }
    }
    return Z;
}

int dongseokMove(int M, int Z, int ans) { // �������̵�
    while (1) {
        if (M - 1 != Z) {
            printf("madongseok move(0:stay, 1:left) >> ");
            scanf_s("%d", &ans);
            if (0 == ans || ans == 1) {
                break;
            } 
            else {
                continue;
            }
        }
        else {
            printf("madongseok move(0:stay) >> ");
            scanf_s("%d", &ans);
            if (ans == 0) {
                break;
            }
            else {
                continue;
            }
        }
    }

    if (ans == 1) {
        if (M > 0) {
            M = M - 1;
        }
    }
    return M;
}

void printAction(int C, int Z, int M) { // ����, �ù� �ൿ ���
    printf("citizen does nothing.\n");
    if (C + 1 != Z && M-1!=Z) {
        printf("zombie attacked nobody.\n");
    }
    else if (C + 1 == Z && M - 1 != Z) {
        printf("GAME OVER! citizen dead...\n");
    }
    else if (C + 1 != Z && M - 1 == Z) {
        printf("Zombie attacked madongseok (aggro : %d vs %d, madongseok stamina : %d -> %d)\n",
            CITIZEN_AGGRO, DONGSEOK_AGGRO, DONGSEOK_STAMINA, DONGSEOK_STAMINA -1);
        DONGSEOK_STAMINA--;
    }
}

void printdongseokAction(int aAns, int M, int random, int p, int aggro) { // ������ �ൿ ��� 
    while (1) {
        printf("madongseok action(0. rest, 1. provoke, 2. pull) >> ");
        scanf_s("%d", &aAns);

        if (0 <= aAns && 2 >= aAns) {
            break;
        }
        else if (0 > aAns || 2 < aAns) {
            continue;
        }
    }
    switch (aAns) {
        case ACTION_REST:
            if (DONGSEOK_AGGRO - 1 != AGGRO_MIN) {
                aggro = DONGSEOK_AGGRO;
                DONGSEOK_AGGRO = DONGSEOK_AGGRO - 1;
            }
            else {
                aggro = DONGSEOK_AGGRO;
            }
            printf("madongseok rest...\n");
            printf("madongseok : %d (aggro : %d -> %d, stamina : %d -> %d)\n\n",
                M, aggro, DONGSEOK_AGGRO, DONGSEOK_STAMINA, DONGSEOK_STAMINA + 1);
            DONGSEOK_STAMINA++;
            DONGSEOK_ACTION = ACTION_REST;
            break;
        case ACTION_PROVOKE:
            aggro = DONGSEOK_AGGRO;
            DONGSEOK_AGGRO = AGGRO_MAX;
            printf("madongseok provoked zombie...\n");
            printf("madongseok : %d (aggro : %d -> %d, stamina : %d)\n\n",
                M, aggro, DONGSEOK_AGGRO, DONGSEOK_STAMINA);
            DONGSEOK_ACTION = ACTION_PROVOKE;
            break;
        case ACTION_PULL:
            if (random >= p) {
                printf("madongseok pulled zombie... Next turn, it can't move\n"); 
            }
            else {
                printf("madongseok failed to pull zombie\n");
            }
            if (DONGSEOK_AGGRO + 1 != AGGRO_MAX) {
                aggro = DONGSEOK_AGGRO;
                DONGSEOK_AGGRO = DONGSEOK_AGGRO + 2;
            }
            else {
                DONGSEOK_AGGRO = AGGRO_MAX;
            }
            printf("madongseok : %d (aggro : %d -> %d, stamina : %d -> %d\n\n",
                M, aggro, DONGSEOK_AGGRO, DONGSEOK_STAMINA, DONGSEOK_STAMINA - 1);
            DONGSEOK_STAMINA--;
            DONGSEOK_ACTION = ACTION_PULL;
            break;
    }
        
    
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

    DONGSEOK_STAMINA = stm;

    printTrain(len, C, Z, M);

    while (1) {
        int cPos = C;
        int zPos = Z;
        int mPos = M;
        int mAns = 0;
        int aAns = 0;
        int random = rand() % 100;

        C = citizenMove(C, p, random); //�ù��̵�
        Z = zombieMove(Z, C, M, turn);

        printTrain(len, C, Z, M);
        printCitizenStatus(cPos, C, CITIZEN_AGGRO);
        printZombieStatus(zPos, Z, turn);

        printTrain(len, C, Z, M);
        M = dongseokMove(M, Z, mAns);
        printDongseokStatus(mPos, M, DONGSEOK_AGGRO, DONGSEOK_STAMINA);
        printf("\n");

        printAction(C, Z, M, stm);
        printdongseokAction(aAns, M, random, p, DONGSEOK_AGGRO, DONGSEOK_STAMINA);

        Sleep(2000);

        if (C == 1) { // �ù��� ���� ���� ĭ�� ������ ��� ����
            break;
        }
        if (C + 1 == Z) { // �ù� �� ĭ�� ���� ������ ��� ����
            break;
        }
        if (DONGSEOK_STAMINA == 0) {
            break;
        }
        turn++;
    }
    outro(C, Z);

    return 0;
}