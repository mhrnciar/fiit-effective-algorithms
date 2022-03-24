/*
 * Jakubko sa pripravuje na programátorský test z rekurzie. Prechádza si staršie úlohy a snaží sa ich
 * vyriešiť rekurzívne. Našiel úlohu na určenie všetkých N prvkových variácií s opakovaním z K-prvkovej
 * množiny.
 *
 * Na vstupe sú prirodzené čísla N a K, napíšte rekurzívny program, ktorý na výstup vypíše všetky N prvkové
 * variácie s opakovaním z K-prvkovej množiny čísel 1, 2, ..., K.
 *
 * Ukážka vstupu:
 * 3 2
 *
 * Výstup pre ukážkový vstup:
 * 1 1 1
 * 1 1 2
 * 1 2 1
 * 1 2 2
 * 2 1 1
 * 2 1 2
 * 2 2 1
 * 2 2 2
 */

#include <stdio.h>
#include <stdlib.h>

void variations(int *arr, int n, int k, int step) {
    if (step == n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }

    for (int j = 1; j <= k; j++) {
        arr[step] = j;
        variations(arr, n, k, step + 1);
    }
}

int main() {
    int n, k;

    scanf("%d %d", &n, &k);
    int *arr = (int *) malloc(n * sizeof(int));

    variations(arr, n, k, 0);

    return 0;
}
