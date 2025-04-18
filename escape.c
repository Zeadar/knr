#include "libkalle.c"
#define MAXSIZE 128

void escape(char *, char *, int);

int main() {
    char from[MAXSIZE];
    char to[MAXSIZE];
    int len;

    while ((len = readline(from, MAXSIZE))) {
        escape(from, to, MAXSIZE);
        printf("%s\n", to);
    }
}

void escape(char *from, char *to, int max_size) {
    int i = 0;
    char *c;

    for (c = from; *c != '\0'; ++c) {
        switch (*c) {
        case '\t':
            to[i++] = '\\';
            if (i < max_size)
                to[i++] = 't';
            break;
        case '\n':
            to[i++] = '\\';
            if (i < max_size)
                to[i++] = 'n';
            break;
        default:
            to[i++] = *c;
            break;
        }

        if (i == max_size) {
            break;
        }
    }

    to[i] = '\0';
}
