/*
 * Jakubkovi sa snívalo, že tancoval na plese. Na plese bolo N chlapcov a M dievčat. Pre správne zaplnenie
 * parketu je potrebné ich prideliť do presne K párov. Toto však nie je úplne ľahké, pretože niektoré deti
 * nemôžu tancovať s niektorými, kvôli rozdielnosti vo výške, tanečnej zručnosti príp. znalosti programovania.
 * Jakubkovi sa ešte prisnil počet možností, koľkými je možné deti takto rozdeliť, nestihol si to však
 * zapamätať. Napíšte program, ktorý vypočíta toto číslo.
 *
 * Na štandardnom vstupe bude viacero vstupov, každý vstup obsahuje najskôr číslo K (do 10), potom čísla
 * N (počet chlapcov do 10) a M (počet dievčat do 10), a potom N riadkov každý s M znakmi Y (áno) alebo N
 * (nie), podľa toho či i-ty chlapec môže tancovať s j-tym dievčaťom. Pre každý vstup vypíšte jeden riadok
 * obsahujúci jedno číslo počet rôznych priradení detí tak, že na parkete tancuje presne K párov, ktoré spolu
 * môžu tancovať.
 *
 * Ukážka vstupu:
 * 3
 * 3 4
 * YYYY
 * YYYY
 * YYYY
 * 3
 * 3 4
 * YYNN
 * NYYN
 * NNYY
 * 3
 * 6 6
 * YYNNNN
 * NYYNNN
 * NNYYNN
 * NNNYYN
 * NNNNYY
 * YNNNNY
 *
 * Výstup pre ukážkový vstup:
 * 24
 * 4
 * 112
 */

// https://github.com/PeterPlevko/STU-FIIT/blob/main/Tvorba%20efektivnych%20algoritmov%20a%20programov/Cviko7/uloha7-1.c
#include <stdio.h>

#define DEBUG 1
#define TEN 10
#define THOUSAND 1000

int big_arr[TEN][THOUSAND][TEN];
char arr[TEN][TEN];
int N, M, K;


int rec(int x, int y, int z) {
    if (z == K) {
        return 1;
    }

    if (x == N) {
        return 0;
    }

    if (big_arr[x][y][z] != -1) {
        return big_arr[x][y][z];
    }

    int total = rec(x + 1, y, z);

    for (int i = 0; i < M; i++) {
        if (arr[x][i] == 'Y' && ((y >> i) & 1) == 0) {
            total += rec(x + 1, y | (1 << i), z + 1);
        }
    }

    big_arr[x][y][z] = total;

    return total;
}


int main() {
    while (scanf("%d", &K) > 0) {
        scanf("%d %d", &N, &M);

        char c;
        for (int i = 0; i < N; i++) {
            scanf("%c", &c);

            for (int j = 0; j < M; j++) {
                scanf("%c", &(arr[i][j]));
            }
        }

        for (int i = 0; i < TEN; i++){
            for (int j = 0; j < THOUSAND; j++) {
                for (int k = 0; k < TEN; k++) {
                    big_arr[i][j][k] = -1;
                }
            }
        }

        int out = rec(0, 0, 0);
        printf("%d\n", out);
    }

    return 0;
}
