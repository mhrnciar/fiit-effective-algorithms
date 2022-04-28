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

int count_steps(int left, int right) {
    int count = 1;

    if (left < right) {
        if (left & 1) {
            count = count + left / 2 + (left & 1);
        }
        else {
            count = count + left / 2;
        }

        // left -> right
        int p = right - left;
        if (p & 1) {
            count = count + p / 2 + (p & 1);
        }
        else{
            count = count + p / 2;
        }
    }
    // If right > left
    else {
        if (right & 1) {
            count = count + right / 2 + (right & 1);
        }
        else {
            count = count + right / 2;
        }

        // right -> left
        int p = left - right;
        if (p & 1) {
            count = count + p / 2 + (p & 1);
        }
        else {
            count = count + p / 2;
        }
    }

    return count;
}

int main() {
    int N, K;

    while (scanf("%d %d", &N, &K) > 0) {
        int **arr = (int **) calloc(N, sizeof(int *));
        for (int i = 0; i < N; i++) {
            arr[i] = (int *) calloc(N, sizeof(int));
        }

        int count = N, num, k = 1;
        for (int i = 0; i < N; i++) {
            scanf("%d", &num);

            // Use DP to fill table with collected satisfaction
            arr[0][i] = num;

            if (i == 0) {
                continue;
            }

            for (int j = 0; j < i; j++) {
                arr[k][j] = abs(arr[0][j] - arr[0][i]);

                // Count the amount of exercises needed to reach the difference of satisfaction >= K
                if (arr[k][j] >= K) {
                    int temp = count_steps(i, j);

                    if (temp < count) {
                        count = temp;
                    }
                }
            }
            k++;
        }

        printf("%d\n", count);

        // Clean up
        for (int i = 0; i < N; i++) {
            free(arr[i]);
        }
        free(arr);
    }

    return 0;
}
