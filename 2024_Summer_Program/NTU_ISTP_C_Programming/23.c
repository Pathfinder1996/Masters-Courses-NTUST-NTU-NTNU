#include <stdio.h>

int main(void) {
	int p, q, N;
	
	scanf("%d %d", &p, &q);
	scanf("%d", &N);
	
	int matrix_size = p * q;
	
	int i, j, array[N];
	
	for (i = 0; i < N; i++) {
		if (i < N - 1) {
			scanf("%d ", &array[i]);
		}
		else {
			scanf("%d", &array[i]);
		}
	}
	
	if (N != matrix_size) {
		printf("failed");
	}
	
	else {
	    for (i = 0; i < p; i++) {
	        for (j = 0; j < q; j++) {
	            printf("%d", array[i * q + j]);
	            if (j < q - 1) {
	                printf(" ");
	            }
	        }
	        printf("\n");
	    }
	}
}
