#include <stdio.h>

void lower(char *);

int main() {

    char buffer[100] =
        "Hello, This Is A String Literal With Various Capital LETTERS";

    lower(buffer);

    printf("%s", buffer);

    return 0;
}

void lower(char *s) {
    char *c = s;

    while (*c != '\0') {
        *c += (*c >= 'A' && *c <= 'Z') ? 32 : 0;
        ++c;
    }
}
