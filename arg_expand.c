#include "types.h"
#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    s32 s32val;
    f64 dval;
    va_start(ap, fmt);

    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
        case 'd':
            s32val = va_arg(ap, s32);
            printf("%d", s32val);
            break;
        case 's':
            sval = va_arg(ap, char *);
            printf("%s", sval);
            break;
        case 'f':
            dval = va_arg(ap, f64);
            printf("%f", dval);
            break;
        default:
            putchar(*p);
            break;
        }
    }

    va_end(ap);
}

int main() {

    minprintf("%s %d %f\n", "Hello", 10, 11.11);

    return 0;
}
