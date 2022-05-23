/*
 * Jakubko stále nemôže zaspať, a tak sa rozhodol spočítať všetky N-ciferné palindrómy, ktoré sú deliteľné
 * číslom M a nezačínajú nulou. Na prvom riadku vstupu sa nachádza jediné celé číslo n (1 ≤ n ≤ 1000), ktoré
 * vyjadruje počet úloh, ktoré budú nasledovať. Opis každej úlohy tvorí jeden riadok s dvoma celými číslami
 * M a N (1 ≤ M ≤ 1000, 1 ≤ N ≤ 19).
 *
 * Výstup bude obsahovať n riadkov, na každom z nich jedno číslo vyjadrujúce počet palindrómov vypočítaný
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
#include <string.h>

#define TEN 10
#define MAX_LEN 22

int main() {
    int M, N, ex, mid;
    long long arr[1001][TEN+1], temp[MAX_LEN], pos, H, L;

    scanf("%d", &ex);

    while (ex > 0) {
        scanf("%d %d", &M, &N);

        if (N == 0) {
            printf("0");
            continue;
        }

        // Clean the array and calculate the middle position
        memset(arr, 0, sizeof(arr));

        mid = (N - 1) / 2;
        temp[0] = 1;

        for (int i = 1; i < MAX_LEN; i++) {
            temp[i] = (temp[i - 1] * TEN) % M;
        }

        // If the length is even, there are 2 middle numbers, so 2 numbers from temp are used, the last from first
        // half, and the first from the second half
        if ((N & 1) == 0) {
            for (int i = 0; i < TEN; i++) {
                if (i || N > 2) {
                    pos = i * temp[mid + 1];
                    pos += i * temp[mid];
                    arr[pos % M][0]++;
                }
            }
        }
        // If the length is odd, there is only one number in the middle used to calculate position, which
        // needs to be increased by 1
        else {
            for (int i = 0; i < TEN; i++) {
                if (i || N > 1) {
                    pos = i * temp[mid];
                    arr[pos % M][0]++;
                }
            }
        }

        // The number is palindrome, so the first half is identical to the second half and we can do only half the
        // cycles, but we need to update both sides, or the result will be incorrect
        for (int j = 0; j < mid; j++) {
            // Calculate the position of the increased digit as mid position + offset, and + 1 if the length is even
            pos = mid + 1 + j + !(N & 1);
            H = temp[pos];
            L = temp[mid - 1 - j];

            for (int i = 0; i < M; i++) {
                for (int k = 0; k < TEN; k++) {
                    if (k || j + 1 < mid) {
                        pos = H * k + i;
                        pos += L * k;
                        arr[pos % M][j + 1] += arr[i][j];
                    }
                }
            }
        }

        printf("%lld\n", arr[0][mid]);
        ex--;
    }

    return 0;
}
