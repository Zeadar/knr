#include "libkalle.c"
#include <stdio.h>
#define MAXLEN 1024

char *get_stop(char *start) {
    char *c = start;

    while (*c != '\0' && (*c == '-' || c == start))
        ++c;

    return c;
}

void expand(char expand_from[], char expand_to[], int expto_size) {
    --expto_size;
    char *start, *stop, c;
    int i = 0;
    start = expand_from;

    for (;;) {
        stop = get_stop(start);

        if (*stop == '\0')
            break;

        printf("start:\t%p\t%d\t%c\nstop:\t%p\t%d\t%c\n", start, *start,
               *start, stop, *stop, *stop);

        for (c = *start; c <= *stop; ++c) {
            if (i < expto_size)
                expand_to[i++] = c;
        }

        start = stop;
    }

    expand_to[i] = '\0';
}


int main() {
    char expand_from[MAXLEN], expand_to[MAXLEN];

    while (readline(expand_from, MAXLEN)) {
        trim(expand_from);
        printf("expand_from %s\n", expand_from);
        expand(expand_from, expand_to, MAXLEN);
        printf("expand_to %s\n", expand_to);
    }

    return 0;
}
