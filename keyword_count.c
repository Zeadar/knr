#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NKEYS (sizeof(keytab) / sizeof(struct key))
#define MAXWORD 100

struct key {
    char *word;
    int count;
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getword(char *, int);
int getch();
void ungetch(int);

struct key keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    { "do", 0 },
    { "double", 0 },
    { "else", 0 },
    { "enum", 0 },
    { "extern", 0 },
    { "float", 0 },
    { "for", 0 },
    { "goto", 0 },
    { "if", 0 },
    { "int", 0 },
    { "long", 0 },
    { "register", 0 },
    { "return", 0 },
    { "short", 0 },
    { "signed", 0 },
    { "sizeof", 0 },
    { "static", 0 },
    { "struct", 0 },
    { "switch", 0 },
    { "typedef", 0 },
    { "union", 0 },
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 },
};

int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;

    for (n = 0; n < (int) NKEYS; ++n)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}

int binsearch(char *word, struct key tab[], int tab_len) {
    int cond, low, high, mid;

    low = 0;
    high = tab_len - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

/*
    TODO
    → if find // skip until \n
    → if find [block comment start] skip until [block comment end]
    → if find " skip until "
    → if find # skip until \n
    → if find _ include as part of word
*/

int getword(char *word, int lim) {
    int c, temp;
    char *w = word;

    while (isspace(c = getch()));


    if (c == '/') {             //if find // skip until \n
        temp = c;
        if ((c = getch()) == '/')
            while ((c = getch()) != '\n');
        else {
            ungetch(c);
            c = temp;
        }
    }

    if (c == '/') {             // if find [block comment start] skip until [block comment end]
        temp = c;
        if ((c = getch()) == '*') {
            for (;;) {
                if ((c = getch()) == '*') {
                    if ((c = getch()) == '/') {
                        break;
                    } else {
                        ungetch(c);
                    }
                }
            }
        } else {
            ungetch(c);
            c = temp;
        }
    }

    if (c == '"')               // if find " skip until "
        while ((c = getch()) != '"');

    if (c == '#')               // if find # skip until \n
        while ((c = getch()) != '\n');

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; ++w)
        if (!isalnum(*w = getch()) && *w != '_') {      // if find _ include as part of word
            ungetch(*w);
            break;
        }

    *w = '\0';

    return word[0];
}

int getch_buf = 0;

int getch() {
    if (getch_buf) {
        int tmp = getch_buf;
        getch_buf = 0;
        return tmp;
    }

    return getchar();
}

void ungetch(int c) {
    getch_buf = c;
}
