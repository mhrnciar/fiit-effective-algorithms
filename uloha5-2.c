/*
 * Jakubko sa hral s kockami. Na každej kocke je nakreslená šípka doľava (označujeme <) alebo šípka doprava
 * (označujeme >). Nepárny počet kociek s nejakými šípkami je rozostavených do radu vedľa seba. Jakubko sa
 * hrá nasledovnú hru, vyberie si kocku, ktorá nie je na kraji a zoberie z radu vybranú kocku a susednú kocku
 * na ktorú vybraná kocka ukazuje. Následne Jakubko kocky prisunie k sebe, aby nezostala v rade medzera.
 * Tento proces opakuje, až kým nezostane len jedna kocka. Otázka je, ktorá kocka (v pôvodnom poradí) môže
 * byť posledná.
 *
 * Štandardný vstup môže obsahovať zápisy viacerých úloh. Každý zápis obsahuje reťazec dĺžky najviac 49,
 * obsahujúci nepárny počet znamienok väčší a menší. Pre každé zadanie úlohy na vstupe vypíšte na štandardný
 * výstup jeden riadok obsahujúci reťazec zložený z bodiek (znak .) a malých písmen o (znak o). Písmeno o
 * znamená, že príslušná kocka môže byť niekedy posledná v odoberaní. Ak nemôže byť posledná, napíšte znak
 * bodky.
 *
 * Ukážka vstupu:
 * <<<<>
 * >>><<
 * >>><<<>>>>><<<>
 *
 * Výstup pre ukážkový vstup:
 * ....o
 * o...o
 * o.....o.o.....o
 */

#include <stdio.h>
#include <string.h>

#define MAX_LEN 51

// Find string in string
int find_substr(const char *str, const char *component, const int begin) {
    int c = 0, save, len_component = strlen(component), len_str = strlen(str);

    // If string is shorter than the component, or one is NULL, or the begin is larger than the length of string
    // without the length of component, return -1
    if (len_str < len_component || !len_str || !len_component || begin > len_str - len_component)
        return -1;

    // Cycle through the string and save the current position, so it can be returned to previous position after the
    // while cycle
    for (int i = begin; i <= len_str - len_component; i++) {
        save = i;

        // If the string and component equal, go through the whole component and if it's whole found in the string,
        // return the position, otherwise load the saved position and try again until the whole string is inspected
        while (str[i] == component[c]) {
            c++;
            i++;

            if (c == len_component)
                return i - len_component;
        }

        c = 0;
        i = save;
    }

    // If the component has not been found in string, return -1
    return -1;
}

// Determine whether there are only left-facing characters <, or only right-facing characters >, or both. In case there
// are both, return 0, if there are only < return 1, otherwise return 2
int str_type(char *str) {
    int facing_left = 0, facing_right = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '<')
            facing_left = 1;
        else
            facing_right = 1;

        if (facing_left && facing_right)
            return 0;
    }

    return facing_left ? 1 : 2;
}


