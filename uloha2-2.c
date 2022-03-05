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
 */

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1
#define MAX 1024

typedef struct node {
    int i, j;
    int remaining;
    int count;
} NODE;

NODE *stack[MAX] = {NULL};
int top = 0;

int arr[10][10] = {0};

int DFS(int n) {
    while (top != 0) {
        NODE *node = stack[top - 1];
        stack[top - 1] = NULL;
        top--;

        if (node->remaining - arr[node->i][node->j] < 0 && node->j > node->i) {
            NODE *new = (NODE *) malloc(sizeof(NODE));
            new->i = node->i;
            new->j = node->j - 1;
            new->remaining = node->remaining;
            new->count = node->count;
            stack[top] = new;
            top++;
        }
        else if (node->remaining - arr[node->i][node->j] > 0) {
            int temp_j = node->i;
            while (temp_j <= node->j - 1) {
                NODE *new = (NODE *) malloc(sizeof(NODE));
                new->i = node->i;
                new->j = temp_j;
                new->remaining = node->remaining - arr[node->i][temp_j];
                new->count = node->count + 1;
                stack[top] = new;
                top++;
                temp_j++;
            }

            if (node->i -(node->i - node->j - 1) < n) {
                NODE *new = (NODE *) malloc(sizeof(NODE));
                new->i = node->i -(node->i - node->j - 1);
                new->j = n - 1;
                new->remaining = node->remaining - arr[node->i][node->j];
                new->count = node->count + 1;
                stack[top] = new;
                top++;
            }
        }
        else if (node->remaining - arr[node->i][node->j] == 0 && node->j == n - 1) {
            return node->count;
        }
    }

    return -1;
}

int main() {
    char input[11], c;
    int result;

    while (scanf("%s %d", input, &result) > 0) {
        int numbers[10] = {0}, n = 0;
        char *p = input;

        while (p[n] != '\0') {
            c = p[n];
            numbers[n] = c - '0';
            n++;
        }

        if (n == 0 && result == 0) {
            printf("0\n");
            continue;
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

        NODE *node = (NODE *) malloc(sizeof(NODE));
        node->count = 0;
        node->remaining = result;
        node->i = 0;
        node->j = n - 1;

        stack[top] = node;
        top++;

        int plus_count = DFS(n);

        if (plus_count != -1) {
            printf("%d\n", plus_count);
        }
        else {
            printf("IMPOSSIBLE\n");
        }
        n = 0;
    }

    return 0;
}
