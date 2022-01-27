#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "includes/algorithms/matrix.h"

void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMaxElemArray);
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMinElemArray);
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m))
        *m = mulMatrices(*m, *m);
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    long long *arraySum = (long long *) calloc(m.nRows, sizeof(long long));
    for (register size_t i = 0; i < m.nRows; ++i)
        arraySum[i] += getSumArray(m.values[i], m.nCols);

    if (isUniqueArrayElements(arraySum, m.nRows))
        transposeSquareMatrix(m);

    free(arraySum);
}

bool isMutuallyInverseMatrices(const matrix m1, const matrix m2) {
    if (m1.nCols != m2.nRows)
        return false;

    const matrix m3 = mulMatrices(m1, m2);

    if (isEMatrix(m3))
        return true;
    else
        return false;
}

long long findSumOfMaxesOfPseudoDiagonal(const matrix m) {
    assert(m.nRows != 0 || m.nCols != 0);

    // Массив максимумов из псевдогоналей матрицы
    int *arrayMaxElemsPseudoDiagonal = (int *) malloc((m.nRows + m.nCols - 2) * sizeof(int));
    size_t sizeArrayMaxElemsPseudoDiagonal = 0;

    // Поиск максимальных значений на псевдогоналях слева и справа от главной диагонали
    position leftI = {1, 0};
    position rightI = {0, 1};
    while (leftI.rowIndex < m.nRows && leftI.colIndex < 1 ||
           rightI.colIndex < m.nCols && rightI.rowIndex < 1) {

        // Поиск слева
        if (leftI.rowIndex < m.nRows && leftI.colIndex < 1) {
            int maxElemLeft = m.values[leftI.rowIndex][leftI.colIndex];
            for (register size_t i = leftI.rowIndex + 1, j = leftI.colIndex + 1; i < m.nRows && j < m.nCols; ++i, ++j)
                if (m.values[i][j] > maxElemLeft)
                    maxElemLeft = m.values[i][j];
            append(arrayMaxElemsPseudoDiagonal, &sizeArrayMaxElemsPseudoDiagonal, maxElemLeft);
            leftI.rowIndex++;
        }

        // Поиск справа
        if (rightI.colIndex < m.nCols && rightI.rowIndex < 1) {
            int maxElemRight = m.values[rightI.rowIndex][rightI.colIndex];
            for (register size_t i = rightI.rowIndex + 1, j = rightI.colIndex + 1; i < m.nRows && j < m.nCols; ++i, ++j)
                if (m.values[i][j] > maxElemRight)
                    maxElemRight = m.values[i][j];
            append(arrayMaxElemsPseudoDiagonal, &sizeArrayMaxElemsPseudoDiagonal, maxElemRight);
            rightI.colIndex++;
        }
    }

    long long sum = getSumArray(arrayMaxElemsPseudoDiagonal, sizeArrayMaxElemsPseudoDiagonal);

    free(arrayMaxElemsPseudoDiagonal);

    return sum;
}

int getMinInArea(const matrix m) {
    position maxElemPos = getMaxValuePos(m);
    int minElem = m.values[maxElemPos.rowIndex][maxElemPos.colIndex];

    int left = maxElemPos.colIndex;
    int right = left;
    for (register int i = maxElemPos.rowIndex; i >= 0; --i) {
        for (register size_t j = left; j <= right; ++j)
            if (m.values[i][j] < minElem)
                minElem = m.values[i][j];
        left = left > 0 ? left - 1 : left;
        right = right < m.nRows ? right + 1 : right;
    }

    return minElem;
}

// 1 задача>>>
/*
int main() {
    size_t n;
    scanf("%zd", &n);

    matrix m = getMemMatrix(n, n);
    inputMatrix(m);
    size_t indexMin = getMinValuePos(m).rowIndex;
    size_t indexMax = getMaxValuePos(m).rowIndex;
    swapRows(m, indexMin, indexMax);

    outputMatrix(m);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 2 задача>>>
/*
int main() {
    size_t n, m;
    scanf("%zd %zd", &n, &m);
    matrix matrix1 = getMemMatrix(n, m);
    inputMatrix(matrix1);
    sortRowsByMinElement(matrix1);

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 3 задача>>>
/*
int maint() {
    size_t n, m;
    scanf("%zd %zd", &n, &m);
    matrix matrix1 = getMemMatrix(n, m);
    inputMatrix(matrix1);
    sortColsByMinElement(matrix1);

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 4 задача>>>
/*
int main() {
    size_t n;
    scanf("%zd", &n);
    matrix matrix1 = getMemMatrix(n, n);
    inputMatrix(matrix1);
    getSquareOfMatrixIfSymmetric(&matrix1);

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 5 задача>>>
/*
int main() {
    size_t n;
    scanf("%zd", &n);
    matrix matrix1 = getMemMatrix(n, n);
    inputMatrix(matrix1);
    transposeIfMatrixHasEqualSumOfRows(matrix1);

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 6 задача>>>
/*
int main() {
    size_t n;
    scanf("%zd", &n);
    matrix matrix1 = getMemMatrix(n, n);
    inputMatrix(matrix1);

    size_t n2;
    scanf("%zd", &n2);
    matrix matrix2 = getMemMatrix(n2, n2);
    inputMatrix(matrix2);

    isMutuallyInverseMatrices(matrix1, matrix2);

    outputMatrix(matrix1);
    outputMatrix(matrix2);
    freeMemMatrix(matrix1);
    freeMemMatrix(matrix2);

    return 0;
}
*/

// 7 задача>>>
/*
int main() {
    size_t n, m;
    scanf("%zd %zd", &n, &m);
    matrix matrix1 = getMemMatrix(n, m);
    inputMatrix(matrix1);
    printf("%d \n", findSumOfMaxesOfPseudoDiagonal(matrix1));

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 8 задача>>>
/*
int main() {
    size_t n, m;
    scanf("%zd %zd", &n, &m);
    matrix matrix1 = getMemMatrix(n, m);
    inputMatrix(matrix1);
    printf("%d \n", getMinInArea(matrix1));

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}
*/

// 9 задача>>>
/**/

// 10 задача>>>
/**/

// 11 задача>>>
/**/

// 12 задача>>>
/**/

// 13 задача>>>
/**/

// 14 задача>>>
/**/

// 15 задача>>>
/**/


double getDistance(const int *a, const size_t n) {
    long long sum = 0;
    for (register size_t i = 0; i < n; ++i)
        sum += (a[i] * a[i]);
    return sqrt(sum);
}

void sortByDistancesByNonDecreasing(matrix m) {
    insertionSortRowsMatrixByRowCriteriaD(m, getDistance);
}

int main() {
    size_t n, m;
    scanf("%zd %zd", &n, &m);
    matrix matrix1 = getMemMatrix(n, m);
    inputMatrix(matrix1);
    sortByDistancesByNonDecreasing(matrix1);

    outputMatrix(matrix1);
    freeMemMatrix(matrix1);

    return 0;
}