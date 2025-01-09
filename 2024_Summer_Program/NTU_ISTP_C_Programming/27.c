#include <stdio.h>

int main(void) {
    int n, count = 0;

    while (scanf("%d", &n) == 1) {
    	if (n != -1) {
    		printf("%d\n", (n * n));
		}
		else {
			count = count + 1;
		}
    }
    printf("%d\n", count);
}
