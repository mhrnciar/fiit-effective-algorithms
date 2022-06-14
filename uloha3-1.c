/*
 * Okolo roku 1924 vymyslel Jan Łukasiewicz Poľskú notáciu, ktorá nepotrebuje zátvorky. Dnes poznáme túto
 * notáciu aj ako prefixovú notáciu. Na rozdiel od reverznej Poľskej (postfixovej) notácie však prefixová
 * notácia nie je jednoznačná. Vypočítajte pre daný výraz koľkými spôsobmi ho vieme vyhodnotiť.
 *
 * Na vstupe je niekoľko výrazov v prefixovej notácii. Každý výraz pozostáva z najviac 50 znakov, čo môžu
 * byť číslice, alebo znaky '+', '-', '*' a '/'. Operátor - (mínus) môže byť unárny iba pre čisto číselný
 * výraz, napr. -3 ale nie -(3*2).
 *
 * Ukážka vstupu:
 * 11111111111110
 * 2/3
 * *3-1-98
 * +++111111111
 *
 * Výstup pre ukážkový vstup:
 * 1
 * 0
 * 2
 * 56
 */

// https://github.com/PeterPlevko/STU-FIIT/blob/main/Tvorba%20efektivnych%20algoritmov%20a%20programov/Cviko3/uloha3-1.c
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define isNumber(x) ((arr[x] >= 48) && (arr[x] < 58))

unsigned long long int evaluate(const char *arr, int length) {
    unsigned long long int **memory = (unsigned long long int **) calloc(length, sizeof(unsigned long long int *));
    for (int i = 0; i < length; ++i) {
        memory[i] = (unsigned long long int *) calloc(length, sizeof(unsigned long long int));
    }

    // Fill main diagonal according to rules for length 1
    for (int i = 0; i < length; ++i) {
        if (isNumber(i)) {
            memory[i][i] = 1;
        } else {
            memory[i][i] = 0;
        }
    }

    // Fill diagonal according to rules for length 2
    for (int i = 0; i < length - 1; ++i) {
        if ((isNumber(i) || arr[i] == 45) && isNumber(i+1)) {
            memory[i][i + 1] = 1;
        } else {
            memory[i][i + 1] = 0;
        }
    }

    // Fill remaining diagonals according to rules for lengths 3...N
    for (int i = 3; i < length + 1; ++i) {
        for (int j = 0; j < length - i + 1; ++j) {
            if (isNumber(j)) {
                int good = 1;
                int now = j;
                while (now <= j + i - 1) {
                    if(!isNumber(now)) {
                        good = 0;
                        break;
                    }
                    now++;
                }
                memory[j][j + i - 1] = good;
            }
            else {
                unsigned long long int count = 0;
                for (int k = 0; k < i-2; ++k) {
                    count += memory[j + 1][j + 1 + k] * memory[j + 2 + k][j + i - 1];
                }
                if (arr[j] == 45) {
                    int good = 1;
                    int now = j + 1;
                    while (now <= j + i - 1) {
                        if(!isNumber(now)) {
                            good = 0;
                            break;
                        }
                        now++;
                    }
                    count += good;
                }
                memory[j][j + i - 1] = count;
            }
        }
    }

    if (DEBUG) {
        for (int l = 0; l < length; ++l) {
            for (int j = 0; j < length; ++j) {
                printf("%2lld ", memory[l][j]);
            }

            printf("\n");
        }
    }

    unsigned long long int res = memory[0][length-1];

    // Clean up
    for (int i = 0; i < length; ++i) {
        free(memory[i]);
    }
    free(memory);

    return res;
}

int main() {
    char arr[50];

    while (scanf("%s", arr) >= 1) {
        int length = -1;
        while (arr[++length] != 0) {}

        printf("%lld\n", evaluate(arr, length));
    }

    return 0;
}
