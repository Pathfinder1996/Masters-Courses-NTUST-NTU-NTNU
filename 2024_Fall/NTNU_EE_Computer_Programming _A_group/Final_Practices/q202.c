#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, c;
    scanf("%d %d", &n, &c);

    int *t = malloc(sizeof(int) * n);

    int i;
    for(i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }

    int count = 1;
    int pre_get = 0;
    int next_get;
    for (i = 1; i < n; i++) {
        next_get = i;
        if (t[next_get] - t[pre_get] >= c) {
            count = count + 1;
            pre_get = next_get;
        }
    }

    printf("%d", count);

    free(t);

    return 0;
}
