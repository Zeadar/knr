#include "hashy.c"
#include <assert.h>
#include <stdio.h>

#define ITERSTART 500
#define ITEREND 700

int main() {
    Map hashmap = hashy_create(sizeof(long));
    long num = 50;
    hashy_install(&hashmap, "test", &num);

    long *r = hashy_get(&hashmap, "test");
    assert(*r == num);

    r = hashy_get(&hashmap, "not exist");
    assert(r == 0);

    num = 30;
    hashy_install(&hashmap, "test", &num);

    r = hashy_get(&hashmap, "test");
    assert(*r == num);

    hashy_remove(&hashmap, "test");
    char buffer[1024];

    for (long i = ITERSTART; i != ITEREND; ++i) {
        long n = i;
        sprintf(buffer, "key %ld", i);

        hashy_install(&hashmap, buffer, &n);
    }

    for (long i = ITERSTART; i != ITEREND; ++i) {
        if (i % 2 == 0)
            continue;

        sprintf(buffer, "key %ld", i);
        hashy_remove(&hashmap, buffer);
    }

    for (long i = ITERSTART; i != ITEREND; ++i) {
        sprintf(buffer, "key %ld", i);
        long *r = hashy_get(&hashmap, buffer);

        if (r) {
            // printf("%s, result %ld\n", buffer, *r);
            assert(i == *r);
        } else {
            // printf("%s, result %p\n", buffer, r);
        }
    }

    for (slice_index i = 0; i != hashmap.size; ++i) {
        if (i % 40 == 0)
            putchar('\n');

        if (hashmap.map[i] == -1)
            printf("   |");
        else
            printf("%3td|", hashmap.map[i]);
    }

    putchar('\n');

    printf("used %td\nsize %td\n", hashmap.used, hashmap.size);

    return 0;
}
