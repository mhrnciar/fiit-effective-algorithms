/*
 * Malý Jakubko sa hral s binárnymi číslami. Dané je číslo v binárnom zápise, vašou úlohou je zistiť
 * na koľko najmenej častí je potrebné ho rozdeliť tak, aby každá zo vzniknutých častí predstavovala
 * binárny zápis nejakej mocniny čísla 5 (napr. 5, 25, 125) bez núl na začiatku.
 *
 * Na štandardnom vstupe je viac riadkov, na každom z nich je číslo zapísané v binárnom zápise, ktorého
 * dĺžka je najviac 50 číslic. Pre každé číslo na vstupe postupne vypíšte jeden riadok na výstup,
 * obsahujúci jedno číslo: najmenší počet časti na ktorý je potrebné zadané číslo rozdeliť tak, aby
 * vzniknuté časti každá predstavovala binárny zápis nejakej mocniny čísla 5, resp. vypíšte -1 ak sa
 * to nedá tak rozdeliť.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1
#define MAX_POWERS 22   // 5^23 has > 50 digits in binary

typedef struct node {
    int end;
    struct node *left;
    struct node *right;
} NODE;

NODE *tree;

char *int_to_binary(long long num) {
    char arr[50];
    int cnt = 0, n = 0;

    while(num){
        if(num & 1)
            arr[cnt] = '1';
        else
            arr[cnt] = '0';

        num >>= 1;
        cnt++;
    }

    char *bin = (char *) malloc(cnt * sizeof(char));
    for (int i = cnt - 1; i >= 0; i--) {
        bin[n++] = arr[i];
    }

    return bin;
}

NODE *insert(NODE *node, char num, int end) {
    if (node == NULL) {
        NODE *akt = (NODE *) malloc(sizeof(NODE));
        akt->end = end;
        akt->left = akt->right = NULL;
        return akt;
    }
    else if (num == '1') {
        node->right = insert(node->right, num, end);
    }
    else {
        node->left = insert(node->left, num, end);
    }

    return node;
}

void build_tree(char **powers) {
    int len;

    for (int i = 0; i < MAX_POWERS; i++) {
        len = strlen(powers[i]);
        for (int j = len - 1; j > 0; j--) {
            tree = insert(tree, powers[i][j-1], j-1 == 0 ? 1 : 0);
        }
    }
}

int main() {
    char string[50];
    char **powers = (char **) malloc(MAX_POWERS * sizeof(char *));
    tree = NULL;

    if (DEBUG) {
        for (int i = 0; i < MAX_POWERS; i++) {
            powers[i] = int_to_binary((long long) pow(5, i));
            printf("%f: %s\n", pow(5, i), powers[i]);
        }
    }

    NODE *root = (NODE *) malloc(sizeof(NODE));
    root->end = 1;
    root->left = root->right = NULL;
    tree = root;

    //build_tree(powers);

    while(scanf("%s", string) > 0) {
        char *num = string;
        unsigned long len = strlen(num);

    }
    return 0;
}
