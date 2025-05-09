#include "libkalle.c"
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1024

int main(int argc, char **argv) {
    char buffer[MAXSIZE];
    char pattern[MAXSIZE];
    char *found;
    int row;

    if (argc < 2)
        return 200;

    /* gather pattern */
    {
        char *write = pattern;
        char *read;
        while (--argc) {
            read = *++argv;

            while (*read && write - pattern < MAXSIZE)
                *write++ = *read++;

            if (argc - 1 && write - pattern < MAXSIZE)
                *write++ = ' ';
        }

        *write = '\0';
    }

    for (row = 1; readline(buffer, MAXSIZE); ++row)
        if ((found = strstr(buffer, pattern))) {
            printf("row\t%d\ncol\t%ld\n", row, found - buffer + 1);
            return 0;
        }

    fprintf(stderr, "Could not find \"%s\" in stdin.\n", pattern);

    return 100;
}
