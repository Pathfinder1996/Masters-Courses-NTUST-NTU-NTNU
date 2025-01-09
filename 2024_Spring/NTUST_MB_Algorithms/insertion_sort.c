#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

void insertionSort(int *array, int size);
void showArray(int *array, int size);

int main(void) {
    int *array = malloc(sizeof(int) * SIZE);
    
    int i;
    for (i = 0; i < SIZE; i++) {
        scanf("%d ", &array[i]);
    }

    printf("排序前: ");
    showArray(array, SIZE);
    printf("\n");

    insertionSort(array, SIZE);

    free(array);

    return 0;
}

void insertionSort(int *array, int size) {
    int i, j, base;
    for (i = 1; i < size; i++) {                                    //C1
        base = array[i];                                            //C2
        // insert array[i] into the sorted sequence array[0..i-1]
        j = i - 1;                                                  //C4
        while (j >= 0 && array[j] > base) {                         //C5
            array[j + 1] = array[j];                                //C6
            j = j - 1;                                              //C7
        }
        array[j + 1] = base;                                        //C8
        printf("第 %d 次整理: ", i);
        showArray(array, SIZE);
    }
}

void showArray(int *array, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}