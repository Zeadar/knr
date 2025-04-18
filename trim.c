#include "libkalle.c"
#include <stdio.h>

int main() {
    char str[1024] = "   12345\t\n";
    int len;

    printf("original:\n%s", str);
    len = trim(str);
    printf("trimmed:\n%s\nnew length: %d\n", str, len);

    return 0;
}
