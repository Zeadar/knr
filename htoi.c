#include <stdio.h>
#include "libkalle.c"

#define MAXSIZE 1024

long htoi(char *);

int main() {
    char hex[MAXSIZE];
    int len;

    while ((len = readline(hex, MAXSIZE))) {
        trim_end(hex, len);
        printf("hex %s\ndec %ld\n", hex, htoi(hex));
    }

    return 0;
}

long htoi(char str[]) {
    long r = 0;
    char *c;

    /* check if string begins with 0x or 0X
       and is at least 2 characters long */
    if (str[0] != '\0' && str[1] != '\0' && str[0] == '0'
        && (str[1] == 'x' || str[1] == 'X'))
        str += 2;

    for (c = str; *c != '\n' && *c != '\0'; ++c) {
        /*
           r = r << 4 is much cooler than r *= 16
         */
        r = r << 4;
        if (*c >= '0' && *c <= '9')
            r += *c - '0';
        else if (*c >= 'A' && *c <= 'F')
            r += *c - 'A' + 10;
        else if (*c >= 'a' && *c <= 'f')
            r += *c - 'a' + 10;
        else
            return -1;
    }

    return r;
}
