#ifndef INC_5B_MATRIX_H
#define INC_5B_MATRIX_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "../structs/matrix.c"
#include "array.h"

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix m);

void inputMatrices(matrix *ms, int nMatrices);

void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));

bool isSquareMatrix(matrix m);

#endif //INC_5B_MATRIX_H
