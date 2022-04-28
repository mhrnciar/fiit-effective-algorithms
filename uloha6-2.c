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
    }

    // TODO: PROBLÉM OBCHODNÉHO CESTUJÚCEHO

    return 0;
}
