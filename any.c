#include <stdio.h>
#include "libkalle.c"

#define MAXSIZE 1024

long any(char *, char *);

int main() {
    char find[MAXSIZE], line[MAXSIZE];
    int find_len, line_len;

    for (;;) {
        printf("\nline: ");
        if (!(line_len = readline(line, MAXSIZE)))
            break;

        printf("find: ");
        if (!(find_len = readline(find, MAXSIZE)))
            break;

        trim_end(line, line_len);
        trim_end(find, find_len);

        printf("\nat: %ld\n", any(line, find));
    }

    return 0;
}

long any(char line[], char find[]) {
    char *f, *c;
    for (c = line; *c != '\0'; ++c)
        for (f = find; *f != '\0'; ++f)
            if (*c == *f)
                return c - line;

    return -1;
}
