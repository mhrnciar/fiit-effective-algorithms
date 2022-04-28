#include <stdio.h>

int ary[10][10], completed[10], n, cost=0;

void takeInput() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &ary[i][j]);
        }
    }
}

int least(int c) {
    int i, nc = 999;
    int min = 999, kmin;

    for(i = 0; i < n; i++) {
        if (ary[c][i] != 0 && completed[i] == 0) {
            if (ary[c][i] + ary[i][c] < min) {
                min = ary[i][0] + ary[c][i];
                kmin = ary[c][i];
                nc = i;
            }
        }
    }

    if (min != 999)
        cost += kmin;

    return nc;
}

void mincost(int city) {
    int ncity;

    completed[city] = 1;

    printf("%d--->", city+1);
    ncity = least(city);

    if (ncity == 999) {
        return;
    }

    mincost(ncity);
}

int main() {
    takeInput();

    printf("\n\nThe Path is:\n");
    mincost(0); //passing 0 because starting vertex

    printf("\n\nMinimum cost is %d\n ", cost);

    return 0;
}