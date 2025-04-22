#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);;

void qsort(char **, int, int);

int main() {
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }

    return 0;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void swap(char **v, int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(char *v[], int left, int right) {
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; ++i)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

#define MAXLEN 1000
// int getline(char *, int);
int readline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    while ((len = readline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

//524288 is half a mibibyte
#define ALLOCSIZE 524288
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return NULL;
    }
}

/* void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
} */

/* OBS Returns bytes used and not amount of characters */
int readline(char line[], int max_size) {
    int i, c;
    i = 0;
    while ((c = getchar()) != EOF && i < max_size - 1 && c != '\n'
           && c != '\0')
        line[i++] = c;

    if (c == '\n') {
        line[i++] = c;
    }

    line[i] = '\0';

    return i;
}
