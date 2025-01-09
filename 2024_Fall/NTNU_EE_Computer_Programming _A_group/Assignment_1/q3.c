#include <stdio.h>
#include <stdlib.h>

int main() {
    int n1, i;
    scanf("%d ", &n1);
    int *array1 = malloc(sizeof(int) * n1);
    for (i = 0; i < n1; i++) {
        scanf("%d ", &array1[i]);
    }

    // for(i = 0; i < n1; i++) {
    //     printf("%d ", array1[i]);
    // }

    int n2;
    scanf("%d ", &n2);
    int *array2 = malloc(sizeof(int) * n2);
    for (i = 0; i < n2; i++) {
        scanf("%d ", &array2[i]);
    }

    // for(i = 0; i < n2; i++) {
    //     printf("%d ", array2[i]);
    // }

    // int *array3 = malloc(sizeof(int) * (n1 + n2));
    int *p1 = array1;
    int *p2 = array2;

    // printf("%d %d", *p1, *p2);

    int q = 0, w = 0;
    while(q < n1 && w < n2) {
        if (array1[q] <= array2[w]) {
            printf("%d ", array1[q]);
            q = q + 1;
        }
        else {
            printf("%d ", array2[w]);
            w = w + 1;
        }
    }

    while (q < n1) {
        printf("%d ", array1[q]);
        q = q + 1;
    }

    while (w < n2) {
        printf("%d ", array2[w]);
        w = w + 1;
    }

    free(array1);
    free(array2);

    return 0;
}
