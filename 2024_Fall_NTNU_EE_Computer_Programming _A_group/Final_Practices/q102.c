#include <stdio.h>

int main() {
    int w, h, o;
    scanf("%d %d %d", &w, &h, &o);
    getchar();
    getchar();

    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int c = getchar();
            int sum = c + o;
            if (sum > 127) {
                sum = sum % 127;
            }
            if (sum < 32) {
                sum = sum + 32;
            }
            printf("%c", sum);
        }
        printf("\n");
        getchar();
        getchar();
    }

    return 0;
}
