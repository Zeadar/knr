#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libkalle.c"

#define NUMERIC 0b1
#define REVERSE 0b10
#define FOLDING 0b100
#define DIRECTO 0b1000

#define MAXLINES 5000
#define MAXLINESIZE 1024
char *lineptr[MAXLINES], *str_arena, *arena_head;

char *allocate(int);
void reverse_array_array(void **, int);

int readlines(char *[]);
void writelines(char *[], int);

void knr_qsort(void *[], int, int, int (*)(void *, void *));

int numcmp(const char *, const char *);
int foldcmp(const char *, const char *);
int dircmp(const char *, const char *);
int folddircmp(const char *, const char *);

int main(int argc, char **argv) {
    int nlines, mode = 0;
    str_arena = malloc(MAXLINESIZE * MAXLINES);
    arena_head = str_arena;

    if (argc > 1 && argv[1][0] == '-') {
        char *head = &argv[1][1];

        while (*head != '\0') {
            switch (*head++) {
            case 'n':
                mode |= NUMERIC;
                break;
            case 'r':
                mode |= REVERSE;
                break;
            case 'f':
                mode |= FOLDING;
                break;
            case 'd':
                mode |= DIRECTO;
            default:
                break;
            }
        }
    }

    if ((nlines = readlines(lineptr)) >= 0) {
        if (mode & NUMERIC)
            knr_qsort((void **) lineptr, 0, nlines - 1,
                      (int (*)(void *, void *)) (numcmp));

        else if ((mode & FOLDING) && (mode & DIRECTO))
            knr_qsort((void **) lineptr, 0, nlines - 1,
                      (int (*)(void *, void *)) (folddircmp));

        else if (mode & FOLDING)
            knr_qsort((void **) lineptr, 0, nlines - 1,
                      (int (*)(void *, void *)) (foldcmp));

        else if (mode & DIRECTO)
            knr_qsort((void **) lineptr, 0, nlines - 1,
                      (int (*)(void *, void *)) (dircmp));

        else
            knr_qsort((void **) lineptr, 0, nlines - 1,
                      (int (*)(void *, void *)) (strcmp));

        if (mode & REVERSE)
            reverse_array_array((void *) lineptr, nlines);

        writelines(lineptr, nlines);
        return 0;
    } else {
        //unreachable
        printf("input too big to sort\n");
    }

    return 0;
}

void knr_qsort(void *v[], int left, int right,
               int (*comp_f)(void *, void *)) {
    int i, last;

    // Didn't know it was possible to have prototypes in
    // a function or why there should be one
    // but here it is, straight from the book, with no explanation
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i)
        if ((*comp_f) (v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    knr_qsort(v, left, last - 1, comp_f);
    knr_qsort(v, last + 1, right, comp_f);
}

void swap(void *v[], int a, int b) {
    void *temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

int numcmp(const char *s1, const char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;

    if (v1 > v2)
        return 1;

    return 0;
}

int readlines(char *lineptr[]) {
    char buffer[MAXLINESIZE];
    int len, i = 0;

    while ((len = readline(buffer, MAXLINESIZE)) && i < MAXLINES) {
        lineptr[i] = allocate(len + 1); //+1 for \0
        strcpy(lineptr[i], buffer);
        ++i;
    }

    return i;
}

void writelines(char *lineptr[], int lines) {
    int i;
    for (i = 0; i < lines; ++i)
        printf("%s", lineptr[i]);
}

char *allocate(int size) {
    arena_head += size;
    return arena_head - size;
}

void reverse_array_array(void **to_reverse, int len) {
    int i, j = len - 1;
    for (i = 0; i < j; ++i, --j)
        swap(to_reverse, i, j);
}

int foldcmp(const char *s1, const char *s2) {
    char v1[MAXLINESIZE], v2[MAXLINESIZE];
    char *v1_write = v1;
    char *v2_write = v2;

    while (*s1 != '\0')
        *v1_write++ = tolower(*s1++);

    while (*s2 != '\0')
        *v2_write++ = tolower(*s2++);

    *v1_write = '\0';
    *v2_write = '\0';

    return strcmp(v1, v2);
}

int dircmp(const char *s1, const char *s2) {
    char v1[MAXLINESIZE], v2[MAXLINESIZE];
    char *v1_write = v1;
    char *v2_write = v2;

    while (*s1 != '\0') {
        if (isalnum(*s1) || *s1 == ' ')
            *v1_write++ = *s1;
        ++s1;
    }

    while (*s2 != '\0') {
        if (isalnum(*s2) || *s2 == ' ')
            *v2_write++ = *s2;
        ++s2;
    }

    *v1_write = '\0';
    *v2_write = '\0';

    return strcmp(v1, v2);
}

int folddircmp(const char *s1, const char *s2) {
    char v1[MAXLINESIZE], v2[MAXLINESIZE];
    char *v1_write = v1;
    char *v2_write = v2;

    while (*s1 != '\0') {
        if (isalnum(*s1) || *s1 == ' ')
            *v1_write++ = tolower(*s1);
        ++s1;
    }

    while (*s2 != '\0') {
        if (isalnum(*s2) || *s2 == ' ')
            *v2_write++ = tolower(*s2);
        ++s2;
    }

    *v1_write = '\0';
    *v2_write = '\0';

    return strcmp(v1, v2);
}
