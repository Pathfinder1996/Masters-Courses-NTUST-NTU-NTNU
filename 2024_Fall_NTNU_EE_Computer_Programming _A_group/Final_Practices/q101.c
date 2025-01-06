#include <stdio.h>

int main() {
    int w, h;
    scanf("%d %d", &w, &h);
    getchar();
    getchar();

    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int c = getchar();
            printf("%d", c);
        }
        printf("\n");
        getchar();
        getchar();
    }

    return 0;
}
