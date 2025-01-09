#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100000

int main() {
    int array[MAX_SIZE];
    int count = 0;
    int num;

    while (1) {
        scanf("%d", &num);

        if (num == -1) {
            break;
        }
        array[count] = num;
        count = count + 1;
    }

    int i;
    for (i = 0; i < count; i++) {
        int j, current = array[i];
        for (j = 0; j < i; j++) {
            if (array[j] == current) {
                printf("%d again at %d\n", current, i);
                break;
            }
        }
    }

    return 0;
}
