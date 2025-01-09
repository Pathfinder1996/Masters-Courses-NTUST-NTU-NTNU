#include <stdio.h>

int GCD(int i, int j);

int main() {
    int n, i, j;
    while(scanf("%d", &n) != EOF) {
        if (n == 0) {
            break;
        }
        int G = 0;
        for (i = 1; i < n; i++) {
            for (j = i + 1; j <= n; j++) {
                G = G + GCD(i, j);
            }
        }
        printf("%d\n", G);
    }

    return 0;
}

int GCD(int i, int j) {
    int temp;
    while (i % j != 0) {
        temp = j;
        j = i % j;
        i = temp;
    }

    return j;
}
