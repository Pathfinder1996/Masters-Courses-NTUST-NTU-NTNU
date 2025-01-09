#include <stdio.h>
#include <stdlib.h>
#define MAX_L 9

int main() {
    
    int *array = malloc(sizeof(int) * MAX_L);

    int i;
    for (i = 0; i < MAX_L; i++) {
        scanf("%d", &array[i]);
    }

    // for (i = 0; i < MAX_L; i++) {
    //     printf("%d", array[i]);
    // }

    printf("%d", (array[0] * (array[4] * array[8] - array[5] * array[7])) 
    - (array[1] * (array[3] * array[8] - array[5] * array[6]))
    + (array[2] * (array[3] * array[7] - array[4] * array[6])));

    return 0;
}
