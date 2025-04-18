#include <stdio.h>
#include "libkalle.c"

#define TABSTOP 4
#define MAXSIZE 1024

int space_check(char[]);
void print_opaque(char[]);

int main() {
    char in_str[MAXSIZE];
    char out_str[MAXSIZE];
    int len, i, j, next_stop, nspace;

    while ((len = readline(in_str, MAXSIZE))) {
        next_stop = j = 0;

        for (i = 0; i < len; ++i) {
            if (next_stop <= i)
                next_stop += TABSTOP;

            if (in_str[i] == ' ') {
                nspace = space_check(&in_str[i]);

                if (i + nspace >= next_stop) {
                    i = next_stop;
                    out_str[j++] = '\t';
                } else {
                    out_str[j++] = in_str[i];
                }
            } else {
                out_str[j++] = in_str[i];
            }
        }

        out_str[j] = '\0';
        print_opaque(out_str);
    }

    return 0;
}

int space_check(char *c) {
    int spaces = 0;

    while (*(c + spaces) == ' ')
        ++spaces;

    return spaces;
}

void print_opaque(char text[]) {
    int i = 0;
    char c;

    while ((c = text[i++]) != '\0') {
        if (c == ' ') {
            putchar('\\');
            putchar('_');
        } else if (c == '\t') {
            putchar('\\');
            putchar('t');
        } else {
            putchar(c);
        }
    }
}
