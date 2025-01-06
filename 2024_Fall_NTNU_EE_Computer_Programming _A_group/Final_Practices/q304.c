#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10000000
#define ARRAY_MOD 10000019 

int main() {
    int *array = malloc(sizeof(int) * MAX_SIZE);

    array[0] = 2;
    array[1] = 1;

    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        array[i] = (array[i - 1] + array[i - 2]) % ARRAY_MOD;
    }

    int n;
    scanf("%d", &n);

    int num;
    for (i = 0; i < n; i++) {
        scanf("%d", &num);
        printf("%d\n", array[num]);
    }

    return 0;
}
