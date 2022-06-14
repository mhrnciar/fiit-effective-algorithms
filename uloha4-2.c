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
 * Poznámka: Kľúčom K riešeniu je uvažovanie, aké znaky dosadiť za ? vo vstupe. Uvedomme si, že za každý
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
#include <string.h>

#define MAX_LEN 51
#define DEBUG 0

void evaluate(char str[MAX_LEN], unsigned long len, int a_like, int p_like) {
    int a_count = 0, p_count = 0, like = 0;

    int i = 0, end = 0;
    char pom1, pom2;

    // Search for dislike
    while (!end && i < len) {
        // Go through list until the '?' is encountered
        if (str[i] == '?') {
            // If it's at the beginning, evaluate the next character, and set the current to opposite type. If the
            // character is '?', cycle until a vowel or consonant is encountered and set the previous character the
            // opposite type from the current one
            if (i == 0) {
                pom1 = str[i + 1];

                if (pom1 == 'A') {
                    str[i] = 'P';
                }

                if (pom1 == 'P') {
                    str[i] = 'A';
                }

                if (pom1 == '?') {
                    while (str[i] == '?' && i < len) {
                        i++;
                    }

                    if (str[i] == 'A') {
                        str[i - 1] = 'P';
                    }

                    if (str[i] == 'P') {
                        str[i - 1] = 'A';
                    }
                }
            }

            // If it's at the end, set the previous character to opposite type from the current one
            else if (i == len - 1) {
                    if (str[i - 1] == 'A') {
                        str[i] = 'P';
                    }

                    if (str[i - 1] == 'P') {
                        str[i] = 'A';
                    }
                }

            // If it's somewhere in the middle, take previous and next characters from the current one
            else {
                pom1 = str[i - 1];
                pom2 = str[i + 1];

                // If both are vowels, set current to consonant
                if (pom1 == 'A' && pom2 == 'A') {
                    str[i] = 'P';
                }

                // If previous is vowel and next is consonant, and the number of vowels in row is 2, set it to
                // consonant, otherwise set it to vowel
                if (pom1 == 'A' && pom2 == 'P') {
                    if (a_count == 2) {
                        str[i] = 'P';
                    }
                    else {
                        str[i] = 'A';
                    }
                }

                // If both are consonants, set current to vowel
                if (pom1 == 'P' && pom2 == 'P') {
                    str[i] = 'A';
                }

                // If previous is consonant and next is vowel, and the number of consonants in row is 4, set it to
                // vowel, otherwise set it to consonant
                if (pom1 == 'P' && pom2 == 'A') {
                    if (p_count == 4) {
                        str[i] = 'A';
                    }
                    else {
                        str[i] = 'P';
                    }
                }

                // If the next one is unknown, cycle until a letter is found, set the previous character to the
                // opposite type from the current one, and reset counts
                if (pom2 == '?') {
                    while (str[i] == '?' && i < len) {
                        i++;
                    }
                    if (str[i] == 'A') {
                        str[i - 1] = 'P';
                    }
                    if (str[i] == 'P') {
                        str[i - 1] = 'A';
                    }

                    a_count = 0;
                    p_count = 0;
                }
            }
        }

        // If the end is encountered, end the cycle
        if (i == len) {
            end = 1;
            continue;
        }

        // As before, count number of consecutive vowels or consonants and if there is at least 3 vowels, or 5
        // consonants in a row, add to like and end the cycle
        if (str[i] == 'A') {
            a_count++;
            p_count = 0;
        }
        else {
            p_count++;
            a_count = 0;
        }

        if (a_count == 3) {
            like++;
            end = 1;
        }
        if (p_count == 5) {
            like++;
            end = 1;
        }

        i++;
    }

    // If there is at least one previous like from replaced '?' on both types (vowels, consonants), but no likes from
    // evaluation, result is unknown
    if (a_like > 0 && p_like > 0 && like == 0) {
        printf("neviem\n");
        return;
    }

    // If there are likes from this evaluation as well as from replaced '?', result is like
    if (a_like > 0 && p_like > 0 && like > 0) {
        printf("paci\n");
        return;
    }
}

void replace_unknown(char str[MAX_LEN], unsigned long len, int like, int a_count, int p_count) {
    int aa_count = 0, pa_count = 0, ap_count = 0, pp_count = 0;
    int a_like = 0, p_like = 0;

    if (DEBUG) {
        printf("Original string: ");
        for (int i = 0; i < len; i++) {
            printf("%c ", str[i]);
        }
        printf("\n");
    }

    /*
     * Now, try replacing all '?' with A, then with P, and try to find if there are some strings that will satisfy
     * the like conditions (3 vowels or 5 consonants)
     */
    if (DEBUG) printf("A replacement: ");

    for (int i = 0; i < len; i++) {
        if (str[i] == '?' || str[i] == 'A') {
            if (DEBUG) printf("A ");
            aa_count++;
            pa_count = 0;
        }
        else {
            if (DEBUG) printf("P ");
            pa_count++;
            aa_count = 0;
        }

        if (aa_count == 3) {
            a_like++;
            break;
        }

        if (pa_count == 5) {
            a_like++;
            break;
        }
    }

    if (DEBUG) printf("\nP replacement: ");

    for (int i = 0; i < len; i++) {
        if (str[i] == '?' || str[i] == 'P') {
            if (DEBUG) printf("P ");
            pp_count++;
            ap_count = 0;
        }
        else {
            if (DEBUG) printf("A ");
            ap_count++;
            pp_count = 0;
        }

        if (ap_count == 3) {
            p_like++;
            break;
        }

        if (pp_count == 5) {
            p_like++;
            break;
        }
    }

    if (DEBUG) printf("\n");

    // If no such liked strings have been found, the result is always dislike
    if (a_like == 0 && p_like == 0) {
        printf("nepaci\n");
        return;
    }
    // If there is satisfied only one type, the result is unknown
    else if ((a_like == 0 && p_like > 0) || (a_like > 0 && p_like == 0)) {
        printf("neviem\n");
        return;
    }

    evaluate(str, len, a_like, p_like);
}

int main() {
    char str[MAX_LEN];

    while (scanf("%s", str) > 0) {
        int a_count = 0, p_count = 0, u_count = 0, like = 0;
        unsigned long len = strlen(str);

        // If string is too short to be liked
        if (len < 3) {
            printf("nepaci\n");
            continue;
        }

        /*
         * Iterating through the string and counting consecutive vowels, encoded as A, or consonants, encoded as P.
         * If there are more than 3 vowels or 5 consonants in row, add to like u_count. The a_count and p_count is reset
         * when comes a letter of different type, or if when '?' is read
         */
        for (int i = 0; i < len; i++) {
            if (str[i] == '?') {
                u_count++;
                a_count = 0;
                p_count = 0;
                continue;
            }
            else if (str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
                str[i] = 'A';
                a_count++;
                p_count = 0;
            }
            else {
                str[i] = 'P';
                p_count++;
                a_count = 0;
            }

            if (a_count == 3) {
                like++;
                break;
            }

            if (p_count == 5) {
                like++;
                break;
            }
        }

        // If some liked string has been found
        if (like > 0) {
            printf("paci\n");
            continue;
        }
        // If the '?' count is the same as the length of string and there are at least 3 '?', the result is unknown
        else if (u_count == len && u_count >= 3) {
            printf("neviem\n");
            continue;
        }
        // If there are no liked strings, but also no '?', the result is dislike
        else if (u_count == 0 && like == 0) {
            printf("nepaci\n");
            continue;
        }
        else {
            replace_unknown(str, len, like, a_count, p_count);
        }
    }

    return 0;
}
