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
 *
 * Ukážka vstupu:
 * 1
 * 1
 * 1000 1000
 * 10
 * 1 2 3 4 5 6 7 8 9 10
 * 1 100000
 * 4
 * 1 3 7 19
 * 1 100000
 *
 * Výstup pre ukážkový vstup:
 * 0
 * 90910
 * 50000
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

        // Using DP, first set sure wins in first places, then always look at already initialised element
        // to which the player would get after taking specific amount of pencils and flip result (since the
        // players don't play at once, but in turns)
        for (int i = 1; i <= B; i++) {
            for (int j = 0; j < n; j++) {
                if (moves[j] == 1) {
                    wins[i] = wins[i-1] == 1 ? 0 : 1;

                    if (wins[i] == 1) {
                        break;
                    }
                }

                if (moves[j] < i + 1) {
                    wins[i] = wins[i - moves[j]] == 1 ? 0 : 1;

                    if (wins[i] == 1) {
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

        // Count possible wins
        int count = 0;
        for (int i = A; i < B + 1; i++) {
            if (wins[i] == 1)
                count++;
        }

        printf("%d\n", count);

        free(moves);
        free(wins);
    }

    return 0;
}
