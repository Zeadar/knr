#include <stdio.h>

void copy(FILE *source, FILE *destination) {
    int c;

    while ((c = getc(source)) != EOF)
        putc(c, destination);
}

int main(int argc, char **argv) {
    int i, status = 0;
    FILE *fptr;

    if (argc == 1)
        copy(stdin, stdout);

    for (i = 1; argv[i]; ++i) {
        if (!(fptr = fopen(argv[i], "r"))) {
            status = 100;
            fprintf(stderr, "Could not open %s\n", argv[i]);
            continue;
        }

        copy(fptr, stdout);

        fclose(fptr);
    }

    return status;
}
