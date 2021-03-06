#include "includes/algorithms/matrix.h"

void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMaxElemArray);
}

void sortColsByMinElement(matrix m) {
    selectionSortColsMatrixByColCriteria(m, getMinElemArray);
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m))
        *m = mulMatrices(*m, *m);
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    int *arraySum = (int *) calloc(m.nRows, sizeof(int));
    printExitCodeIfPtrIsNull(arraySum);

    for (register size_t i = 0; i < m.nRows; ++i)
        arraySum[i] += getSumArrayLL(m.values[i], m.nCols);

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

int findSumOfMaxesOfPseudoDiagonal(const matrix m) {
    assert(m.nRows != 0 || m.nCols != 0);

    // Массив максимумов из псевдогоналей матрицы
    const int sizeArray = m.nRows + m.nCols - 1;
    int *arrayMaxElemsPseudoDiagonal = (int *) malloc(sizeArray * sizeof(int));
    printExitCodeIfPtrIsNull(arrayMaxElemsPseudoDiagonal);
    for (register size_t i = 0; i < sizeArray; ++i)
        arrayMaxElemsPseudoDiagonal[i] = INT_MIN;

    for (register size_t i = 0; i < m.nRows; ++i) {
        for (register size_t j = 0; j < m.nCols; ++j) {
            int indexArray = j + m.nRows - 1 - i;
            if (m.values[i][j] > arrayMaxElemsPseudoDiagonal[indexArray])
                arrayMaxElemsPseudoDiagonal[indexArray] = m.values[i][j];
        }
    }
    arrayMaxElemsPseudoDiagonal[m.nRows - 1] = 0;

    int sum = getSumArrayLL(arrayMaxElemsPseudoDiagonal, sizeArray);

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

void sortByDistancesByNonDecreasing(matrix m) {
    insertionSortRowsMatrixByRowCriteriaD(m, getVectorLength);
}

unsigned countEqClassesByRowsSum(const matrix m) {
    assert(m.nRows > 0 && m.nCols > 0);

    int *arraySumsRows = (int *) malloc(m.nRows * sizeof(int));
    printExitCodeIfPtrIsNull(arraySumsRows);

    for (register size_t i = 0; i < m.nRows; ++i)
        arraySumsRows[i] = getSumArrayLL(m.values[i], m.nCols);

    insertionSort(arraySumsRows, m.nRows, isIncreasing);

    unsigned counterEqual = 0;
    int lastNumber = arraySumsRows[0];
    bool isLowTwo = true;
    for (register size_t i = 1; i < m.nRows; ++i) {
        int currentNumber = arraySumsRows[i];
        if (currentNumber == lastNumber && isLowTwo) {
            counterEqual++;
            isLowTwo = false;
        } else if (currentNumber != lastNumber)
            isLowTwo = true;

        lastNumber = currentNumber;
    }

    free(arraySumsRows);

    return counterEqual;
}

unsigned getCounterSpecialElement(const matrix m) {
    assert(m.nRows > 0 && m.nCols > 0);

    if (m.nRows == 1 && m.nCols == 1)
        return 0;

    // Массив для хранения столбца
    int *arraySumColumn = (int *) malloc(m.nCols * sizeof(int));
    printExitCodeIfPtrIsNull(arraySumColumn);

    // Массив для хранения суммы стобца
    int *arrayColumn = (int *) (malloc(m.nRows * sizeof(int)));
    printExitCodeIfPtrIsNull(arrayColumn);

    unsigned counterSpecial = 0;
    for (register size_t i = 0; i < m.nCols; ++i) {
        for (register size_t j = 0; j < m.nRows; ++j)
            arrayColumn[j] = m.values[j][i];

        arraySumColumn[i] = getSumArrayLL(arrayColumn, m.nRows);
        int maxElementColumn = getMaxElemArray(arrayColumn, m.nRows);
        if (arraySumColumn[i] - maxElementColumn < maxElementColumn)
            counterSpecial++;
    }
    free(arrayColumn);
    free(arraySumColumn);

    return counterSpecial;
}

void swapPenultimateRow(matrix m, const size_t indexColumn) {
    assert(m.nRows > 1 && m.nCols > 0);

    const size_t swapRowIndex = m.nRows - 2;
    const bool isLargeMiddle = indexColumn >= m.nCols / 2;
    int swapColIndex = isLargeMiddle ? 0 : m.nCols - 1;
    for (register size_t i = 0, rowForColumn = 0; i < m.nRows; ++i, rowForColumn++) {
        m.values[swapRowIndex][swapColIndex] = m.values[rowForColumn][indexColumn];
        swapColIndex = isLargeMiddle ? swapColIndex + 1 : swapColIndex - 1;
    }
}

unsigned getCountNonDescendingRowsMatrices(const matrix *ms, const size_t nMatrix) {
    unsigned counterMatrix = 0;
    for (register size_t i = 0; i < nMatrix; ++i)
        if (hasAllSortByRows(ms[i], isNonDecreasing))
            counterMatrix++;
    return counterMatrix;
}

void printMatrixWithMaxZeroRows(const matrix *ms, const size_t nMatrix) {
    int *arrayCounterZeroRows = (int *) malloc(nMatrix * sizeof(int));
    printExitCodeIfPtrIsNull(arrayCounterZeroRows);

    for (register size_t i = 0; i < nMatrix; ++i)
        arrayCounterZeroRows[i] = getCounterZeroRows(ms[i]);
    int maxCounterZeroRows = getMaxElemArray(arrayCounterZeroRows, nMatrix);

    for (register size_t i = 0; i < nMatrix; ++i)
        if (arrayCounterZeroRows[i] == maxCounterZeroRows)
            outputMatrix(ms[i]);

    free(arrayCounterZeroRows);
}

void printMinMatrixWithMaxAbsElement(const matrixD *ms, const size_t nMatrix) {
    double *arrayMaxAbsElemMatrix = (double *) malloc(nMatrix * sizeof(double));
    printExitCodeIfPtrIsNull(arrayMaxAbsElemMatrix);

    for (register size_t i = 0; i < nMatrix; ++i)
        arrayMaxAbsElemMatrix[i] = getMaxElementMatrixByAbsD(ms[i]);
    double minAbsElement = getMinElementD(arrayMaxAbsElemMatrix, nMatrix);

    for (register size_t i = 0; i < nMatrix; ++i)
        if (fabs(arrayMaxAbsElemMatrix[i] - minAbsElement) < DBL_EPSILON)
            outputMatrixD(ms[i]);

    free(arrayMaxAbsElemMatrix);
}

void getSpecialArrayMax(int *a, const size_t n, const int *b) {
    memcpy(a, b, n * sizeof(int));
    for (register size_t i = 1; i < n; ++i)
        a[i] = max(a[i], a[i - 1]);
}

void getSpecialArrayMin(int *a, const size_t n, const int *b) {
    memcpy(a, b, n * sizeof(int));
    for (register int i = (int) n - 2; i >= 0; --i)
        a[i] = min(a[i], a[i + 1]);
}

unsigned getCountSpecialElementsInArray(const int *a, const size_t n, const int *aMax, const int *aMin) {
    unsigned counterSpecialElements = 0;
    for (register size_t i = 0; i < n; ++i) {
        if (i != 0 && i != n - 1) {
            if (a[i] > aMax[i - 1] && a[i] < aMin[i + 1])
                counterSpecialElements++;
        } else if (i == 0) {
            if (a[i] < aMin[i + 1])
                counterSpecialElements++;
        } else if (i == n - 1) {
            if (a[i] > aMax[i - 1])
                counterSpecialElements++;
        }
    }

    return counterSpecialElements;
}

unsigned getCountSpecialElementsInMatrixRows(const matrix m) {
    assert(m.nCols > 0 && m.nRows > 0);

    if (m.nCols < 2)
        return 0;

    unsigned counterSpecialElements = 0;
    int *arrayMax = (int *) malloc(m.nCols * sizeof(int));
    printExitCodeIfPtrIsNull(arrayMax);
    int *arrayMin = (int *) malloc(m.nCols * sizeof(int));
    printExitCodeIfPtrIsNull(arrayMin);

    for (register size_t i = 0; i < m.nRows; ++i) {
        getSpecialArrayMax(arrayMax, m.nCols, m.values[i]);
        getSpecialArrayMin(arrayMin, m.nCols, m.values[i]);

        counterSpecialElements += getCountSpecialElementsInArray(m.values[i], m.nCols, arrayMax, arrayMin);
    }
    free(arrayMin);
    free(arrayMax);

    return counterSpecialElements;
}

int scalarProductTwoVectors(const int *a, const size_t n, const int *b) {
    int product = 0;
    for (register size_t i = 0; i < n; ++i)
        product += a[i] * b[i];
    return product;
}

double valueCosBtwTwoVectors(const int *a, const size_t n, const int *b) {
    double scalProd = scalarProductTwoVectors(a, n, b);
    double l1 = getVectorLength(a, n);
    double l2 = getVectorLength(b, n);
    return scalProd / (l1 * l2);
}

size_t getVectorIndexWithMaxAngle(matrix m, const int *b) {
    double *arrayCos = (double *) malloc(m.nRows * sizeof(double));
    printExitCodeIfPtrIsNull(arrayCos);

    for (register size_t i = 0; i < m.nRows; ++i)
        arrayCos[i] = valueCosBtwTwoVectors(m.values[i], m.nCols, b);

    size_t maxIndexRow = getMinIndexElemArrayD(arrayCos, m.nRows);
    free(arrayCos);

    return maxIndexRow;
}

double scalarProductTwoVectorsD(const double *a, const size_t n, const double *b) {
    double product = 0;
    for (register size_t i = 0; i < n; ++i)
        product += a[i] * b[i];
    return product;
}

double getSpecialScalarProduct(matrixD m) {
    // Получение вспомогательного массива и массива со значением в столбцах
    double *arrayColumn = (double *) malloc(m.nRows * sizeof(double));
    printExitCodeIfPtrIsNull(arrayColumn);

    const size_t minIndexCol = getMinValuePosD(m).colIndex;
    for (register size_t j = 0; j < m.nRows; ++j)
        arrayColumn[j] = m.values[j][minIndexCol];

    double scalarProduct = scalarProductTwoVectorsD(arrayColumn, m.nRows, m.values[getMaxValuePosD(m).rowIndex]);
    free(arrayColumn);

    return scalarProduct;
}