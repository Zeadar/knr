#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getint(int *);

int main() {
    int d, r;

    while ((r = (getint(&d)) != EOF)) {
        printf("\t%d\n", d);
    }

    return 0;
}

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);             //is not a digit
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + c - '0';

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

#define BUFEMPTY -1000
int getchbuf = BUFEMPTY;

int getch(void) {
    if (getchbuf == BUFEMPTY) {
        return getchar();
    } else {
        int r = getchbuf;
        getchbuf = BUFEMPTY;
        return r;
    }
}

void ungetch(int c) {
    getchbuf = c;
}
