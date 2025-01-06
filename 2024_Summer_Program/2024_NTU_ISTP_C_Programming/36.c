#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int N, A = 0;
	scanf("%d", &N);
	getchar();
	
	int i;
	char input[100];
	for (i = 0; i < N; i++) {
		if(fgets(input, sizeof(input), stdin) != NULL) {
			char *endptr;
			long long num = strtol(input, &endptr, 10);
			if (*endptr == '\n' || *endptr == '\0') {
				A = A + num;
				printf("%d\n", A);	
			}
			else {
				printf("not an integer\n");
			}
		}
	}
}
