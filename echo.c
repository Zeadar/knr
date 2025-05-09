#include <stdio.h>

int main(int argc, char **argv) {
    while (--argc) {
        printf(argc > 1 ? "%s " : "%s", *++argv);
    }

    putchar('\n');

    return 0;
}
