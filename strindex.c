#include <stdio.h>
#include "libkalle.c"

#define MAXLEN 1024

int strindex(char *, char *);
int length(char *);
int data_compare(void *, void *, int);

int main() {
    char str[MAXLEN];
    char find[MAXLEN];
    int len;

    for (;;) {
        printf("str\t");
        len = readline(str, MAXLEN);
        if (!len)
            break;
        trim(str);

        printf("find\t");
        len = readline(find, MAXLEN);
        if (!len)
            break;
        trim(find);

        /* printf("string\t%s\nletters\t%d\n", find, length(find)); */
        printf("str[]\t%s\nfind[]\t%s\nat %d\n", str, find,
               strindex(str, find));
    }

    putchar('\n');
    return 0;
}

int strindex(char string[], char target[]) {
    int s_len, t_len, i, position;
    s_len = length(string);
    t_len = length(target);
    position = -1;

    if (s_len < t_len)
        return -1;

    for (i = 0; i <= s_len - t_len; ++i)
        if (data_compare(string + i, target, t_len))
            position = i;

    return position;
}

int length(char s[]) {
    char *c;
    for (c = s; *c != '\0'; ++c);
    return c - s;
}

int data_compare(void *a, void *b, int width) {
    unsigned char *aa = a;
    unsigned char *bb = b;
    int i;

    for (i = 0; i != width; ++i)
        if (aa[i] != bb[i])
            return 0;

    return 1;
}
