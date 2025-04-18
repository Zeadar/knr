#include <stdio.h>

long double powaa(long double x, long double y) {
    long double rez = 1;
    for (; y > 0; --y)
        rez *= x;

    return rez;
}

int main() {
    long long bytes;

    bytes = powaa(2, sizeof(long) * 8);
    printf("LONG MAX %lld\n", bytes - (bytes / 2) - 1);
    printf("LONG MIN %lld\n", (bytes - bytes / 2) * -1);
    printf("ULONG %lld\n", bytes);

    bytes = powaa(2, sizeof(int) * 8);
    printf("INT MAX %lld\n", bytes - (bytes / 2) - 1);
    printf("INT MIN %lld\n", (bytes - bytes / 2) * -1);
    printf("UINT %lld\n", bytes);

    bytes = powaa(2, sizeof(short) * 8);
    printf("SHORT MAX %lld\n", bytes - (bytes / 2) - 1);
    printf("SHORT MIN %lld\n", (bytes - bytes / 2) * -1);
    printf("USHORT %lld\n", bytes);

    bytes = powaa(2, sizeof(char) * 8);
    printf("CHAR MAX %lld\n", bytes - (bytes / 2) - 1);
    printf("CHAR MIN %lld\n", (bytes - bytes / 2) * -1);
    printf("UCHAR %lld\n", bytes);

    return 0;
}
