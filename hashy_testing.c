#include "hashy.c"
#include <assert.h>

int main() {
    Map hashmap = hashy_create(sizeof(long));
    long num = 50;
    hashy_install(&hashmap, "test", &num);

    long *r = hashy_get(&hashmap, "test");
    assert(*r == 50);

    r = hashy_get(&hashmap, "not exist");
    assert(r == 0);

    num = 30;
    hashy_install(&hashmap, "test", &num);

    r = hashy_get(&hashmap, "test");
    assert(*r == 30);

    char buffer[1024];

    for (long i = 10; i != 10000; ++i) {
        long n = i;
        sprintf(buffer, "key %ld", i);

        hashy_install(&hashmap, buffer, &n);
    }

    for (long i = 10; i != 10000; ++i) {
        sprintf(buffer, "key %ld", i);
        long *r = hashy_get(&hashmap, buffer);
        // printf("result %ld\n", *r);
        assert(i == *r);
    }

    printf("used %zu\n", hashmap.used);

    return 0;
}
