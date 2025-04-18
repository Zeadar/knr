#include "libkalle.c"
#include <stdio.h>

void print_values(char str[], int len) {
    for (int i = 0; i != len; ++i)
        printf("%d ", str[i]);
    putchar('\n');
}

int main() {
    char str[1024];
    int len;

    while ((len = readline(str, 1024))) {
        /* Since readline(char *line, int max_size) returns amount of bytes used
           it is slightly inapproperiate to call this variable len.
           And thus we get the len from my beloved trim function instead. */
        len = trim(str);
        printf("len: %d\n", len);
        print_values(str, len);
        reverse(str, len);
        print_values(str, len);
        printf("%s\n", str);
    }

    return 0;
}
