#include <stdio.h>
#include "libkalle.c"

#define MAXSIZE 1024
#define TABSTOP 4

int readline(char[], int);

int main() {
    char in_str[MAXSIZE];
    char out_str[MAXSIZE];
    int len, i, j, next_stop;

    while ((len = readline(in_str, MAXSIZE))) {
        next_stop = TABSTOP;
        j = 0;

        for (i = 0; i != len && j < MAXSIZE; ++i) {
            if (j >= next_stop)
                next_stop += TABSTOP;

            if (in_str[i] == '\t')
                while (j < next_stop && j < MAXSIZE)
                    out_str[j++] = ' ';
            else
                out_str[j++] = in_str[i];
        }

        out_str[j] = '\0';

        printf("%s", out_str);
    }

    return 0;
}
