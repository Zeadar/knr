#include <stdio.h>
int binsearch_original(int x, int *v, int n);
int binsearch_improved(int x, int *v, int n);

#define ARRSIZE 1024
int main() {
    int arr[ARRSIZE];
    int i, result;
    for (i = 0; i < ARRSIZE; ++i)
        arr[i] = i;


    result = binsearch_original(79, arr, i);
    printf("original %d\n", result);
    result = binsearch_improved(79, arr, i);
    printf("improved %d\n", result);


}

int binsearch_improved(int x, int *v, int n) {
    /*
       Can't figure this one out, requires too much algorithm practise.
       ChatGTP couldn't figure it out either. AI won't replace good
       programmer. But it might replace me.
     */
    int low, mid, high;

    low = 0;
    high = n - 1;

    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }

    return x == v[low] ? mid : -1;
}

int binsearch_original(int x, int *v, int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid + 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;

}
