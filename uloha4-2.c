/*
 * Jakubko sa začal učiť cudzie jazyky. Páči sa mu keď objaví nejaké nové komplikované slovo, ktoré obsahuje
 * aspoň 3 samohlásky za sebou, alebo 5 spoluhlások za sebou. Rozhodol sa, že sa pôjde zdokonaliť v cudzích
 * jazykoch na výlet do zahraničia. Pomôžte mu naplánovať trasu výletu tak, aby mal príležitosť vidieť čo
 * najviac komplikovaných slov. Zohnali ste si fotky viacerých miest, ktoré by Jakubko mohol navštíviť.
 * Na vstupe je niekoľko cudzích slov, ktoré vidíte na fotkách, každé na samostatnom riadku. Niektoré slová
 * však nevidieť celé, lebo vo výhľade niečo prekáža. Každé slovo môže pozostávať z veľkých písmen anglickej
 * abecedy a otáznikov, ktoré vyjadrujú, že na fotke nevidieť dané písmeno slova. Maximálna dĺžka slova je
 * 50 znakov.
 *
 * Na výstup vypíšte paci ak sa Jakubkovi dané slovo určite bude páčiť, nepaci ak sa mu určite nebude páčiť
 * a neviem ak sa to nedá s istotou určiť.
 * Poznámka: Kľúčom k riešeniu je uvažovanie, aké znaky dosadiť za ? vo vstupe. Uvedomme si, že za každý
 * otáznik môžeme dosadiť alebo samohlásku alebo spoluhlásku, no ale potom vzhľadom na okolité písmenká je
 * možné, že už nutne vznikne postupnosť troch samohlások alebo piatich spoluhlások, a teda sa takéto cudzie
 * slovo bude Jakubkovi určite páčiť. Niekedy to nemusí byť jednoznačné (neviem), alebo sa to určite nedá
 * takto dosadiť (nepaci).
 *
 * Ukážka vstupu:
 * ZPRPR
 * TEAP
 * ???
 *
 * Výstup pre ukážkový vstup:
 * paci
 * nepaci
 * neviem
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define MAX_LEN 51

int evaluate(const int *encoded, unsigned long len) {
    int *temp = (int *) malloc(len * sizeof(int));
    int a_count = 0, a_max = 0, p_count = 0, p_max = 0;

    for (int i = 0; i < len; i++) {
        if (encoded[i] != 2) {
            temp[i] = encoded[i];
        } else {
            temp[i] = 0;
        }
    }

    for (int i = 0; i < len; i++) {
        if (encoded[i] != 2) {
            temp[i] = encoded[i];
        } else {
            temp[i] = 1;
        }
    }

    return len;
}

int main() {
    int encoded[MAX_LEN], i = 0, end = 0;
    int a_count = 0, p_count = 0, q_count = 0, a_max = 0, p_max = 0;
    char c;

    while (scanf("%c", &c) > 0) {
        switch (c) {
            case 'A': case 'E': case 'I': case 'O': case 'U': case 'Y':
                encoded[i] = 1;
                a_count++;
                a_max = a_max < a_count ? a_count : a_max;
                p_count = 0;
                break;
            case '?':
                encoded[i] = 2;
                q_count++;
                break;
            case '\n':
                end = 1;
                break;
            default:
                encoded[i] = 0;
                p_count++;
                p_max = p_max < p_count ? p_count : p_max;
                a_count = 0;
                break;
        }
        i++;

        if (end) {
            i--;
            if (DEBUG) {
                for (int j = 0; j < i; j++) {
                    printf("%d ", encoded[j]);
                }
                printf("\n");
            }

            if (a_max >= 3 || p_max >= 5) {
                printf("paci\n");
            } else {
                int result = evaluate(encoded, i);
            }

            end = 0;
            p_max = p_count = a_max = a_count = 0;
            i = 0;
        }
    }

    return 0;
}