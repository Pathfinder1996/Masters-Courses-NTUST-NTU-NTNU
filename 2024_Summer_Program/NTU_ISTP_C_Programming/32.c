#include <stdio.h>
#define MAXL 1001

void arrayDelete(int array[], int, int);
void insertionSort(int array[], int);

int main(void) {
	int array[MAXL];
	
	int n;
	scanf("%d", &n);
	
	int i, nums;
	for (i = 0; i < n; i++) {
		scanf("%d", &nums);
		array[i] = nums;
//		printf("%d ", array[i]);
	}
	
	int j;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (array[i] == array[j]) {
				arrayDelete(array, n, j);
				j = j - 1;
				n = n - 1;
			}
		}
	}
	
	insertionSort(array, n);

    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
}

void arrayDelete(int array[], int size, int index) {
	int i;
	for (i = index; i < size; i++) {
		array[i] = array[i + 1];
	}
	array[size - 1] = 0;
}

void insertionSort(int array[], int size) {
	int i, j, temp;
	for (i = 0; i < size; i++) {
		j = i;
		while (j > 0 && array[j - 1] > array[j]) {
			temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;
			j = j - 1;
		}
	}
}