int can_finish(char *str, int right, int endrem) {
    char remaining[MAX_LEN / 2] = {};
    int len = strlen(str), count = 0;

    // If len is 0 or not positive, return 1
    if (!len)
        return 1;

    // Cycle through the string and always try to first find the <> component, which denotes the place where will
    // be 'o'. If no <> component has been found, set find to length of the string and copy the substring to temp
    for (int i = 0; i < len;) {
        char temp[MAX_LEN] = {};
        int prev = i;

        int find = find_substr(str, "<>", i) + 1;

        if (!find)
            find = len;

        strncpy(temp, str + prev, find - prev);
        i = find;

        char len_temp = strlen(temp), type_temp = str_type(temp);

        // If the end hasn't been removed, and we are in the right string
        if (!endrem && right && find == len) {
            // If there are only left-facing characters < and the length of temp is odd, add one < to val remaining,
            // if the length is even, add two
            if (type_temp == 1) {
                if (len_temp % 2)
                    remaining[count++] = '<';
                else {
                    remaining[count++] = '<';
                    remaining[count++] = '<';
                }
            }

                // Otherwise, we want to keep the >, but only if the length of temp is odd, otherwise remove end
            else {
                if (len_temp % 2)
                    remaining[count++] = '>';
                else
                    endrem = 1;
            }

            continue;
        }

        // If the end hasn't been removed and we are in the left string
        else if (!endrem && !right && !prev) {
            // Similar to code above, if there are only right-facing characters >, add to val remaining >
            if (type_temp == 2) {
                if (len_temp % 2)
                    remaining[count++] = '>';
                else {
                    remaining[count++] = '>';
                    remaining[count++] = '>';
                }
            }

                // Otherwise, we want to keep the <, but only if the length of temp is odd, otherwise remove end
            else {
                if (len_temp % 2)
                    remaining[count++] = '<';
                else
                    endrem = 1;
            }

            continue;
        }

        // If the length of temp is odd, we are going to count which character stays by calculating balance between,
        // characters: left-facing is -1 and right-facing is +1
        if (len_temp % 2) {
            int char_balance = 0;

            for (int c = 0; c < len_temp; c++) {
                // The last character is < which we want to get rid of and the type is either mixed or left-facing
                if (count && remaining[count - 1] == '<' && (!type_temp || type_temp == 1)) {
                    if (count == 1 && !endrem)
                        endrem = 1;

                    // Reduce the position in remaining and remove the character
                    count--;
                    remaining[count] = 0;
                    break;
                }

                // Nothing is on the left, so we keep the character
                if (!count && !type_temp) {
                    char_balance = 1;
                    break;
                }

                // We are in the left string and the selected character in temp is left-facing -> set negative balance
                if (!right && prev && temp[c] == '<') {
                    char_balance = -1;
                    break;
                }

                    // We are in the right string and the selected character in temp is right-facing -> set positive balance
                else if (right && find != len && temp[c] == '>') {
                    char_balance = 1;
                    break;
                }

                // Reduce the balance if the character is left-facing, or add to it if the character is right-facing
                char_balance += (temp[c] == '<') ? -1 : 1;
            }

            // If the balance is not 0 (there is different number of left-facing and right-facing characters), add to
            // remaining character according to the negative or positive balance
            if (char_balance)
                remaining[count++] = (char_balance < 0) ? '<' : '>';
        }
    }

    // If the length of remaining is 2, return true if the characters are not <> AND if we are in the right string and
    // the end has been removed and the first character isn't < AND if we are in the left string and the end has been
    // removed and the second character isn't >
    if (strlen(remaining) == 2)
        return !(remaining[0] == '<' && remaining[1] == '>') &&
               !(right && !endrem && remaining[0] == '<') &&
               !(!right && !endrem && remaining[1] == '>');

    // If the length of remaining is odd, return 0
    if (strlen(remaining) % 2)
        return 0;

    // Otherwise, recursively continue
    return can_finish(remaining, right, endrem);
}

int main() {
    char str[MAX_LEN], left[MAX_LEN] = {}, right[MAX_LEN] = {}, final[MAX_LEN] = {};

    // Read string
    while (scanf("%s", str) > 0) {
        unsigned long len = strlen(str);

        for (int i = 0; i < len; i += 2) {
            // Copy string to left and right. To left copy string iteratively, as it is, and to right copy the
            // remaining part that isn't in the left
            strncpy(left, str, i);
            strncpy(right, str + i + 1, len - i);

            // Call the can_finish function on the left and right substrings and if the function returns 1 (true), set
            // the current character to 'o', otherwise set it to '.'
            if (can_finish(left, 0, 0) && can_finish(right, 1, 0))
                final[i] = 'o';
            else
                final[i] = '.';

            // The characters on even positions will always be '.'
            if (i < len - 1)
                final[i + 1] = '.';
        }

        // Print the resulting string
        printf("%s\n", final);

        // Clean up
        for (int i = 0; i < MAX_LEN; i++) {
            left[i] = '\0';
            right[i] = '\0';
            final[i] = '\0';
        }
    }

    return 0;
}
