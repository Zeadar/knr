#include "libkalle.c"

#define MAXSIZE 1024

int main() {
    char buffer[MAXSIZE];

    while (readline(buffer, MAXSIZE)) {
        itob(atoi(buffer), buffer, 16);
        printf("%s\n", buffer);
    }

    return 0;
}
