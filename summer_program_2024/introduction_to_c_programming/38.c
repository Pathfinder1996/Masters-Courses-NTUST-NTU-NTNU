#include <stdio.h>
#include <stdlib.h>

int add(int, int, int);

int main(void) {	
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf("%d", add(a, b, c));
	
	return 0;
}

int add(int a, int b, int c) { 
	int sum;
	sum = a + b + c;
	return sum;
}
