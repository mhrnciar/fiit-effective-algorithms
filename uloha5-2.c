/*
 * Jakubko sa hral s kockami. Na každej kocke je nakreslená šípka doľava (označujeme <) alebo šípka doprava
 * (označujeme >). Nepárny počet kociek s nejakými šípkami je rozostavených do radu vedľa seba. Jakubko sa
 * hrá nasledovnú hru, vyberie si kocku, ktorá nie je na kraji a zoberie z radu vybranú kocku a susednú kocku
 * na ktorú vybraná kocka ukazuje. Následne Jakubko kocky prisunie k sebe, aby nezostala v rade medzera.
 * Tento proces opakuje, až kým nezostane len jedna kocka. Otázka je, ktorá kocka (v pôvodnom poradí) môže
 * byť posledná.
 *
 * Štandardný vstup môže obsahovať zápisy viacerých úloh. Každý zápis obsahuje reťazec dĺžky najviac 49,
 * obsahujúci nepárny počet znamienok väčší a menší. Pre každé zadanie úlohy na vstupe vypíšte na štandardný
 * výstup jeden riadok obsahujúci reťazec zložený z bodiek (znak .) a malých písmen o (znak o). Písmeno o
 * znamená, že príslušná kocka môže byť niekedy posledná v odoberaní. Ak nemôže byť posledná, napíšte znak
 * bodky.
 *
 * Ukážka vstupu:
 * <<<<>
 * >>><<
 * >>><<<>>>>><<<>
 *
 * Výstup pre ukážkový vstup:
 * ....o
 * o...o
 * o.....o.o.....o
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

int **arr;

void evaluate(const char string[50], unsigned long len) {
    for (int j = 1; j < len; j += 2) {
        int k = j;
        for (int i = 0; k < len; i++, k++) {
            if (k == 1 && string[k] == '<') {
                arr[i][k] = 1;
            }
            else if (k == len-1 && string[k-1] == '>') {
                arr[i][k] = 1;
            }
            else if (k != 1 && k != len-1 && (string[k-1] != '<' || string[k] !='>')) {
                arr[i][k] = 1;
            }
            else if (j != 1) {
                for (int row = i+2, col = i+1; row < k && col < k; row += 2, col += 2) {
                    if (arr[i][col] == 1 && arr[col][k] == 1) {
                        arr[i][k] = 1;
                        break;
                    }
                }
                if (arr[i][k] != 1 && (string[i] != '<' || string[k+1] !='>')) {
                    arr[i][k] = 1;
                }
                else {
                    arr[i][k] = 0;
                }
            }
            else {
                arr[i][k] = 0;
            }
        }
    }
}

int main() {
    char string[50], result[50];

    for (int i = 0; i < 50; i++) {
        result[i] = '.';
    }

    while(scanf("%s", string) > 0) {
        char *num = string;
        unsigned long len = strlen(num);

        arr = (int **) calloc(len, sizeof(int *));
        for (int i = 0; i < len; i++) {
            arr[i] = (int *) calloc(len, sizeof(int));
            for (int j = 0; j < len; j++) {
                arr[i][j] = -1;
            }
        }

        if (DEBUG) {
            for (int i = 0; i < len; i++) {
                printf("%c ", string[i]);
            }
            printf("\n");
        }

        evaluate(string, len);

        if (DEBUG) {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    printf("%2d ", arr[i][j]);
                }
                printf("\n");
            }
        }

        for (int j = 1; j < len; j += 2) {
            int k = j;
            for (int i = 0; k < len; i++, k++) {
                if (arr[i][k] == 0) {
                    if (k == 1) {
                        result[0] = 'o';
                    }
                    else if (j != 1) {
                        result[k+j-1] = 'o';
                    }
                    else {
                        result[k] = 'o';
                    }
                }
            }
        }

        for (int i = 0; i < len; i++) {
            printf("%c", result[i]);
        }
        printf("\n");

        for (int i = 0; i < 50; i++) {
            string[i] = '\0';
            result[i] = '.';
        }

        for (int i = 0; i < len; i++) {
            free(arr[i]);
        }
        free(arr);
    }

    return 0;
}

/* Test 1
..o
o...o
....o
o.....o
o.....o.o.....o
o.....o.o.........o.o
o..
..o
o..
o..
 */

/* Test 2
..o
o...o
....o
o.....o
o.....o.o.....o
o.....o.o.........o.o
o..
..o
o..
o..
o................................................
o................................................
................................................o
o...............................................o
o.o.o.o.o.o.o.o..................................
................o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
................................................o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o..
o.o...o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
..o...o...o...o...o...o...o...o...o...o...o...o.o
..o...o...o...o...o...o...o...o...o...o...o...o.o
o.........o...o...o...o...o...o...o...o...o...o.o
o................................................
................................................o
o.o.....o.....o.....o.....o.....o.....o.....o....
....o.o.....o.o.....o.o.....o.o.....o.o.....o.o.o
o.o.o.......o.o.......o.o.......o.o.......o.o....
........................o.o.o.o.o.o.o.o.o.o.o.o.o
o.o.o.o.o.o.o.o.o.o.o.o.o........................
............o.o.o.o.o.o.............o.o.o.o.o.o.o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o.o.o.o.o.o.o.o.........o.o.o.o.o.o.o............
o...............o.o.o.o.o.o.o.o.................o
..o
o....
o.....o
..o
....o
o.o...o
o.o.......o
o...o.......o.o.o....
o...........o.......o..........
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.....o
o...........o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o.o.........o.o.o.o.o.o.o.o.o.o.o.o.o...o.o.o...o
o...o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o...o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o...o.o.....o...o
o.o...o.....o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o.o.o.o.o.o.o.o.o.o.o.....................o.....o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o...o
o...o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o...o.....o
o...o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o
o.........o.....o.o.o.o.o.o.o.o.o.o.o.o.o.o.....o
o.....................o...o.o...o.o.o...o.o.o.o.o
o...............o.o.o.o.o.o.o...o.o.o.o.o.o.o.o
o.....o.o.o...o.o.o.o...o.o.o.o.o.o.o.o.o...o
o...........o.o.o.o.o.o.o.o.o.o...o.o.o.o.o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o...o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.......o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.............o
o.o.o.o.o.o.o.o.o.o.o.o.o.o.............o
 */
