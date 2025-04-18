#include <stdio.h>
#include "libkalle.c"

#define MAXSIZE 1024
#define BREAKPOINT 20

int chars_till_ws(char *);

int main() {

    char line[MAXSIZE];
    int len, i, cf, checkpoint;
    while ((len = readline(line, MAXSIZE))) {
        i = 0;
        checkpoint = BREAKPOINT;

        while (i < len) {

            if (line[i] == ' ') {
                cf = chars_till_ws(&line[i + 1]);
                printf("%d ", cf);

                if (i + cf > checkpoint) {
                    line[i] = '\n';
                    i += cf;
                } else
                    ++i;

            } else
                ++i;

            while (checkpoint <= i)
                checkpoint += BREAKPOINT;
            /* i += chars_till_ws(&line[i]) - 1; */
        }

        printf("\n%s", line);
    }

    return 0;
}

int chars_till_ws(char *c) {
    int i = 0;
    char *cc;

    while (*(cc = c + i) != ' ' && *cc != '\n' && *cc != '\t'
           && *cc != '\0')
        ++i;

    return i;
}
