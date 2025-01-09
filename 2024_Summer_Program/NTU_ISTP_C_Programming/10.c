#include <stdio.h>

int main(void) {
	float a, b, c, x, sum;
	
	scanf("%f", &a);
	scanf("%f", &b);
	scanf("%f", &c);
	scanf("%f", &x);
	
	sum = a + b + c;
	
	if (sum == x) {
		printf("==");
	}
	else {
		printf("!=");
	}
}
