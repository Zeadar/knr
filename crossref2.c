#include "hashy.c"
#include "types.h"
#include "libkalle.c"

#define BUFSIZE 1024

Map hashmap;

void each(char *key, void *value) {
    u64 *v = value;
    printf("%.4ld %s\n", *v, key);
}

int main() {
    hashmap = hashy_new(u64);
    char buffer[BUFSIZE];
    u64 *r;

    while (getword(buffer, BUFSIZE)) {
        // printf("%s\n", buffer);
        r = hashy_get(&hashmap, buffer);

        if (r) {
            *r += 1;
        } else {
            u64 count = 1;
            hashy_install(&hashmap, buffer, &count);
        }
    }

    hashy_foreach(&hashmap, each);

    hashy_destroy(&hashmap);
    return 0;
}
