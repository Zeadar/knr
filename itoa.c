#include <stdio.h>
#include <limits.h>
#include "libkalle.c"

// void itoa(int n, char s[]);

int main() {
    char buffer[1024];
    char bits[1024];

    itoa(INT_MIN, buffer);
    printf("%s\n", buffer);

    /* itoa(INT_MIN + 1, buffer);
       printf("%s\n", buffer); */

    /* int min = -INT_MIN;
       formatbytes(bits, &min, sizeof(min));
       printf("%s\n", bits); */

    signed char a = 0b01111111;

    signed char b = 0b10000000;

    printf("%d %d\n", a, b);


    return 0;
}

/* void itoa(int n, char s[]) {
    long i, sign, nn;
    i = 0;
    nn = n;

    if ((sign = nn) < 0)
        nn = -nn;

    do {
        s[i++] = nn % 10 + '0';
    } while ((nn /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s, i);
} */
