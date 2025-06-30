#include <stdio.h>
#include <string.h>
#include "libkalle.c"
#define BUFSIZE 1024

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr,
                "Please feed two files in the argument parameter.\n");
        return 1;
    }

    FILE *f1, *f2;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    char buf1[BUFSIZE], buf2[BUFSIZE];

    while (fgets(buf1, BUFSIZE, f1)
           && fgets(buf2, BUFSIZE, f2)
        ) {
        if (strcmp(buf1, buf2) != 0) {
            mark_tabnewline(buf1, BUFSIZE);
            mark_tabnewline(buf2, BUFSIZE);
            printf("Found difference:\n%s\n%s\n", buf1, buf2);
            break;
        }
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
