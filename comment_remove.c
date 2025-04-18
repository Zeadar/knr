#include <stdio.h>
#define IN 100
#define OUT 200
#define MAXSIZE 1024 * 5

int main() {
    int len, c, status;
    char *cc;
    char buffer[MAXSIZE];

    /* will this comment be removed? */

    status = OUT;
    len = 0;

    while ((c = getchar()) != EOF)
        buffer[len++] = c;

    buffer[len] = '\0';

    printf("len: %d\n", len);
    for (cc = buffer; *cc != '\0'; ++cc) {
        if (cc - buffer < len + 2 && *(cc + 1) == '/' && *(cc + 2) == '*')
            status = IN;

        if (cc - buffer > 2 && *(cc - 1) == '/' && *(cc - 2) == '*')
            status = OUT;

        if (status == OUT)
            putchar(*cc);
    }

    /* if (&cc - buffer > 2 && *(&cc - 2) == '/' && *(&cc - 1) == '*')
       status = IN;

       if (*(&cc - 2) == '*' && *(&cc - 1) == '/')
       status = OUT;


       if (status == OUT)
       putchar(cc); */


    /*
       What about
       this one?
     */
    return 0;
}

/* Extra comment! */
