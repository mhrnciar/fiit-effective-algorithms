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
#define DEBUG 1
#define MAX 1024

typedef struct node {
    int i, j;
    int remaining;
    int count;
} NODE;

NODE *stack[MAX] = {NULL};
int top = 0;

long arr[10][10] = {0};

int DFS(int n) {
    // While stack isn't empty, pop the node at the top
    while (top != 0) {
        NODE *node = stack[top - 1];
        top--;

        // If number in array is too large, move to the left
        if (node->remaining - arr[node->i][node->j] < 0 && arr[node->i][node->j] != 0) {
            NODE *new = (NODE *) malloc(sizeof(NODE));
            new->i = node->i;
            new->j = node->j - 1;
            new->remaining = node->remaining;
            new->count = node->count;
            stack[top] = new;
            top++;
        }
        // If number in array is smaller, make new nodes from all numbers left from selected number
        // and add new node with remaining amount reduced by the selected number
        else if (node->remaining - arr[node->i][node->j] > 0 || (node->remaining - arr[node->i][node->j] == 0 && node->j != n - 1)) {
            int temp_j = node->i;
            while (temp_j <= node->j - 1) {
                NODE *new = (NODE *) malloc(sizeof(NODE));
                new->i = node->i;
                new->j = temp_j;
                new->remaining = node->remaining;
                new->count = node->count;
                stack[top] = new;
                top++;
                temp_j++;
            }

            // Calculate how many rows to descend
            int diff = 0, temp = arr[node->i][node->j];
            if (temp == 10) {
                diff = 1;
            }
            else {
                do {
                    temp /= 10;
                    diff++;
                } while (temp > 0);
            }

            // If the calculated row doesn't overflow the array, make new node
            if (node->i + diff < n) {
                NODE *new = (NODE *) malloc(sizeof(NODE));
                new->i = node->i + diff;
                new->j = n - 1;
                new->remaining = node->remaining - arr[node->i][node->j];
                new->count = node->count + 1;
                stack[top] = new;
                top++;
            }
        }
        // If the remaining amount is 0 and we are at the end of array, return count of plus signs
        else if (node->remaining - arr[node->i][node->j] == 0 && node->j == n - 1) {
            return node->count;
        }
        free(node);
    }

    return -1;
}

int main() {
    char input[11], c;
    int result;

    while (scanf("%s %d", input, &result) > 0) {
        int numbers[10] = {0}, n = 0;
        char *p = input;

        // Separate digits
        while (p[n] != '\0') {
            c = p[n];
            numbers[n] = c - '0';
            n++;
        }

        // If there is no input, return 0
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

        // Fill DP grid with numbers to which is in every column appended another number
        int k = 0;
        for (int i = 0; i < n; i++) {
            // If number is 0, skip
            if (numbers[i] == 0) {
                continue;
            }
            for (int j = i; j < n; j++) {
                if (i == 0 && j == 0) {
                    arr[0][0] = numbers[0];
                    continue;
                }
                arr[k][j] = arr[k][j-1] * 10 + numbers[j];
            }
            k++;
        }

        if (DEBUG) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%10ld\t", arr[i][j]);
                }
                printf("\n");
            }
        }

        // Create first node and add it to stack
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

        // Clean up
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = 0;
            }
        }

        top = 0;
    }

    return 0;
}

/*
99999 45
1110 3
0123456789 45
99999 100
382834 100
9230560001 71
0000000000 0
111 3
1111111111 10
1212121212 15
1213121712 21
0123456789 81
8833614925 100
0525222922 93
3769558148 99
1210102121 100
0220120200 63
0000000001 1
1000000000 1
1000000001 2
1000000001 11
1001098 100
99999 100
382834 100
1110 3
1 1
 */