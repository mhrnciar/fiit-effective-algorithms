//
// Created by Matej Hrnčiar on 24/05/2022.
//

#include <stdio.h>

int kuk = 0;

int f(int a, int b, int c) {
    int i,r=0;
    kuk++;

    if (b>=c) return a;
    for(i=b;i<c;i++)
        r = r + f(a,b,i) + f(a,i+1,c);
    return r/(c-b);
}

int a[] = {1, 2, 3, 2, 1};
int p1[] = {-1, -1, -1, -1, -1};
int p2[] = {-1, -1, -1, -1, -1};

int h1(int l, int r) {
    if (l == r) return l;

    int mi, m = 999999;

    for (int i = l; i <= r; i++)
        if (a[i] < m) {
            m = a[i];
            mi = i;
        }

    if (mi > l)
        p1[h1(l, mi - 1)] = mi;
    
    if (mi < r)
        p1[h1(mi + 1, r)] = mi;

    return mi;
}

void h2() {
    for (int i = 1; i < 6; i++) {
        int j, oj;

        for(j = oj = i - 1; p2[j] != -1 && a[i] < a[j];) {
            oj = j;
            j = p2[j];
        }
        if (a[i] < a[j]) {
            p2[j] = i;
        }
        else {
            if (oj != j)
                p2[oj] = i;
            p2[i] = j;
        }
    }
}

int loop(int n) {
    int sum = 0;

    for (int i = n; i > 0; i--) {
        for (int j = 1; j < i; j *= 2) {
            for (int k = 0; k < j; ++k) {
                sum++;
            }
        }
    }

    return sum;
}

int main() {
    //f(3, 6, 2020);
    //printf("%d", kuk);

    /*
    h1(0, 5);
    h2();

    for (int i = 0; i < 6; i++) {
        printf("%d ", p1[i]);
    }
    printf("\n");
    for (int i = 0; i < 6; i++) {
        printf("%d ", p2[i]);
    }
*/

    printf("%d\n", loop(1000));
    return 0;
}
