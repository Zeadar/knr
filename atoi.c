#include <stdio.h>
int atoi(char *);

int main() {
    char test[] = "-59";
    int r = atoi(test);

    printf("%d\n", r);
    return 0;
}

int atoi(char s[]) {
    int val = 0;
    int sign = 1;
    char *c = s;

    if (*c == '-') {
        sign = -1;
        ++c;
    }

    while (*c >= '0' && *c <= '9')
        val = val * 10 + *c++ - '0';

    return val * sign;
}
