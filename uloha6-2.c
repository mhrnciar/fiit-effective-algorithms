/*
 * "Šibi, šibi, šibáky, išli ujec na raky. Raky štípu, pichá jež, naše prúty musia tiež…" Jakubko by
 * chcel na Veľkonočný pondelok navštíviť všetky svoje kamarátky v meste. Mesto si môžeme predstaviť ako
 * N domov, v domčeku č.1 býva Jakubko a v každom z ostatných domov býva jedna kamarátka. Jakubko sa medzi
 * domami presúva na kolobežke a chcel by sa čo najmenej nakolobežkovať, aby mu zostali ešte sily na
 * básničky… Zároveň chce navštíviť všetky kamarátky, ale okolo/do každého domu chce ísť práve raz.
 * Napíšte program, ktorý nájde najmenej náročnú cestu z domčeka 1 takú, že navštívi všetky domčeky práve
 * raz, a skončí v ľubovoľnom domčeku. Jakubko nechce okolo toho istého domčeku prechádzať viackrát. Ak
 * existuje viacero rovnako náročných ciest, nájdite takú, v ktorej čísla skôr navštívených domov sú čo
 * najmenšie.
 *
 * Na vstupe je najskôr počet domov v meste N, a potom matica N x N čísel, kde v i-tom riadku a j-tom stĺpci
 * sa nachádza číslo, reprezentujúce námahu presunu z i-teho domčeka do j-teho domčeka. Na výstup napíšte
 * celkovú vynaloženú námahu na navštívenie všetkých kamarátiek, ako aj postupnosť, v akej by mal kamarátky
 * navštevovať, aby dosiahol túto námahu.
 *
 * Ukážka vstupu:
 * 5
 * 1 5 3 2 3
 * 6 4 9 2 5
 * 6 2 4 5 6
 * 1 3 4 5 6
 * 4 5 6 7 8
 *
 * Výstup pre ukážkový vstup:
 * 13
 * 1 3 2 4 5
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
int MIN_PATH = 9999;

void TSP(int *str, int left, int right, int *path, int n, int **arr) {
    int temp;

    // If left equals right (we are at the last house), calculate the total path and if it's smaller than the previous
    // shortest path, save the length and copy the path
    if (left == right) {
        if (DEBUG) {
            for (int i = 0; i < right; i++) {
                printf("%d ", str[i]);
            }
            printf("\n");
        }

        int act = 0, z;

        // Calculate the length of the current path
        for (int m = 0, k = 0; m < right; m++) {
            z = str[m];
            act += arr[k][z - 1];
            k = z - 1;
        }

        // Save new minimum cost and shortest path
        if (act < MIN_PATH) {
            MIN_PATH = act;

            for (int i = 0; i < right; i++) {
                path[i] = str[i];
            }
        }
    }

    // If left and right are not equal, try all switches of selected house with the remaining ones
    else {
        for (int i = left; i < right; i++) {
            // First, switch houses and call recursion with switched order
            temp = str[left];
            str[left] = str[i];
            str[i] = temp;

            TSP(str, left + 1, right, path, n, arr);

            // Return to previous order
            temp = str[left];
            str[left] = str[i];
            str[i] = temp;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int **arr = (int **) calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        arr[i] = (int *) calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    if (DEBUG) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // Permutation array of houses with currently considered order
    int *str = (int *) calloc(n-1, sizeof(int));
    // Array for the shortest path
    int *path = (int *) calloc (n, sizeof(int));

    // Create first order as 1 -> 2 -> 3 -> ... -> n
    for (int i = 2, j = 0; i <= n; i++) {
        str[j] = i;
        j++;
    }

    TSP(str, 0, n - 1, path, n, arr);

    printf("%d\n", MIN_PATH);

    printf("1 ");
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", path[i]);
    }

    // Clean up
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
