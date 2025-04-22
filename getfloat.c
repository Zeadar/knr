#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getfloat(double *);

int main() {
    double r;

    while (getfloat(&r)) {
        printf("\t%f\n", r);
    }

    return 0;
}

int getfloat(double *buffer) {
    double sign;
    int c, dec = 0;

    while (isspace(c = getch()) || isalpha(c));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);             //Illegal character
        return 0;
    }

    sign = c == '-' ? -1.0 : 1.0;

    if (c == '-' || c == '+')
        c = getch();

    for (*buffer = 0.0; isdigit(c); c = getch())
        *buffer = *buffer * 10 + c - '0';

    if (c != '.')
        ungetch(c);
    else {
        while (isdigit(c = getch())) {
            *buffer = *buffer * 10 + c - '0';
            ++dec;
        }

        *buffer /= pow(10, dec);
    }

    *buffer *= sign;

    if (c == EOF)
        return 0;

    return ~0;                  //Totally non-zero
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
