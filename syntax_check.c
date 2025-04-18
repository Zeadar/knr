#include "libkalle.c"

#define MAXSIZE 1024

int is_symbol(char c);

int main() {
    char symbol[MAXSIZE] = { 0 };
    char buffer[MAXSIZE] = { 0 };
    int nline[MAXSIZE] = { 0 };
    int position[MAXSIZE] = { 0 };
    int i, len, s, p, l, lc;
    s = p = l = lc = 0;

    while ((len = readline(buffer, MAXSIZE))) {
        ++lc;
        for (i = 0; i != len; ++i) {
            if (is_symbol(buffer[i])) {
                symbol[s++] = buffer[i];
                nline[l++] = lc;
                position[p++] = i + 1;
            }
        }
    }

    return 0;
}

int is_symbol(char c) {
    return c == '{' || c == '}' || c == '\'' || c == '"' || c == '('
        || c == ')';
}
