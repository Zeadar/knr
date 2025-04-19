#include <stdio.h>
#define swap(t, x, y) { t tmp = x; x = y; y = tmp; }
#define print(s, a, b) printf(#s " " #s "\n", a ,b)

int main() {
    int x = 10;
    int y = 20;

    print(%d, x, y);
    swap(int, x, y);
    print(%d, x, y);

    double a = 40;
    double b = 60;

    print(%f, a, b);
    swap(double, a, b);
    print(%f, a, b);

    return 0;
}
