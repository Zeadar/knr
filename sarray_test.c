#include "string_array.c"
#include "libkalle.c"
#include <stdio.h>

int main() {
    Sarray str1 = sarray_create();
    char buffer[1024];

    for (int i = 0; i != 10; ++i) {
        itob(i, buffer, 10);
        strcat(buffer, " Hello");

        slice_index idx = sarray_push(&str1, buffer);
        printf("Index %td\n", idx);
    }

    printf("%td\n", sarray_size(&str1));

    sarray_remove(&str1, 3);
    sarray_remove(&str1, 7);
    sarray_remove(&str1, 1);

    for (int i = 10; i != 15; ++i) {
        itob(i, buffer, 10);
        strcat(buffer, " Bye");

        slice_index idx = sarray_push(&str1, buffer);
        printf("Index %td\n", idx);
    }

    for (int i = 0; i < sarray_size(&str1); ++i) {
        char *test = sarray_get(&str1, i);

        printf("Get result i%d %s\n", i, test);
    }

    printf("%td\n", sarray_size(&str1));

    return 0;
}
