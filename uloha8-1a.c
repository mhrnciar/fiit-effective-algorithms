/*
 * Jakubko oslavuje narodeniny a na oslavu chce pozvať všetkých svojich kamarátov zo všetkých krúžkov, ktoré
 * navštevuje. Kamarátov chce usadiť k stolom tak, aby sa nestalo, že pri jednom stole sedia dvaja (alebo
 * viacerí) kamaráti z rovnakého krúžku. Pomôžte Jakubkovi rozhodnúť, či také usadenie všetkých kamarátov k
 * stolom existuje.
 *
 * Na štandardnom vstupe bude viacero scenárov za sebou. Každý scenár obsahuje najskôr dve čísla N
 * (1 <= N <= 100) počet krúžkov, ktoré Jakubko navštevuje, a M (1 <= M <= 100) počet stolov, ktoré má
 * Jakubko na oslave k dispozícií. Nasleduje N čísel Ni (1 <= Ni <= 100) počet kamarátov z i-teho krúžku,
 * a M čísel Mj (2 <= Mj <= 100) počet miest pri j-tom stole. Jakubko pri stole nesedí. Pre každý scenár na
 * štandardný výstup vypíšte 1, ak také rozsadenie všetkých kamarátov k stolom existuje, inak vypíšte 0.
 *
 * Ukážka vstupu:
 * 4 5
 * 4 5 3 5
 * 3 5 2 6 4
 * 4 5
 * 4 5 3 5
 * 3 5 2 6 3
 *
 * Výstup pre ukážkový vstup:
 * 1
 * 0
 */

#include <stdio.h>
#include <stdlib.h>

#define A 0
#define B 1
#define C 2
#define MAX_SIZE 100
#define O 1000000000

int n;
int capacity[MAX_SIZE][MAX_SIZE];
int flow[MAX_SIZE][MAX_SIZE];
int color[MAX_SIZE];
int pred[MAX_SIZE];

int min(int x, int y) {
    return x < y ? x : y;
}

int head, tail;
int q[MAX_SIZE + 2];

void enqueue(int x) {
    q[tail] = x;
    tail++;
    color[x] = B;
}

int dequeue() {
    int x = q[head];
    head++;
    color[x] = C;
    return x;
}

// Using BFS as a searching algorithm
int bfs(int start, int target) {
    int u, v;
    for (u = 0; u < n; u++) {
        color[u] = A;
    }
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head != tail) {
        u = dequeue();
        for (v = 0; v < n; v++) {
            if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
    return color[target] == C;
}

// Applying ford-fulkerson algorithm
int fordFulkerson(int source, int sink) {
    int i, j, u;
    int max_flow = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flow[i][j] = 0;
        }
    }

    // Updating the residual values of edges
    while (bfs(source, sink)) {
        int increment = O;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
        }
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }
        // Adding the path flows
        max_flow += increment;
    }
    return max_flow;
}

int main() {
    int n, m;

    while (scanf("%d %d", &n, &m) > 0) {

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            capacity[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &people[i]);
        max_people = people[i] > max_people ? people[i] : max_people;
        total_people += people[i];
    }

    // If number of seats is more than number of circles, the seats can be reduced, add to total
    for (int i = 0; i < m; i++) {
        scanf("%d", &temp);
        seats[i] = temp < n ? temp : n;
        total_seats += seats[i];
    }

    n = 6;

    capacity[0][1] = 8;
    capacity[0][4] = 3;
    capacity[1][2] = 9;
    capacity[2][4] = 7;
    capacity[2][5] = 2;
    capacity[3][5] = 5;
    capacity[4][2] = 7;
    capacity[4][3] = 4;

    int s = 0, t = 5;
    printf("Max Flow: %d\n", fordFulkerson(s, t));
}