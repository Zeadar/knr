#include <stdio.h>
#include "libkalle.c"
typedef unsigned short u16;

u16 invert(u16, u16, u16);

int main() {
    char buffer[sizeof(u16) * 8 + 1];
    u16 result = invert(0b1010101010101010, 0, 6);
    formatbytes(buffer, &result, sizeof(result));
    printf("result\n%s\n", buffer);

    return 0;
}

u16 invert(u16 x, u16 p, u16 n) {
    u16 bitmask = ~((u16) ~ 0 << n) << p;
    return (x & ~bitmask) | (~x & bitmask);
}
