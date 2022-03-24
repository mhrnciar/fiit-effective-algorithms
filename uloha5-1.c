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

#define DEBUG 1

int main() {
    int n, limit;

    while (scanf("%d %d", &n, &limit) > 0) {
        int *arr = (int *) malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        if (DEBUG) {
            printf("n: %d, limit: %d\n", n, limit);
            for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
