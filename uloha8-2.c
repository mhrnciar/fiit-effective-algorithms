/*
 * Deti prišli Jakubkovi na oslavu narodenín. Zabudol však, že deti sú prieberčivé, a nebudú jesť nič iné
 * iba svoje obľúbené jedlá, a piť iba svoje obľúbené nápoje. Jakubko však už pripravil nejaké jedlá aj
 * nápoje a nestíha spraviť iné. Pomôžte mu rozhodnúť, ktorým deťom dať ktoré jedlá a nápoje tak, aby čo
 * najviac detí jedlo svoje obľúbené jedlo a zároveň pili svoj obľúbený nápoj. Každé z pripravených jedál
 * môže byť skonzumované najviac jedným dieťaťom, a každý z pripravených nápojov môže byť vypitý tiež najviac
 * jedným dieťaťom.
 *
 * Na štandardnom vstupe je viacero scenárov. Každý scenár najskôr obsahuje tri čísla N
 * (1 <= N <= 100) počet detí, F (1 <= F <= 100) počet jedál, D (1 <= D <= 100) počet nápojov. Nasleduje N
 * riadkov, každý obsahuje najskôr dve čísla Fi (počet jedál, ktoré i-te dieťa obľubuje) a Di (počet nápojov,
 * ktoré i-te dieťa obľubuje), nasleduje Fi čísel (čísla jedál, ktoré dieťa obľubuje) a Di čísel (čísla
 * nápojov, ktoré dieťa obľubuje). Pre každý scenár na štandardný výstup vypíšte koľko najviac detí je možné
 * potešiť tak, že budú jesť nejaké svoje obľúbené jedlo a zároveň piť nejaký svoj obľúbený nápoj.
 *
 * Ukážka vstupu:
 * 4 3 3
 * 2 2 1 2 3 1
 * 2 2 2 3 1 2
 * 2 2 1 3 1 2
 * 2 1 1 3 3
 * 3 3 3
 * 2 2 1 2 1 2
 * 2 1 1 3 1
 * 2 2 2 3 1 2
 *
 * Výstup pre ukážkový vstup:
 * 3
 * 2
 */

// Ford-Fulkerson algorithm references:
// https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
// https://www.programiz.com/dsa/ford-fulkerson-algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THOUSAND 1001
#define DEBUG 0
#define FALSE 0
#define TRUE 1

typedef struct node {
    int val;
    struct node* next;
} NODE;

NODE* queue = NULL;

int capacity[THOUSAND][THOUSAND];
int SOURCE, SINK, MAX_NODES;

int min(int a1, int a2) {
    return a1 < a2 ? a1 : a2;
}

void enqueue(int val) {
    if (queue == NULL) {
        queue = (NODE *) malloc(sizeof(NODE));
        queue->val = val;
        queue->next = NULL;
        return;
    }

    NODE *new_node = (NODE *) malloc(sizeof(NODE));

    new_node->val = val;
    new_node->next = queue;
    queue = new_node;
}

int dequeue() {
    NODE *curr = queue;
    int val = queue->val;
    queue = queue->next;

    free(curr);
    return val;
}

int bfs(int *parent) {
    int visited[THOUSAND];
    memset(visited, FALSE, THOUSAND * sizeof(int));

    queue = NULL;

    enqueue(SOURCE);
    visited[0] = 1;

    while (queue != NULL) {
        int u = dequeue();

        for (int v = 0; v < MAX_NODES; v++) {
            if (visited[v] == FALSE && capacity[u][v] > 0) {
                enqueue(v);

                parent[v] = u;
                visited[v] = TRUE;

                if (v == SINK) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int ford_fulkerson() {
    int parent[THOUSAND], max_flow = 0, v, u;
    memset(parent, -1, THOUSAND * sizeof(int));

    while (bfs(parent)) {
        int path_flow = 99999;
        for (v = SINK; v != SOURCE; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }

        for (v = SINK; v != SOURCE; v = parent[v]) {
            u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int f_count, d_count, temp;
    int n, f, d;

    while (scanf("%d %d %d", &n, &f, &d) > 0) {
        // Clean up
        for (int i = 0; i < SINK; i++) {
            for (int j = 0; j < SINK; j++) {
                capacity[i][j] = 0;
            }
        }

        // Source is always the first, so its index is 0. Sink is calculated as a number of foods + number of drinks +
        // source + twice number of children, once as food and second time as drink consumers. The maximum number of
        // nodes is the number of sink + 1
        SOURCE = 0;
        SINK = n + n + f + d + 1;
        MAX_NODES = n + n + f + d + 2;

        // Source -> food - food follows directly after source, so the positions are i + 1 (1 to offset source)
        for (int i = 0; i < f; i++) {
            capacity[SOURCE][i + 1] = 1;
        }

        // Load all children data
        for (int i = 0; i < n; i++) {
            // Child -> child - create children twice, first as a food consumer, second as a drink consumer. There is
            // always only one connection, from the first node of one child, to its second node, which is located on
            // the offset of the first node + the number of children (N)
            capacity[f + i + 1][f + n + i + 1] = 1;

            scanf("%d %d", &f_count, &d_count);

            // Food -> child - foods are connected to first node of the child
            for (int j = 0; j < f_count; j++) {
                scanf("%d", &temp);
                capacity[temp][f + i + 1] = 1;
            }

            // Child -> drink - drinks are set as a connection between the second node of the child,
            // and respective drink
            for (int j = 0; j < d_count; j++) {
                scanf("%d", &temp);
                capacity[n + f + i + 1][n + n + f + temp] = 1;
            }
        }

        // Drink -> sink - drinks are located as offset of food (f), first and second children nodes (2n),
        // drink offset, and source
        for (int i = 0; i < d; i++) {
            capacity[n + n + f + i + 1][SINK] = 1;
        }

        if (DEBUG) {
            for (int i = 0; i < MAX_NODES; i++) {
                for (int j = 0; j < MAX_NODES; j++) {
                    printf("%d ", capacity[i][j]);
                }
                printf("\n");
            }
        }

        printf("%d\n", ford_fulkerson());
    }

    return 0;
}
