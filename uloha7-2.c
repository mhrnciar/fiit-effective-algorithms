/*
 * Jakubko stále nemôže zaspať, a tak sa rozhodol spočítať všetky N-ciferné palindrómy, ktoré sú deliteľné
 * číslom M a nezačínajú nulou. Na prvom riadku vstupu sa nachádza jediné celé číslo N (1 ≤ N ≤ 1000), ktoré
 * vyjadruje počet úloh, ktoré budú nasledovať. Opis každej úlohy tvorí jeden riadok s dvoma celými číslami
 * M a N (1 ≤ M ≤ 1000, 1 ≤ N ≤ 19).
 *
 * Výstup bude obsahovať N riadkov, na každom z nich jedno číslo vyjadrujúce počet palindrómov vypočítaný
 * podľa vyššie uvedených pravidiel.
 *
 * Ukážka vstupu:
 * 2
 * 2 1
 * 2 2
 *
 * Výstup pre ukážkový vstup:
 * 4
 * 4
 */

#include <stdio.h>
#include <math.h>

#define DEBUG 1
#define TEN 10
#define MIDDLE(N) (int)((N - 1) / 2)

long long arr[TEN][1000];
long long start, rem, l_rem, r_rem, n_rem;

void palindromes_odd(int d, int N, int M) {
    // Since the number is palindrome, we only need to work with half of the number
    while (d <= MIDDLE(N)) {
        if (d == MIDDLE(N)) {
            start = 1;
        }
        else {
            start = 0;
        }

        if (d == 0) {
            for (int i = start; i < TEN; i++) {
                rem = (i * (long long) pow(TEN, N / 2)) % M;
                arr[d][rem] += 1;
            }
        }
        else {
            for (int i = start; i < TEN; i++) {
                l_rem = (i * (long long) pow(TEN, N / 2 + d)) % M;
                r_rem = (i * (long long) pow(TEN, MIDDLE(N) - d)) % M;
                rem = (l_rem + r_rem) % M;

                for (int j = 0; j < M; j++) {
                    n_rem = (rem + j) % M;
                    arr[d][n_rem] += arr[d - 1][j];
                }
            }
        }
        d++;
    }
}

void palindromes_even(int d, int N, int M) {
    while (d <= MIDDLE(N)) {
        if (d == MIDDLE(N)) {
            start = 1;
        }
        else {
            start = 0;
        }

        if (d == 0) {
            for (int i = start; i < TEN; i++) {
                rem = i * (long long) pow(TEN, N / 2);
                rem += i * (long long) pow(TEN, N / 2 - 1);
                rem %= M;
                arr[d][rem] += 1;
            }
        }
        else {
            for (int i = start; i < TEN; i++) {
                l_rem = (i * (long long) pow(TEN, N / 2 + d)) % M;
                r_rem = (i * (long long) pow(TEN, MIDDLE(N) - d)) % M;
                rem = (l_rem + r_rem) % M;

                for (int j = 0; j < M; j++) {
                    n_rem = (rem + j) % M;
                    arr[d][n_rem] += arr[d - 1][j];
                }
            }
        }
        d++;
    }
}

int main() {
    int ex, N, M;

    scanf("%d", &ex);
    while (ex > 0) {
        scanf("%d %d", &M, &N);

        // If number length is odd, call palindromes_odd() function, otherwise call palindromes_even()
        if (N & 1) {
            palindromes_odd(0, N, M);
        }
        else {
            palindromes_even(0, N, M);
        }

        printf("%lld\n", arr[(N - 1) / 2][0]);

        ex--;

        // Clean used space
        for (int i = 0; i < TEN; i++) {
            for (int j = 0; j < M+1; j++) {
                arr[i][j] = 0;
            }
        }
    }

    return 0;
}
