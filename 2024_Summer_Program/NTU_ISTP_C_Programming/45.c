#include <stdio.h>
#define MAX_N 1000

int main(void) {
	int n;
	scanf("%d", &n);
	
	int i, scoreArr[MAX_N], passLine;
	for (i = 0; i < n; i++) {
		scanf("%d", &scoreArr[i]);
	}
	
	scanf("%d", &passLine);
	
	int allPassed = 1;
	for (i = 0; i < n; i++) {
		if (scoreArr[i] < passLine) {
			allPassed = 0;
			printf("%d: %d\n", i, scoreArr[i]);
		}
	}
	
	if (allPassed) {
		printf("All passed!\n");
	}
	
	return 0;
}
