/*
 * Bernard a Chryzostom majú na stole veľa ceruziek. Keďže nemajú papier, tak si vymysleli hru, ktorou
 * by sa zabavili. Na striedačku si berú ceruzky a ten, kto zoberie posledné zvyšné ceruzky vyhráva.
 * Aby to ale nebolo také nudné, obmedzili si možné ťahy. Hru sa hrajú na viac krát a v každej hre môžu
 * mať inú množinu povolených ťahov. Povolený ťah je počet ceruziek, koľko môžu zobrať na jeden ťah.
 *
 * Na vstupe je niekoľko hier. Pre každú hru je najprv zadané celé číslo N - počet povolených ťahov.
 * Nasleduje N celých čísel T_i vyjadrujúcich povolené ťahy a dve celé čísla A a B. V každej hre
 * spočítajte pre koľko čísel X (A <= X <= B) vyhrá Bernard, ak by sa hrali hru s X ceruzkami a Bernard
 * by ťahal ako prvý.
 *
 * Obmedzenia:
 * 1 <= N <= 50,
 * 1 <= T_i <= 100,
 * 1 <= A <= B,
 * 1 <= B <= 100000
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main() {
    int n, A, B;

    while (scanf("%d", &n) > 0) {
        int *moves = (int *) malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &moves[i]);
        }

        scanf("%d %d", &A, &B);

        if (DEBUG) {
            printf("N: %d\n", n);
            for (int i = 0; i < n; i++) { printf("%d ", moves[i]); }
            printf("\nA: %d\tB: %d\n", A, B);
        }

        int *wins = (int *) calloc((B + 1), sizeof(int));

        for (int i = 1; i <= B; i++) {
            for (int j = 0; j < n; j++) {
                if (moves[j] == 1) {
                    wins[i] = !wins[i-1];

                    if (wins[i]) {
                        break;
                    }
                }

                if (moves[j] <= i) {
                    wins[i] = !wins[i - moves[j]];

                    if (wins[i]) {
                        break;
                    }
                }
            }
        }

        if (DEBUG) {
            for (int i = 0; i < B; i++) {
                printf("%d: %d\n", i, wins[i]);
            }
        }

        int count = 0;
        for (int i = A; i <= B; i++) {
            if (wins[i] == 1)
                count++;
        }

        printf("%d\n", count);

        free(moves);
        free(wins);
    }

    return 0;
}
