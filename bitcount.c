#include <stdio.h>
int bitcount_original(unsigned);
int bitcount_better(unsigned);

int main() {
    unsigned test_value = 7851;

    printf("original:\tbits in %b is %d\n", test_value,
           bitcount_original(test_value));
    printf("better: \tbits in %b is %d\n", test_value,
           bitcount_better(test_value));
}

int bitcount_original(unsigned x) {
    int b = 0;

    while (x != 0) {
        if (x & 01)
            ++b;

        x >>= 1;
    }

    return b;
}

int bitcount_better(unsigned x) {
    int b = 0;

    while (x) {
        x &= (x - 1);
        ++b;
    }

    return b;
}
