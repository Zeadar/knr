#include <stdio.h>
#include <string.h>
char *pstrncopy(char *, char *, int);

#define LEN 9

int main() {
    char *str1 = "Copy this string";
    char buffer[1024];

    pstrncopy(buffer, str1, LEN);

    buffer[LEN] = '\0';

    printf("%s\n", buffer);
    return 0;
}

char *pstrncopy(char *destination, char *source, int n) {
    int src_len = strlen(source);
    int lowest = n < src_len ? n : src_len;
    int excess = n - lowest;

    while (lowest--)
        *destination++ = *source++;

    while (excess--)
        *destination++ = '\0';

    return destination;
}
