#include <stdio.h>
#include <libintl.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("ru", ".");
    textdomain("ru");

    int guessed, beg = 1, end = 100;
    char c;
    printf(gettext("Enter digit from 1 to 100\n"));
    scanf("%d", &guessed);

    if (guessed > 100 || guessed < 1) {
        printf("From 1 to 100!!!\n");
        return 0;
    }

    while ((end - beg) > 1) {
        printf(gettext("Is the guessed digit greater then %d?\n"), (end + beg) / 2);
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

    printf(gettext("You guessed %d!\n"), guessed);

    return 0;
}
