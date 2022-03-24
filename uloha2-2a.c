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

#define DEBUG 1

int main() {
    char input[11], c;
    int result;
    int arr[10][10] = {0};
    int numbers[10] = {0};

    while (scanf("%s %d", input, &result) > 0) {
        int n = 0;
        char *p = input;

        while(p[n] != '\0') {
            c = p[n];
            numbers[n] = c - '0';
            n++;
        }

        if (DEBUG) {
            for (int i = 0; i < n; i++) {
                printf("%d ", numbers[i]);
            }
            printf("\n");
        }

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (i == 0) {
                    if (j == 0) {
                        arr[0][0] = numbers[0];
                        continue;
                    }
                    arr[i][j] = arr[i][j-1] * 10 + numbers[j];
                }
                else {
                    arr[i][j] = arr[i][j-1] * 10 + numbers[j];
                }
            }
        }

        if (DEBUG) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%10d\t", arr[i][j]);
                }
                printf("\n");
            }
        }

        int remaining = result, found = 0, plus_count = 0, limit = n, i = n - 1, j;

        while (i >= 0) {
            j = n - 1;
            while (j >= i && j >= 0) {
                remaining -= arr[i][j];

                if (remaining < 0) {
                    remaining += arr[i][j];
                    j--;
                }
                else if (remaining > 0) {
                    int diff = 0, temp = arr[i][j];

                    while (temp > 1) {
                        temp /= 10;
                        diff++;
                    }
                    if (diff == 0){
                        diff = 1;
                    }

                    j -= diff;
                    i -= diff;

                    if (arr[i][j] != 0) {
                        plus_count++;
                    }
                    else {
                        plus_count--;
                    }
                }
                else {
                    found = 1;
                    break;
                }
            }

            // TODO: Skusiť i od 0 a postupne prehlbovať tabuľku až kým sa nenájde riešenie
            if (found) {
                break;
            }
            else if (i <= 0 && j <= 0 && limit >= 0){
                remaining = result;
                plus_count = 0;
                limit--;
                i = limit;
            }

            i--;
        }

        if (found && plus_count < 10) {
            printf("%d\n", plus_count);
        }
        else {
            printf("IMPOSSIBLE\n");
        }
    }

    return 0;
}
