#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int c;
    if (argc < 1)
        return 0;

    if (strcmp("upper", argv[1]) == 0)
        while ((c = getchar()) != EOF)
            putchar(toupper(c));

    if (strcmp("lower", argv[1]) == 0)
        while ((c = getchar()) != EOF)
            putchar(tolower(c));

    return 0;
}
