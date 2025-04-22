#include <stdio.h>
#define dprint(a, b) printf("%s, %s, %d\n", a, b, strend(a, b))

int strend(char *, char *);

int main() {
    char *str1 = "This is a test";
    char *str2 = "a test";
    char *str3 = "not a test";
    char *str4 = "abcd";

    dprint(str1, str2);
    dprint(str1, str3);
    dprint(str4, str4);
    dprint(str4, "abcde");

    return 0;
}

int strend(char *source, char *target) {
    char *t = target;
    char *s = source;

    while (*t)
        ++t;

    while (*s)
        ++s;

    if (t - target > s - source)
        return 0;

    while (*--t == *--s)
        if (t == target)
            return 1;

    return 0;
}
