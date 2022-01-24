#ifndef INC_5B_ARRAY_H
#define INC_5B_ARRAY_H

#include <stdio.h>

void swap(int *const a, int *const b);

void inputArray(int *a, const size_t n);

void outputArray(int *a, const size_t n);

void append(int *a, size_t *n, int x);

int getMinElemArray(const int *a, size_t n);

int getMaxElemArray(const int *a, size_t n);

#endif //INC_5B_ARRAY_H