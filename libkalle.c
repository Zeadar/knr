#pragma once
#include <stdio.h>

int readline(char line[], int max_size) {
    int i, c;
    i = 0;
    while ((c = getchar()) != EOF && i < max_size - 1 && c != '\n'
           && c != '\0')
        line[i++] = c;

    if (c == '\n') {
        line[i++] = c;
    }

    line[i] = '\0';

    return i;
}

/* void reverse(char *to_reverse, int length) {
    char *i, *j, temp;

    j = to_reverse + length - 1;
    for (i = to_reverse; i < j; ++i, --j) {
        temp = *i;
        *i = *j;
        *j = temp;
    }
} */

void reverse(char *to_reverse, int length) {
    char temp;
    if (length > 1) {
        temp = *to_reverse;
        *to_reverse = to_reverse[length - 1];
        to_reverse[length - 1] = temp;
        reverse(to_reverse + 1, length - 2);
    }
}

void itob(int n, char s[], int b) {
    int i, sign, temp;
    i = 0;

    if ((sign = n) < 0)
        n = -n;

    do {
        temp = n % b;

        if (temp > 9)
            s[i++] = temp - 10 + 'A';
        else
            s[i++] = temp + '0';

    } while ((n /= b) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    reverse(s, i);
}

// int atoi(char s[]) {
//     int val = 0;
//     int sign = 1;

//     if (*s == '-') {
//         sign = -1;
//         ++s;
//     }

//     while (*s >= '0' && *s <= '9')
//         val = val * 10 + *s++ - '0';

//     return val * sign;
// }

int trim_end(char str[], int len) {
    int i = len - 1;

    while (i > 0 && (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'))
        str[i--] = '\0';

    return ++i;
}

int trim_beginning(char str[]) {
    char *read, *write;
    read = write = str;

    while (*read == ' ' || *read == '\n' || *read == '\t')
        ++read;

    while (*read != '\0')
        *write++ = *read++;

    *write = '\0';

    return write - str;
}

int trim(char str[]) {
    int len = trim_beginning(str);
    return trim_end(str, len);
}

void formatbytes(char str[], void *bytes, unsigned bytes_n) {
    unsigned i;
    unsigned char *b;
    unsigned char *cbytes = bytes;
    unsigned char ii;
    str[bytes_n * 8] = '\0';

    for (b = cbytes; (i = (unsigned) (b - cbytes)) < bytes_n; ++b)
        for (ii = 0; ii < 8; ++ii)
            str[bytes_n * 8 - (i + 1) * 8 + ii] =
                *b & (1 << (8 - ii - 1)) ? '1' : '0';
}
