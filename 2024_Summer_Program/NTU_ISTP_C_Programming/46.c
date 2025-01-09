#include <stdio.h>

int main(void) {
    int N, M;
    int matrix[71][71];

    scanf("%d %d", &N, &M);
	
	int i, j;
	for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (j = 0; j < M; j++) {
        for (i = 0; i < N; i++) {
            printf("%d", matrix[i][j]);
            
            if (i < N - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
