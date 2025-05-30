#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i, r, end;

    if (argc > 1)
        end = atoi(argv[1]);
    else
        end = 100;

    for (i = 1; i <= end; ++i) {
        r = i % 3 == 0;
        r |= (i % 5 == 0) << 1;

        if (!r) {
            printf("%d\n", i);
            continue;
        }

        if (r & 0b01)
            printf("fizz");

        if (r & 0b10)
            printf("buzz");

        putchar('\n');
    }

    return 0;
}
