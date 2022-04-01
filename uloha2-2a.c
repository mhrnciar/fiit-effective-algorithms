/*
 * Jakubko sa učí sčitovať. Pre daný reťazec číslic určite koľko najmenej znamienok sčítania je potrebné
 * do reťazca vložiť, aby výsledný výraz mal nejaký konkrétny súčet. Napr. ak chceme pre reťazec 303
 * dosiahnuť súčet 6, tak stačí vložiť jedno znamienko sčítania (3+03=6).
 *
 * Vstup: Štandardný vstup môže obsahovať zápisy viacerých úloh. Každý zápis obsahuje reťazec čísel
 * obsahujúci najviac 10 znakov a súčet, ktorý chceme dosiahnuť, oddelené medzerou.
 *
 * Výstup: Pre každé zadanie úlohy na vstupe vypíšte na štandardný výstup jeden riadok obsahujúci jedno
 * číslo - najmenší počet znamienok sčítania, ktoré je nutné do reťazca na vstupe vložiť, aby výsledný
 * výraz mal požadovaný súčet. Ak nie je možné súčet dosiahnuť, vypíšte IMPOSSIBLE
 *
 * Ukážka vstupu:
 * 999 27
 * 101 2
 * 999 100
 *
 * Výstup pre ukážkový vstup:
 * 2
 * 1
 * IMPOSSIBLE
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int len(long number) {
    if (number == 0) {
        return 1;
    }

    return floor (log10 (abs (number))) + 1;
}


int extract(long number, int left, int right) {
    return (number / (long) pow(10, right)) % (long) pow(10, len(number) - left - right);
}


int main() {
    long x, target;
    while (scanf("%ld %ld", &x, &target) > 0) {
        int current_best = 1 << 30;

        for (long i = 0; i < pow(2, len(x)); i++) {
            long out = 0, previous = 0, ones = -1;

            for (int j = 1; j <= len(x); j++) {
                if ((i >> (len(x) - j)) & 1) {
                    out += extract(x, previous, len(x) - j);
                    previous = j;
                    ones++;
                }
            }

            if (previous != len(x)) {
                out += extract(x, previous, 0);
                ones++;
            }

            if (out == target && ones < current_best) {
                current_best = ones;
            }
        }

        if (current_best == (1 << 30)) {
            printf("IMPOSSIBLE\n");
        }

        else {
            printf("%d\n", current_best);
        }
    }

    return 0;
}