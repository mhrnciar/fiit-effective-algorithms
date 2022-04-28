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

#define DEBUG 0

// Descending ordering function
int cmpfunc (const void *a, const void *b) {
    return ( *(int *) b - *(int *) a );
}

int main() {
    int n, m;

    while (scanf("%d %d", &n, &m) > 0) {
        int *people = (int *) malloc(n * sizeof(int));
        int *seats = (int *) malloc(m * sizeof(int));
        int max_people = 0, temp, total_seats = 0, total_people = 0, fail = 0;

        // Count max number of people in circle while loading it to array, and add to total
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

        // If there are more people than seats, or some circle has more people than is the number of tables,
        // the seating is impossible to satisfy, return 0
        if (total_people > total_seats || max_people > m) {
            printf("0\n");
        }
        else {
            // Sort array of circles in descending order
            qsort(people, n, sizeof(int), cmpfunc);

            // Print sorted array
            if (DEBUG) {
                for (int i = 0; i < n; i++) {
                    printf("%d ", people[i]);
                }
                printf("\n");
            }

            /*
             * Cycle through circles and remove from each table 1 seat. Because the tables are ordered by number of
             * seats, this greedy algorithm is correct, since it will always remove starting from the biggest tables
             * and the smallest tables at the end will reduce the number of seats only if the circle is big enough to
             * reach the table. Circles are also ordered, so as there is fewer tables, there is also fewer people to
             * seat. If seats are all taken and we still have a person to seat, the seating is impossible to satisfy,
             * and 0 is returned
             */
            for (int i = 0; i < n; i++) {
                // Sorting seats after every iteration avoids cases when some table is not fully occupied and could
                // incorrectly fail the test
                qsort(seats, m, sizeof(int), cmpfunc);
                temp = people[i];

                for (int j = 0; j < temp; j++) {
                    if (seats[j] <= 0) {
                        fail = 1;
                        break;
                    }

                    seats[j] -= 1;
                }

                if (fail == 1)
                    break;
            }

            if (fail != 1)
                printf("1\n");
            else
                printf("0\n");
        }

        free(people);
        free(seats);
    }

    return 0;
}
