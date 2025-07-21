#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "string_array.c"

void test_create_destroy() {
    Sarray sa = sarray_create();
    assert(sa.ptr != NULL);
    assert(sarray_size(&sa) == 0);
    sarray_destroy(&sa);
}

void test_push_get() {
    Sarray sa = sarray_create();

    slice_index a = sarray_push(&sa, "alpha");
    slice_index b = sarray_push(&sa, "bravo");
    slice_index c = sarray_push(&sa, "charlie");

    assert(strcmp(sarray_get(&sa, a), "alpha") == 0);
    assert(strcmp(sarray_get(&sa, b), "bravo") == 0);
    assert(strcmp(sarray_get(&sa, c), "charlie") == 0);

    sarray_destroy(&sa);
}

void test_remove_middle() {
    Sarray sa = sarray_create();

    slice_index a = sarray_push(&sa, "first");
    slice_index b = sarray_push(&sa, "middle");
    slice_index c = sarray_push(&sa, "last");

    sarray_remove(&sa, b);      // remove "middle"
    assert(strcmp(sarray_get(&sa, a), "first") == 0);
    assert(strcmp(sarray_get(&sa, c - 1), "last") == 0);
    assert(sarray_size(&sa) == 2);

    sarray_destroy(&sa);
}

void test_remove_all() {
    Sarray sa = sarray_create();

    sarray_push(&sa, "1");
    sarray_push(&sa, "2");
    sarray_push(&sa, "3");

    sarray_remove(&sa, 2);
    sarray_remove(&sa, 1);
    sarray_remove(&sa, 0);

    assert(sarray_size(&sa) == 0);

    sarray_destroy(&sa);
}

void test_empty_and_duplicates() {
    Sarray sa = sarray_create();

    sarray_push(&sa, "");
    sarray_push(&sa, "duplicate");
    sarray_push(&sa, "duplicate");

    assert(strcmp(sarray_get(&sa, 0), "") == 0);
    assert(strcmp(sarray_get(&sa, 1), "duplicate") == 0);
    assert(strcmp(sarray_get(&sa, 2), "duplicate") == 0);

    sarray_destroy(&sa);
}

int main() {
    printf("Running sarray tests...\n");

    test_create_destroy();
    test_push_get();
    test_remove_middle();
    test_remove_all();
    test_empty_and_duplicates();

    printf("All tests passed.\n");
    return 0;
}
