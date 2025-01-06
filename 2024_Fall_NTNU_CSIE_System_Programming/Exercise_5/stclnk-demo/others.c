#include <math.h>
#include <string.h>
#include <stdio.h>

void additinalFunction() {
	double value = sqrt(123456.789);
	printf("test: %f\n", value);
}

void stringMul() {
	char buffer[100];
	strcpy(buffer, "Hello World!\n");
	strcat(buffer, "How are you?\n");
	printf("%s", buffer);
}
