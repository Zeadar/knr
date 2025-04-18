#include <stddef.h>
#include <stdio.h>
#include "libkalle.c"

typedef unsigned char u8;
typedef unsigned short u16;

#define STRSIZE sizeof(long) * 8 + 1

u16 setbits(u16, u8, u8, u16);

int main() {
    u16 bits = setbits(0b1010101010101010, 12, 8, 0b1111111111111111);
    char buffer[STRSIZE];

    formatbytes(buffer, &bits, sizeof(bits));
    printf("result %s\n", buffer);

    // for (unsigned i = 1024; i < 1024 + 512; i += 16) {
    //     formatbytes(buffer, &i, sizeof(i));
    //     printf("%s\n", buffer);
    // }

    char test = -1;             //11111111
    formatbytes(buffer, &test, sizeof(test));
    printf("%s\n", buffer);

    test = 0;                   //00000000
    formatbytes(buffer, &test, sizeof(test));
    printf("%s\n", buffer);

    return 0;
}

u16 setbits(u16 x, u8 p, u8 n, u16 y) {
    /* Need to cast as u16 because ~0 == -1; true
       Also -WError has no mercy.
       Btw, priority rules for bitwise operators are totally whack
     */
    u16 bitmask = ~((~((u16) ~ 0 << n)) << (p - n));
    x = x & bitmask;
    bitmask = ~((u16) ~ 0 << n);
    y = (y & bitmask) << (p - n);
    x = x | y;
    char xstr[STRSIZE], ystr[STRSIZE], maskstr[STRSIZE];
    formatbytes(xstr, &x, sizeof(x));
    formatbytes(ystr, &y, sizeof(y));
    formatbytes(maskstr, &bitmask, sizeof(bitmask));

    printf("x %s\np %d\nn %d\ny %s\nmask %s\n", xstr, p, n, ystr, maskstr);

    return x;
}
