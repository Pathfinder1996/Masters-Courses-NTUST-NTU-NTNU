#include <stdio.h>

int main(void) {	
	int a, b, x;
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &x);
	
	int i, count = 0;
	for (i = a; i <= b; i++) {
		if (i % x == 0) {
			count = count + 1;
		}
	}
	printf("%d\n", count);
}
