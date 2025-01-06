#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findNextMin(int *array, int n, int num);

int main() {
    int n;
    scanf("%d", &n);

    int *array = malloc(sizeof(int) * n);

    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
//        printf("%d ", array[i]);
    }

    int first_min = INT_MAX;
    for (i = 0; i < n; i++) {
        if (array[i] < first_min) {
            first_min = array[i];
        }
    }

    int sec_min = findNextMin(array, n, first_min);
    int third_min = findNextMin(array, n, sec_min);

    printf("%d\n", third_min);

    free(array);

    return 0;
}

int findNextMin(int *array, int n, int num) {
    int next_min = INT_MAX;
    
    int i;
    for (i = 0; i < n; i++) {
        if (array[i] > num && array[i] < next_min) {
            next_min = array[i];
        }
    }

    return next_min;
}
