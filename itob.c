#include "libkalle.c"

int main() {
    char buffer[1024];

    itob(10, buffer, 16);

    printf("%s\n", buffer);

    return 0;
}
