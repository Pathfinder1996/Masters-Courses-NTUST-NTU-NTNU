#include <stdio.h>

int main() {
    int m, n;
    while(scanf("%d %d", &m, &n) != EOF) {
        // printf("%d %d\n", m, n);
        int num;
        int array[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &num);
                // printf("%d ", num);
                array[i][j] = num;
            }
            // printf("\n");
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", array[j][i]);
            }
            printf("\n");
        }
    }

    return 0;
}
