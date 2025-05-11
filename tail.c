#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libkalle.c"
#define MAXSIZE 1024

void shift(char **, int);

int main(int argc, char **argv) {
    char buffer[MAXSIZE];
    char **lines;
    int i, tail = argc == 1 ? 5 : 0;

    while (*++argv) {
        char *head = *argv;
        while (*head) {
            if (isdigit(*head))
                tail = tail * 10 + *head - '0';
            ++head;
        }
    }

    if (tail == 0) {
        fprintf(stderr, "unparsable parameters\n");
        return 100;
    }

    if (tail > 1024) {
        fprintf(stderr, "%d lines. Don't be ridiculous\n", tail);
        return 100;
    }

    lines = malloc(tail * sizeof(*lines));

    for (i = 0; i != tail; ++i)
        lines[i] = 0;

    for (i = 0; i != tail; ++i) {
        lines[i] = malloc(MAXSIZE);
        if (!readline(lines[i], MAXSIZE))
            break;
    }

    for (i = 0; readline(buffer, MAXSIZE); ++i) {
        shift(lines, tail);
        strcpy(lines[tail - 1], buffer);
    }

    for (i = 0; i < tail; ++i)
        if (lines[i])
            printf("%s", lines[i]);

    // Valgrind approved
    for (i = 0; i != tail; ++i)
        free(lines[i]);
    free(lines);

    return 0;
}

void shift(char **lines, int tail) {
    if (tail < 2)
        return;
    int i;
    char *first = *lines;
    for (i = 0; i < tail - 1; ++i)
        lines[i] = lines[i + 1];
    lines[tail - 1] = first;
}
