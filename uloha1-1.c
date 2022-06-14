/*
 * Humanitárny konvoj sa presúva na Ukrajinu do hlavného mesta Kyjev, aby pomohol tunajším ľuďom. Ako
 * jeden z organizátorov si sa dozvedel, že konvoj má prechádzať cez most s nosnosťou N. Vieš, že na
 * most sa nezmestí viac ako K vozidiel súčasne. Zároveň poznáš hmotnosť každého vozidla. (Naopak
 * nevieš vopred povedať akým spôsobom budú vozidlá cez most prechádzať). Tvojou úlohou je zistiť,
 * či je prejazd cez most pre konvoj bezpečný, alebo nie.
 *
 * Na vstupe je niekoľko riadkov, každý obsahuje čísla N, K, M a M čísel h[i], ktoré určujú hmotnosť
 * vozidiel konvoja. Pre každý riadok na vstupe vypíšte Ano ak konvoj môže bezpečne prejsť cez most
 * bez ohľadu nato v akom poradí budú vozidlá cez most prechádzať, inak vypíšte Nie.
 *
 * Obmedzenia:
 * 1 <= N <= 10000,
 * 1 <= K <= M,
 * 1 <= M <= 9,
 * 1 <= h[i] <= 1000
 *
 * Ukážka vstupu:
 * 1234 3 4 1000 200 4 30
 * 20 4 5 10 10 10 10 10
 *
 * Výstup pre ukážkový vstup:
 * Ano
 * Nie
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

// Sorting function to sort in descending order
int cmpfunc(const void *a, const void *b) {
    return (*(int *) b - *(int *)a);
}

int main() {
    int capacity, max_vehicles, n_cars;

    while (scanf("%d", &capacity) > 0) {
        scanf("%d %d", &max_vehicles, &n_cars);

        int *cars = (int *) malloc(sizeof(int) * n_cars);

        for (int i = 0; i < n_cars; i++) {
            scanf("%d", &cars[i]);
        }

        if (DEBUG) {
            printf("Original: \n");
            for (int i = 0; i < n_cars; i++) {
                printf("%d ", cars[i]);
            }
            printf("\n");
        }

        // Sort cars in descending order
        qsort(cars, n_cars, sizeof(int), cmpfunc);

        if (DEBUG) {
            printf("Sorted: \n");
            for (int i = 0; i < n_cars; i++) {
                printf("%d ", cars[i]);
            }
            printf("\n");
        }

        // If first N heaviest vehicles and sum their weight, if it's over max capacity,
        // the convoy cannot go through the bridge in any order
        int sum = 0;
        for (int i = 0; i < max_vehicles; i++) {
            sum += cars[i];
        }

        if (sum <= capacity)
            printf("Ano\n");
        else
            printf("Nie\n");

        free(cars);
    }
}
