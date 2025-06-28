#include "slice.c"
#include <assert.h>
#include <stdio.h>

struct test_set1 {
    int a;
    int b;
    char c;
};

void test_set1(void *ptr) {
    struct test_set1 *ts = ptr;
    assert(ts->a == ts->b);
    assert(ts->b == ts->c);
}

void test_push_and_get() {
    Slice s = slice_new(int);
    int x = 42;
    slice_push(&s, &x);
    int value = slice_get(int, &s, 0);
    assert(value == 42);
    slice_destroy(&s);
    printf("test_push_and_get passed\n");
}

void test_replace() {
    Slice s = slice_new(int);
    int x = 10, y = 20;
    slice_push(&s, &x);
    slice_replace(&s, 0, &y);
    int value = slice_get(int, &s, 0);
    assert(value == 20);
    slice_destroy(&s);
    printf("test_replace passed\n");
}

void test_remove_last() {
    Slice s = slice_new(int);
    int a = 1, b = 2, c = 3;
    slice_push(&s, &a);
    slice_push(&s, &b);
    slice_push(&s, &c);
    slice_remove(&s, 2);        // remove last
    assert(slice_size(&s) == 2);
    assert(slice_get(int, &s, 0) == 1);
    assert(slice_get(int, &s, 1) == 2);
    slice_destroy(&s);
    printf("test_remove_last passed\n");
}

void test_serial_remove_middle() {
    Slice s = slice_new(int);
    for (int i = 0; i < 5; ++i)
        slice_push(&s, &i);
    slice_serial_remove(&s, 2);
    assert(slice_size(&s) == 4);
    assert(slice_get(int, &s, 2) == 3);
    assert(slice_get(int, &s, 3) == 4);
    slice_destroy(&s);
    printf("test_serial_remove_middle passed\n");
}

void test_size_and_room() {
    Slice s = slice_new(int);
    for (int i = 0; i < 10; ++i)
        slice_push(&s, &i);
    assert(slice_size(&s) == 10);
    assert(slice_room(&s) >= 10);
    slice_destroy(&s);
    printf("test_size_and_room passed\n");
}

void test_bounds_checking() {
    Slice s = slice_new(int);
    int x = 5;
    slice_push(&s, &x);

    assert(slice_index_in_bounds(&s, 0) == 1);
    assert(slice_index_in_bounds(&s, 1) == 0);
    assert(slice_ptr_in_bounds(&s, slice_get_ptr(&s, 0)) == 1);

    slice_destroy(&s);
    printf("test_bounds_checking passed\n");
}

int main() {
    Slice s1 = slice_new(struct test_set1);
    struct test_set1 ts1;

    printf("size of struct %lu\n", sizeof(struct test_set1));
    printf("slice width %zu\n", s1.width);

    for (int i = 0; i != 10; ++i) {
        ts1.a = i;
        ts1.b = i;
        ts1.c = i;
        slice_push(&s1, &ts1);
    }

    slice_foreach(&s1, test_set1);
    slice_destroy(&s1);

    // Additional tests from chatgpt
    test_push_and_get();
    test_replace();
    test_remove_last();
    test_serial_remove_middle();
    test_size_and_room();
    test_bounds_checking();

    printf("All tests passed.\n");
    return 0;
}
