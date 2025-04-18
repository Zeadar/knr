#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellsort(int v[], int n) {
    int gap, i, j, temp;

    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; ++i)
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}

void randarray(int v[], int n) {
    srand(time(0));
    --n;

    for (; n > 0; --n)
        v[n] = rand();
}

int main() {
    int numbers[10];

    randarray(numbers, 10);

    for (int i = 0; i < 10; ++i)
        printf("%d ", numbers[i]);
    printf("\n");

    shellsort(numbers, 10);

    for (int i = 0; i < 10; ++i)
        printf("%d ", numbers[i]);
    printf("\n");

    return 0;
}
