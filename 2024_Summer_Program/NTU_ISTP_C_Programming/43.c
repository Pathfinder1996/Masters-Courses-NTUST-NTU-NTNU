#include <stdio.h>

int main(void) {
	int a, b;
	char op;
	
	scanf("%d %d ", &a, &b);
	scanf("%c", &op);
	
	if (op == '+') {
		printf("%d", a + b);
	} 
	
	if (op == '-') {
		printf("%d", a - b);
	}
	
	if (op == '*') {
		printf("%d", a * b);
	}
	
	if (op == '/') {
		printf("%d", a / b);
	}
}
