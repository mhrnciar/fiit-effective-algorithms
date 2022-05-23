/*
 * Keď minule Jakubko nemohol zaspať, zobral si papier a začal si kresliť kopčeky.
 * Prvý riadok vstupu obsahuje číslo N (1 ≤ N ≤ 20) vyjadrujúce počet úloh. Každá úloha pozostáva z riadku
 * obsahujúceho dve celé čísla D (2 ≤ D ≤ 5000) a V (1 ≤ V ≤ 200).
 *
 * Výstup bude obsahovať N riadkov, pre každú úlohu jeden. Obsahovať budú počet rôznych kopcov majúcich
 * šírku D metrov a výšku presne V metrov. Kopec pozostáva len z troch možných úsekov: stúpanie široké
 * 1 meter a vysoké 1 meter, klesanie široké 1 meter a vysoké 1 meter a rovinka široká 1 meter. Jednotlivé
 * úseky musia na seba nadväzovať, výška nesmie presiahnuť V metrov, na začiatku a na konci musí mať kopec
 * nulovú výšku a nikde inde nesmie byť výška ≤ 0 (takže kopec napríklad nemôže začínať alebo končiť
 * rovinkou). Keďže takých kopcov môže byť veľmi veľa, vypíšte počet kopcov ako zvyšok po delení číslom
 * 100 000 007.
 *
 * Ukážka vstupu:
 * 2
 * 6 2
 * 30 5
 *
 * Výstup pre ukážkový vstup:
 * 7
 * 11640085
 */

#include <stdio.h>
#define DEBUG 0

typedef struct node {
    int touched;
    int untouched;
} NODE;

int main() {
    int n, width, height;
    long num;
    NODE arr[202][5002] = {0};
    scanf("%d", &n);

    while (n > 0) {
        scanf("%d %d", &width, &height);
        width += 1;

        if (height == 1)
            arr[height][0].touched = 1;
        else
            arr[height][0].untouched = 1;

        // Fill left (rising) half of array
        for (int j = 1; j < width - height; j++) {
            for (int i = height - 1; i >= 0; i--) {
                // If we reached the top of hill, add to the paths that already touched the top the paths
                // that are one column and one row behind, which could become paths that touched the top
                if (i == 0) {
                    num = arr[i][j-1].touched + arr[i + 1][j - 1].touched + arr[i + 1][j - 1].untouched;
                    arr[i][j].touched = num > 100000007 ? num % 100000007 : num;
                    continue;
                }

                // Add paths that touched the top from previous column together as well as paths that haven't
                num = arr[i][j - 1].touched + arr[i - 1][j - 1].touched + arr[i + 1][j - 1].touched;
                arr[i][j].touched = num > 100000007 ? num % 100000007 : num;

                num = arr[i][j - 1].untouched + arr[i - 1][j - 1].untouched + arr[i + 1][j - 1].untouched;
                arr[i][j].untouched = num > 100000007 ? num % 100000007 : num;
            }
        }

        // Fill right (declining) half of array
        for (int j = width - height, slope = 0; j < width; j++, slope++) {
            for (int i = height - 1; i > slope; i--) {
                // Repeat the path count propagation, but with declining slope
                num = arr[i][j - 1].touched + arr[i - 1][j - 1].touched + arr[i + 1][j - 1].touched;
                arr[i][j].touched = num > 100000007 ? num % 100000007 : num;

                num = arr[i][j - 1].untouched + arr[i - 1][j - 1].untouched + arr[i + 1][j - 1].untouched;
                arr[i][j].untouched = num > 100000007 ? num % 100000007 : num;
            }
        }

        // Set last number in lower right corner
        arr[height][width - 1] = arr[height - 1][width - 2];

        if (DEBUG) {
            for (int i = 0; i < height + 1; i++) {
                for (int j = 0; j < width; j++) {
                    printf("%10d", arr[i][j].touched);
                }
                printf("\n");
            }
            printf("\n");

            for (int i = 0; i < height + 1; i++) {
                for (int j = 0; j < width; j++) {
                    printf("%10d", arr[i][j].untouched);
                }
                printf("\n");
            }
        }

        // Print result
        printf("%d\n", arr[height][width - 1].touched);

        // Clean up
        for (int i = 0; i <= height; i++) {
            for (int j = 0; j <= width; j++) {
                arr[i][j].touched = 0;
                arr[i][j].untouched = 0;
            }
        }
        n--;
    }

    return 0;
}
