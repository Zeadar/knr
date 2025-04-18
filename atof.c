#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "libkalle.c"

double atof(char s[]);

int main() {
    char buffer[1024];
    double result;

    while (readline(buffer, 1024)) {
        result = atof(buffer);
        printf("%f\n", result);
    }

    return 0;
}

double atof(char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); ++i);

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        ++i;

    for (val = 0.0; isdigit(s[i]); ++i)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        ++i;

    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E') {
        power /= pow(10, atof(&s[++i]));
    }

    return sign * val / power;
}
