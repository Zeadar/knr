#include "slice.c"
#include <stdio.h>

struct test_set {
    long data_a;                //8 bytes
    long data_b;
    long data_c;
    long data_d;
};

#define PUSHAMOUNT 10

int main() {
    struct slice s1 = slice_new(struct test_set);

    for (int i = 0; i != PUSHAMOUNT; ++i) {
        struct test_set ts = {
            i,
            PUSHAMOUNT - i,
            i - PUSHAMOUNT,
            i + PUSHAMOUNT,
        };

        slice_push(&s1, &ts);
    }

    slice_serial_remove(&s1, 2);
    printf("removed index 2\n");

    for (int i = 0; i <= PUSHAMOUNT; ++i) {
        struct test_set *ts1 = slice_get_ptr(&s1, i);
        printf("%p\n", ts1);

        if (ts1) {
            printf("data_a %ld\tdata_b %ld\tddata_c %ld\tdata_d %ld\n",
                   ts1->data_a, ts1->data_b, ts1->data_c, ts1->data_d);
        }
    }

    struct test_set ts2 = slice_get(struct test_set, &s1, PUSHAMOUNT / 2);
    printf("data_a %ld\tdata_b %ld\tddata_c %ld\tdata_d %ld\n",
           ts2.data_a, ts2.data_b, ts2.data_c, ts2.data_d);


    printf("data_a %ld\tdata_b %ld\tddata_c %ld\tdata_d %ld\n",
           ts2.data_a, ts2.data_b, ts2.data_c, ts2.data_d);

    printf("size\t%ld\n", slice_size(&s1));
    printf("byte size\t%ld\n", s1.head - s1.begin);
    printf("full byte size\t%ld\n", s1.end - s1.begin);

    slice_destroy(&s1);

    return 0;
}
