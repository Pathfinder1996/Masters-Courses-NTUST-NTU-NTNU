/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

int** construct2DArray(int* original, int originalSize, int m, int n, int* returnSize, int** returnColumnSizes) {
    if (originalSize != (m * n)) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    *returnSize = m;
    *returnColumnSizes = malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
    }

    int** result = malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++) {
        result[i] = malloc(sizeof(int) * n);
    }

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = original[count];
            count = count + 1;
        }
    }

    return result;
}
