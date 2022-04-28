/*
 * Malý Jakubko sa hral s binárnymi číslami. Dané je číslo v binárnom zápise, vašou úlohou je zistiť
 * na koľko najmenej častí je potrebné ho rozdeliť tak, aby každá zo vzniknutých častí predstavovala
 * binárny zápis nejakej mocniny čísla 5 (napr. 5, 25, 125) bez núl na začiatku.
 *
 * Na štandardnom vstupe je viac riadkov, na každom z nich je číslo zapísané v binárnom zápise, ktorého
 * dĺžka je najviac 50 číslic. Pre každé číslo na vstupe postupne vypíšte jeden riadok na výstup,
 * obsahujúci jedno číslo: najmenší počet časti, na ktorý je potrebné zadané číslo rozdeliť tak, aby
 * vzniknuté časti každá predstavovala binárny zápis nejakej mocniny čísla 5, resp. vypíšte -1 ak sa
 * to nedá tak rozdeliť.
 *
 * Ukážka vstupu:
 * 101101101
 * 0000
 *
 * Výstup pre ukážkový vstup:
 * 3
 * -1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

// Check if number is a power of 5
int is_power(long long n) {
    if (n < 125)
        return (n == 1 || n == 5 || n == 25);

    if (n % 125 != 0)
        return 0;
    else
        return is_power(n / 125);
}

// Change binary string to number
long long binary_to_long (const char *s, int front, int back) {
    long long ans = 0;
    for (int i = front; i < back; i++) {
        ans = (ans << 1) + (s[i] - '0');
    }
    return ans;
}

int min_cuts(char *s, unsigned long n) {
    int *arr = (int *) calloc (n + 1, sizeof(int));
    for (int i = 1; i < n + 1; i++) {
        arr[i] = 1000;
    }

    for (int i = 1; i <= n; i++) {
        // Remove leading 0s
        if (s[i - 1] == '0')
            continue;

        for (int j = 0; j < i; j++) {
            // Remove leading 0s
            if (s[j] == '0')
                continue;

            long long num = binary_to_long(s, j, i);
            if (!is_power(num))
                continue;

            // Save the number in array, if it's smaller than arbitrary value
            arr[i] = arr[i] < arr[j] + 1 ? arr[i] : arr[j] + 1;
        }
    }
    // Return result if found, otherwise return -1
    return ((arr[n] < n + 1) ? arr[n] : -1);
}

int main() {
    char string[100];

    while(scanf("%s", string) > 0) {
        char *num = string;
        unsigned long len = strlen(num);
        printf("%d\n", min_cuts(num, len));
    }

    return 0;
}
