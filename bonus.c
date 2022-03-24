#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

void palindromes() {
    int N;
    char s[1000];

    scanf("%d %s", &N, s);
    int flag = 1;
    int a = 0;
    int l = strlen(s);

    while (l > a) {
        if (s[a++] != s[l--]) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) {
        printf("%s nie je palindrom", s);
    } else {
        printf("%s je palindrom", s);
    }
}

void histogram() {
    int arr[1000], histogram[1000];
    int size, i, j, ctr;

    scanf("%d", &size);
    for(i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
        histogram[i] = -1;
    }

    for(i = 0; i < size; i++) {
        ctr = 1;
        for(j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                ctr++;
                histogram[j] = 0;
            }
        }

        if(histogram[i] != 0) {
            histogram[i] = ctr;
        }
    }

    printf("Frekvencia prvkov v poli: \n");

    for(i = 0;  i < size; i++) {
        if(histogram[i] != 0) {
            printf("%d - %dx", arr[i], histogram[i]);
            if (i < size - 1) printf(", ");
        }
    }
}

void counting_sort() {
    int size;
    int array[MAX], output[MAX], count[MAX];

    scanf("%d", &size);
    for(int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) max = array[i];
    }

    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

void radix_sort() {
    int size, array[MAX], pole[MAX];

    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    int max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    int pocetCifier = 0, delitel = 1, cifra = 0, pomocna = 0;
    int histogram[10];

    while (max != 0) {
        max /= 10;
        pocetCifier++;
    }

    for (int j = pocetCifier; j > 0; j--) {
        for (int i = 0; i < 10; i++) {
            histogram[i] = 0;
        }

        for (int i = 0; i < size; i++) {
            pomocna = array[i] / delitel;
            cifra = pomocna % 10;
            histogram[cifra]++;
        }

        for (int i = 1; i < 10; i++) {
            histogram[i] += histogram[i - 1];
        }

        for (int i = size - 1; i >= 0; i--) {
            pomocna = array[i] / delitel;
            cifra = pomocna % 10;
            pole[histogram[cifra] - 1] = array[i];
            histogram[cifra]--;
        }

        for (int i = 0; i < size; i++) {
            array[i] = pole[i];
        }
        delitel *= 10;
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

void closest_pair() {
    int size, array[MAX];

    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    int i, j, sum, minSum, first, second;
    first = array[0];
    second = array[1];
    minSum = first + second;

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            sum = abs(0 - (array[i] + array[j]));

            if (sum < minSum) {
                minSum = sum;
                first = array[i];
                second = array[j];
            }
        }
    }

    printf("Dvojica prvkov so suctom najblizim k cislu 0 je: \n");
    printf("[%d, %d]\n", first, second);
}

int main() {
    palindromes();
    histogram();
    counting_sort();
    radix_sort();
    closest_pair();
}