/** @mainpage Guess the number program
 * Usage ./prog [OPTION]
 * Where OPTION could be
 *    [] to run program
 *    [-r] to run program with roman numbers
 *    [--help] to open help page\n"
 */
/** @page Guess the number program
 * Program guesses number from [1, 100] using binary search.
 *
 * Options:
 *  -r          Use Roman numbers instead of Arabic
 *  --help      Help for Number guesser program
 *
 */
/** @file program.c
 * Implementation
 *
 *The program asks the user to guess (enter into the console)
 *a number from 1 to 100. Then, using a binary search (dividing
 *the segment in half) and using questions to clarify the boundaries
 *of the segment, it guesses the number.
 */

#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h> 

char *roman[] = {"I","II","III","IV","V","VI","VII","VIII","IX","X",
                 "XI","XII","XIII","XIV","XV","XVI","XVII","XVIII",
                 "XIX","XX","XXI","XXII","XXIII","XXIV","XXV","XXVI",
                 "XXVII","XXVIII","XXIX","XXX","XXXI","XXXII","XXXIII",
                 "XXXIV","XXXV","XXXVI","XXXVII","XXXVIII","XXXIX","XL",
                 "XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII",
                 "XLIX","L","LI","LII","LIII","LIV","LV","LVI","LVII","LVIII",
                 "LIX","LX","LXI","LXII","LXIII","LXIV","LXV","LXVI","LXVII",
                 "LXVIII","LXIX","LXX","LXXI","LXXII","LXXIII","LXXIV","LXXV",
                 "LXXVI","LXXVII","LXXVIII","LXXIX","LXXX","LXXXI","LXXXII",
                 "LXXXIII","LXXXIV","LXXXV","LXXXVI","LXXXVII","LXXXVIII",
                 "LXXXIX","XC","XCI","XCII","XCIII","XCIV","XCV","XCVI",
                 "XCVII","XCVIII","XCIX","C"}; /**< List of roman numbers from [1, 100] */

/** Convert arabic number int @p num into roman
 *
 * @param num arabic number
 * @return corresponding roman number
 */
char *to_roman(int num) {
    return roman[num - 1];
}

/** Convert roman number char* @p num into arabic
 *
 * @param num roman number
 * @return corresponding arabic number
 */
int to_arabic(char *num) {
    for (int i = 0; i < 100; i++) {
        if (!strcmp(num, roman[i]))
            return i + 1;
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("ru", ".");
    textdomain("ru");

    bool in_roman = false;
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        printf(gettext("Usage ./prog [OPTION]\nWhere OPTION could be\n   [] to run program\n   [-r] to run program with roman numbers\n   [--help] to open help page\n"));
        return 0;
    }
    if (argc == 2 && !strcmp(argv[1], "-r"))
        in_roman = true;

    int guessed, beg = 1, end = 100;
    char roman_guessed[10];
    char c;

    if (!in_roman) {
        printf(gettext("Enter digit from 1 to 100\n"));
        scanf("%d", &guessed);
    } else {
        printf(gettext("Enter digit from I to C\n"));
        scanf("%s", roman_guessed);
        guessed = to_arabic(roman_guessed);
    }

    if (guessed > 100 || guessed < 1) {
        if (!in_roman)
            printf(gettext("From 1 to 100!!!\n"));
        else
            printf(gettext("From I to C!!!\n"));
        return 0;
    }
printf("before while\n");
    while ((end - beg) > 1) {
        if (!in_roman)
            printf(gettext("Is the guessed digit greater then %d?\n"), (end + beg) / 2);
        else
            printf(gettext("Is the guessed digit greater then %s?\n"), to_roman((end + beg) / 2));
        scanf(" %c", &c);

        if (c == gettext("y")[0])
            if ((end - beg) > 2)
                beg = (end + beg) / 2;
            else if ((end - beg) == 2)
                beg = end;
            else
                beg++;
        else if (c == gettext("n")[0])
            if ((end - beg) > 1)
                end = (end + beg) / 2;
            else
                end--;
        else
            printf(gettext("Type \'y\' or \'n\'\n"));
    }

    if (!in_roman)
        printf(gettext("You guessed %d!\n"), guessed);
    else
        printf(gettext("You guessed %s!\n"), to_roman(guessed));

    return 0;
}
