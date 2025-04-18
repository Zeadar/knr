#include <stdio.h>
#define MAXLINE 1000
#define MIN_LEN 40

int getline(char line[], int maxline);
void copy(char *, char *);
void original();
void more_than_min();
void trim_end();
void reverse();

int main() {
    /* more_than_min(); */
    /* trim_end(); */
    reverse();

    return 0;
}

void reverse() {
    char line[MAXLINE];
    char reversed[MAXLINE];
    int len, i, j;

    while ((len = getline(line, MAXLINE))) {

        j = 0;
        /* len - 1 else the sentence will start with a null character */
        for (i = len - 1; i >= 0; --i) {
            reversed[j++] = line[i];
            /* printf("%d-%d ", i, j); */
        }

        reversed[j] = '\0';

        printf("%s\n", reversed);
    }
}

void trim_end() {
    char line[MAXLINE];
    int i, len;

    while ((len = getline(line, MAXLINE))) {
        if (len < 2)
            continue;

        i = len - 1;
        while (line[i] == '\t' || line[i] == ' ' || line[i] == '\n') {
            line[i--] = '\0';
        }

        line[i + 1] = '\n';
        line[i + 2] = '\0';

        printf("%d %d %s", len, i + 2, line);
    }
}

void more_than_min() {
    char line[MAXLINE];
    int len;

    while ((len = getline(line, MAXLINE)))
        if (len > MIN_LEN)
            printf("%d %s\n", len, line);

}

void original() {
    int len, max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)))
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0) {
        printf("%3d ", max);
        printf("%s\n", longest);
    }
}

int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

void copy(char to[], char from[]) {
    int i;

    i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
