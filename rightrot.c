#include "libkalle.c"
typedef unsigned short u16;

u16 rightrot(u16, u16);

int main() {
    u16 result;
    u16 i;
    char buffer[sizeof(u16) * 8 + 1];

    for (i = 0; i < sizeof(result) * 8 * 2; ++i) {
        result = rightrot(0b1111111100000000, i);
        formatbytes(buffer, &result, sizeof(result));
        printf("i: %d\tresult\n%s\n", i, buffer);
    }

    return 0;
}

u16 rightrot(u16 x, u16 n) {
    n = n % (sizeof(x) * 8);
    return x >> n | x << (sizeof(x) * 8 - n);
}
