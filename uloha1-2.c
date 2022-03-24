/*
 * Skupina Iron Maiden po koncerte na Topfeste sa vracia naspäť domov do Londýna. Teraz sa potrebujú
 * zbaliť. Majú veľa vecí - kostýmy, aparatúru, gitary, bicie, pareničky a korbáčiky,... K dispozícii
 * majú ľubovoľný počet kamiónov, no keďže zaplatenie každého kamiónu niečo stojí, chcú minimalizovať
 * celkové náklady. Každý kamión má nosnosť 300 krabíc. Keďže chcú mať vo veciach poriadok, balia ich
 * spolu do väčších balíkov, každý pojme 101 až 300 krabíc. Tvojou úlohou je zistiť koľko najmenej
 * kamiónov potrebujú na úspešné prepravenie vecí (zabalených vo väčších balíkoch) domov.
 *
 * Každý riadok obsahuje celé číslo N predstavujúce počet väčších balíkov do ktorých sú zabalené veci,
 * a N čísel x[i], kde x[i] je počet krabíc zabalených v i-tom balíku. Pre každý riadok vypíšte jedno
 * číslo - minimálny počet kamiónov, ktoré musíme zaplatiť na prevezenie všetkých krabíc (ktoré sú
 * balené vo väčších balíkoch).
 *
 * Obmedzenia:
 * 1 <= N <= 50,
 * 101 <= x[i] <= 300
 *
 * Ukážka vstupu:
 * 5 150 150 150 150 150
 * 9 101 101 101 101 101 101 101 101 101
 *
 * Výstup pre ukážkový vstup:
 * 3
 * 5
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main() {
    int n_boxes;

    while (scanf("%d", &n_boxes) > 0) {
        int *boxes = (int *) malloc(sizeof(int) * n_boxes);

        for (int i = 0; i < n_boxes; i++) {
            scanf("%d", &boxes[i]);
        }

        if (DEBUG) {
            printf("Loaded: \n");
            for (int i = 0; i < n_boxes; i++) {
                printf("%d ", boxes[i]);
            }
            printf("\n");
        }

        int trucks = 0;
        int *buckets = (int *) calloc(200, sizeof(int));

        // If there are more than 200 boxes in one group, it has to be packed into one truck alone,
        // otherwise add it to counting array
        for (int i = 0; i < n_boxes; i++) {
            if (boxes[i] >= 200)
                trucks++;
            else
                buckets[boxes[i]]++;
        }

        if (DEBUG) {
            printf("Trucks: %d\n", trucks);
            printf("Buckets: \n");
            for (int i = 101; i < 200; i++) {
                printf("%d: %d\n", i, buckets[i]);
            }
            printf("\n");
        }

        // Go through counting array and try to pair groups - if sum of two groups is <= 300, put them into
        // one truck, otherwise pack only larger group
        int front = 101, back = 199;
        while (front <= back) {
            if (buckets[front] > 0 && buckets[back] > 0) {
                if (front + back <= 300) {
                    buckets[front]--;
                    buckets[back]--;
                    trucks++;
                }
                else {
                    buckets[back]--;
                    trucks++;
                }
            }
            else if (buckets[front] > 0 && buckets[back] == 0) {
                back--;
            }
            else if (buckets[front] == 0 && buckets[back] > 0) {
                front++;
            }
            else {
                front++;
                back--;
            }
        }

        printf("%d\n", trucks);

        free(boxes);
        free(buckets);
    }
}
