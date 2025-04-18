#include <stdio.h>

#define IN 10
#define OUT 20

int isWhitespace(int c) {
    return c == '\n' || c == ' ' || c == '\t';
}

int main() {
    int c;
    int lc = 0;
    int state = OUT;

    while ((c = getchar()) != EOF) {

        int c_is_whitespace = isWhitespace(c);

        if (c_is_whitespace && isWhitespace(lc)) {
            continue;
        }

        lc = c;

        /* I hate this logic but I am out of time */
        if (c_is_whitespace) {
            state = OUT;
            putchar('\n');
        } else if (state == OUT) {
            state = IN;
            putchar(c);
        } else {
            putchar(c);
        }
    }

    return '\0';
}
