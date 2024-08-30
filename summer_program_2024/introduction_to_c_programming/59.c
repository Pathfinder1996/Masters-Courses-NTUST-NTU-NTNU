#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b);

int main(void) {
    int N;
    int *array;

    scanf("%d", &N);
    array = malloc(sizeof(int) * N);

    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    qsort(array, N, sizeof(int), compare);

    printf("%d", array[0]);
    for (i = 1; i < N; i++) {
        if (array[i] != array[i - 1]) {
            printf(" %d", array[i]);
        }
    }

    free(array);

    return 0;
}

int compare(const void *a, const void *b) {
    int ina = *(int *)a;
	int inb = *(int *)b;

	if (ina < inb) {
		return -1;
	}
	if (ina > inb) {
		return 1;
	}
	return 0;
}
