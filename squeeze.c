#include <stdio.h>
#include <stdlib.h>
#include "libkalle.c"

#define MAXSIZE 1024

void squeeze(char *, char *, int);
void squeeze2(char *, char *);

int main() {
    char sqz[MAXSIZE], line[MAXSIZE];
    int sqz_len, line_len;


    do {
        printf("\nline: ");
        if (!(line_len = readline(line, MAXSIZE)))
            break;

        printf("\nexclude: ");
        if (!(sqz_len = readline(sqz, MAXSIZE)))
            break;


        trim_end(line, line_len);
        trim_end(sqz, sqz_len);

        /* squeeze(line, sqz, MAXSIZE); */
        squeeze2(line, sqz);
        printf("result: %s", line);
    } while (1337);

    return 0;
}

void squeeze2(char str1[], char str2[]) {
    int i, j, h, skip;
    h = 0;
    for (i = 0; str1[i] != '\n'; ++i) {
        skip = 0;
        for (j = 0; str2[j] != '\0'; ++j) {
            if (str1[i] == str2[j])
                skip = 1;
        }

        if (!skip) {
            str1[h++] = str1[i];
        }
    }

    str1[h] = '\0';
}

void squeeze(char str1[], char str2[], int max_size) {
    char *temp = malloc(max_size);
    char *c1, *c2;
    int i = 0;
    int skip;

    for (c1 = str1; *c1 != '\0'; ++c1) {
        skip = 0;

        for (c2 = str2; *c2 != '\0'; ++c2) {
            if (*c1 == *c2)
                skip = 1;

        }

        if (!skip)
            temp[i++] = *c1;
    }
    temp[i] = '\0';

    i = 0;
    for (c1 = temp; *c1 != '\0'; ++c1)
        str1[i++] = *c1;
    str1[i] = '\0';

    free(temp);
}
