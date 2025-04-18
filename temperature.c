#include <stdio.h>

#define LOWER -20
#define UPPER 40
#define STEP 5
#define FLOWER 0
#define FUPPER 200
#define FSTEP 20

void c2f(int lower, int upper, int step) {
    float fahr, celsius;

    celsius = lower;

    while (celsius <= upper) {
        fahr = celsius * (9.0 / 5.0) + 32;
        printf("%3.0f\t%3.2f\n", celsius, fahr);
        celsius += step;
    }
}

void f2c(int lower, int upper, int step) {
    float fahr, celsius;

    fahr = lower;

    while (fahr <= upper) {
        /* celsius = 5 * (fahr - 32) / 9; */
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f\t%3.2f\n", fahr, celsius);
        celsius = (fahr - 32) / (9.0 / 5.0);
        printf("%3.0f\t%3.2f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void f2c_for(int lower, int upper, int step) {
    int fahr;
    for (fahr = upper; fahr >= lower; fahr -= step) {
        printf("%3d\t%3.2f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }
}

int main() {
    c2f(LOWER, UPPER, STEP);
    printf("\n\n");
    f2c(FLOWER, FUPPER, FSTEP);
    printf("\n\n");
    f2c_for(FLOWER, FUPPER, FSTEP);
    return 0;
}
