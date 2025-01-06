#include <stdio.h>
#include <stdlib.h>

void quickSort(int *array, int p, int r);
int hoarePartition(int *array, int left, int right);
void swap(int *a, int *b);

int main() {
    int n;
    scanf("%d", &n);

    int *array = malloc(sizeof(int) * n);

    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    quickSort(array, 0, n - 1);

    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    free(array);

    return 0;
}

void quickSort(int *array, int p, int r) {
    if (p < r && p >= 0 && r >= 0) {
        int j = hoarePartition(array, p, r);
        quickSort(array, p, j);
        quickSort(array, j + 1, r);
    }
}

int hoarePartition(int *array, int left, int right) {
    int pivot = array[left];
    int i = left - 1;
    int j = right + 1;

    while(1) {
        do {
            i = i + 1;
        } while (array[i] < pivot);

        do {
            j = j - 1;
        } while (array[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(&array[i], &array[j]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
