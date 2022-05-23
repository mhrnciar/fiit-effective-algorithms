/*
 * Jakubko by vás chcel pochváliť. Doposiaľ ste mali príležitosť vyriešiť niekoľko príkladov. Pravidlá sú
 * nasledovné: Ak vyriešite nejaký príklad, tak môžete ten ďalší preskočiť (ale nemusíte). Každý príklad
 * má určitú hodnotu radosti U_i, t.j. ako veľmi Jakubka potešíte, keď vyriešite daný príklad. Jakubko vás
 * pochváli vtedy, keď rozdiel medzi maximálnou a minimálnou hodnotou radosti dosiahne (alebo presiahne)
 * hodnotu K. Musíte teda vyriešiť problémy, ktoré majú danú maximálnu a minimálnu hodnotu radosti. Ak to
 * nemôže nikdy nastať, musíte vyriešiť všetky úlohy. Ak sa vám vyriešením niektorej úlohy podarí dosiahnuť
 * rozdiel medzi maximálnou a minimálnou hodnotou radosti aspoň K, všetky nasledujúce úlohy už nemusíte
 * riešiť. Vypočítajte, koľko najmenej problémov musíte vyriešiť, aby ste splnili Jakubkove požiadavky na
 * pochvalu.
 *
 * Na vstupe je niekoľko prípadov. Pre každý prípad sú zadané čísla N a K. Nasleduje N čísel, kde každé
 * vyjadruje hodnotu radosti U_i pre jednotlivé príklady.
 *
 * Obmedzenia:
 * 1 <= N <= 50,
 * 0 <= U_i <= 1000,
 * 0 <= K <= 1000
 *
 * Ukážka vstupu:
 * 3 2
 * 1 2 3
 * 5 4
 * 1 2 3 4 5
 *
 * Výstup pre ukážkový vstup:
 * 2
 * 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0

// Compare first pos-2 numbers in array with the currently selected number and add 1 to position,
// if the difference is bigger than the limit
int *check_pos(int *arr, int pos, int limit, int *count) {
    int *out = (int *) malloc(pos * sizeof(int));

    for (int i = 0; i < pos - 1; i++) {
        if (abs(arr[i] - arr[pos - 1]) >= limit) {
            out[ (*count)++ ] = i + 1;
        }
    }

    if (DEBUG) {
        printf("pos: %d, ", pos);
        for (int i = 0; i < pos; i++) {
            printf("%d ", out[i]);
        }
        printf("\n");
    }

    return out;
}

int main() {
    int n, limit;

    while (scanf("%d %d", &n, &limit) > 0) {
        int min = 1000, max = 0, found = 0;
        int *arr = (int *) malloc(n * sizeof(int));

        // Read n numbers from input while saving max and min
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            if (arr[i] < min) {
                min = arr[i];
            }
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        if (DEBUG) {
            printf("n: %d, limit: %d\n", n, limit);
            for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }

        // If the difference between max and min is lower than limit,
        // or there are only 2 exercises, print n (must solve all exercises)
        if (max - min < limit || n <= 2) {
            printf("%d\n", n);
            continue;
        }

        // First exercise always has to be solved, so start from the second number, but since we can
        // omit one exercise, if we solved the previous one, we will compare the i+1-th position.
        // List of positions where the difference is higher than limit is returned along with the count
        for (int i = 1; i < n; i++) {
            int count = 0, best = 999;
            int *res = check_pos(arr, i + 1, limit, &count);

            // If count is not 0 (some solution has been found), calculate the number of exercises between
            // min and max + 1, if the result is smaller than current best, update the best
            if (count != 0) {
                for (int j = 0; j < count; j++) {
                    int steps = floor((double) res[j] / 2);
                    steps += ceil((double) ((i + 1) - res[j]) / 2) + 1;
                    best = steps < best ? steps : best;
                }

                // Set flag to found and print the best solution
                printf("%d\n", best);
                found = 1;
                break;
            }
        }

        // If best hasn't been found, print n
        if (!found) {
            printf("%d\n", n);
        }

        free(arr);
    }

    return 0;
}
