#include <stdio.h>
#include "libkalle.c"

#define BUFSIZE 2048

int pstrcat(char *, const char *);
int main() {
    char target[BUFSIZE];
    char buffer[BUFSIZE];
    int buffer_len, total_len = 0;
    target[0] = '\0';

    while ((buffer_len = readline(buffer, BUFSIZE))
           && buffer_len + total_len < BUFSIZE - 1) {
        trim_end(buffer, buffer_len);
        total_len = pstrcat(target, buffer);
        printf("%s\n", target);
    }

    return 0;
}


int pstrcat(char *t, const char *s) {
    char *write = t;
    while (*write++);
    write--;
    while ((*write++ = *s++));

    return write - t;
}
