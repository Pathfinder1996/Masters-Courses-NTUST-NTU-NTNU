#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
void quickSort(int *array, int left, int right);
int hoarePartition(int *array, int left, int right);

int main() {
    int input;
    scanf("%d", &input);

    int *array = malloc(sizeof(int) * input);

    for (int i = 0; i < input; i++) {
        scanf("%d", &array[i]);
    }

    printf("排序前: ");
    for (int i = 0; i < input; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    quickSort(array, 0, input - 1);

    printf("排序後: ");
    for (int i = 0; i < input; i++) {
        printf("%d ", array[i]);
    }

    free(array); 

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int hoarePartition(int *array, int left, int right) {
    int pivot = array[left];
    int i = left - 1;
    int j = right + 1;
    while (1) {
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

void quickSort(int *array, int left, int right) {
    if (left >= 0 && right >= 0 && left < right) {
        int p = hoarePartition(array, left, right);
        quickSort(array, left, p);
        quickSort(array, p + 1, right);
    }
}
