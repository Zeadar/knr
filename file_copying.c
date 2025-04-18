#include <stdio.h>

void copy() {
    int c;
    int r;

    do {
        c = getchar();
        r = c != EOF;

        putchar(c);
    } while (r);

    printf("%d\n", r);
}

void character_counting() {
    /* int c;
       long nc = 0;

       do {
       c = getchar();
       ++nc;
       } while (c != EOF);

       printf("%ld\n", nc); */

    double nc;
    for (nc = 0; getchar() != EOF; ++nc);
    printf("%.0f\n", nc);
}

void newline_counting() {
    int nl, s, c;
    nl = 0;
    s = 0;

    do {
        c = getchar();
        if (c == '\n') {
            ++nl;
        }
        if (c == ' ') {
            ++s;
        }
    } while (c != EOF);

    printf("%d\n%d\n", nl, s);
}

void replace_blank() {
    int c = 0;
    int lc = 0;

    do {
        c = getchar();

        if (c != ' ' || lc != ' ') {
            putchar(c);
        }

        lc = c;
    } while (c != EOF);
}

int main() {
    /* copy(); */
    /* character_counting(); */
    /* newline_counting(); */
    replace_blank();
    return 0;
}
