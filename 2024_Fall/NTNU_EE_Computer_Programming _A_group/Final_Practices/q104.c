#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_L 4

int main() {
    int *array = malloc(sizeof(int) * MAX_L);

    int i, j, n, level;
    for (i = 0; i < 4; i++) {
        scanf("%d", &n);
        int count = 0;
        for (j = 0; j < n; j++) {
            scanf("%d", &level);
            if (level >= n) {
                count = count + 1;
            }
        }
        array[i] = count;
    }

    // for (i = 0; i < 4; i++) {
    //     printf("%d ", array[i]);
    // }
    // printf("\n");

    // 1st
    int first_index;
    int max_num = INT_MIN;
    for (i = 0; i < MAX_L; i++) {
        if (array[i] >= max_num) {
            max_num = array[i];
            first_index = i;
        }
    }
    // printf("%d %d\n", max_num, index);
    printf("%c ", first_index + 65);

    // 2nd
    int sec_index;
    int sec_num = INT_MIN;
    for (i = 0; i < MAX_L; i++) {
        if (i != first_index && array[i] <= max_num && array[i] >= sec_num) {
            sec_num = array[i];
            sec_index = i;
        }
    }
    printf("%c ", sec_index + 65);

    // 3rd
    int third_index;
    int third_num = INT_MIN;
    for (i = 0; i < MAX_L; i++) {
        if (i != first_index &&  i != sec_index && array[i] <= sec_num && array[i] >= third_num) {
            third_num = array[i];
            third_index = i;
        }
    }
    printf("%c ", third_index + 65);

    // last
    int last_index;
    for (i = 0; i < MAX_L; i++) {
        if (i != first_index &&  i != sec_index && i != third_index) {
            last_index = i;
        }
    }
    printf("%c ", last_index + 65);

    free(array);

    return 0;
}
