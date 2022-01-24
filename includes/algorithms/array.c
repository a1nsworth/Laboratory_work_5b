#include "array.h"

void swap(int *const a, int *const b) {
    const int t = *a;
    *a = *b;
    *b = t;
}

void inputArray(int *const a, const size_t n) {
    for (size_t i = 0; i < n; ++i)
        scanf("%d", &a[i]);
}

void outputArray(int *const a, const size_t n) {
    for (size_t i = 0; i < n; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

void append(int *const a, size_t *n, const int x) {
    a[*n] = x;
    (*n)++;
}

int getMinElemArray(const int *const a, const size_t n) {
    int elemMin = a[0];
    for (size_t i = 1; i < n; ++i)
        if (a[i] < elemMin)
            elemMin = a[i];

    return elemMin;
}

int getMaxElemArray(const int *const a, const size_t n) {
    int elemMax = a[0];
    for (size_t i = 1; i < n; ++i)
        if (a[i] > elemMax)
            elemMax = a[i];

    return elemMax;
}