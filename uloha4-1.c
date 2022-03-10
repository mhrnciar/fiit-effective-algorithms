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
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main() {
    int n, width, height, rows, slope;
    scanf("%d", &n);

    while (n > 0) {
        scanf("%d %d", &width, &height);
        rows = height + 1;

        int **arr = (int **) calloc(rows, sizeof(int *));
        for (int i = 0; i < rows; i++) {
            arr[i] = (int *) calloc(width, sizeof(int));
        }
        arr[height][0] = 1;

        // Fill left (rising) half of array
        for (int j = 1; j <= width / 2; j++) {
            for (int i = height - 1; i >= 0; i--) {
                // If we are in upper row, sum only numbers from previous column, same and lower rows,
                // otherwise sum numbers from previous column, upper, same and lower rows
                arr[i][j] = i == 0 ? arr[i][j-1] + arr[i+1][j-1] : arr[i-1][j-1] + arr[i][j-1] + arr[i+1][j-1];
            }
        }

        // Fill right (declining) half of array
        slope = 0;
        for (int j = width / 2 + 1; j < width; j++) {
            for (int i = height - 1; i > slope; i--) {
                // If we are in upper row, sum only numbers from previous column, same and lower rows,
                // otherwise sum numbers from previous column, upper, same and lower rows, and lower
                // maximum height of hill by one every column
                arr[i][j] = i == 0 ? arr[i][j-1] + arr[i+1][j-1] : arr[i-1][j-1] + arr[i][j-1] + arr[i+1][j-1];
            }
            slope++;
        }

        // Set last number in lower right corner
        arr[height][width - 1] = arr[height - 1][width - 2];

        if (DEBUG) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < width; j++) {
                    printf("%10d", arr[i][j]);
                }
                printf("\n");
            }
        }


        for (int i = 0; i <= height; i++) {
            free(arr[i]);
        }
        free(arr);
        n--;
    }

    return 0;
}
