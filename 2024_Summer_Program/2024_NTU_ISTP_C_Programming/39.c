#include <stdio.h>

int main(void) {
	double r, pi, area, circumference;
	scanf("%lf", &r);
	
	pi = 3.1415926;
	area = pi * (r * r);
	circumference = (2 * pi) * r;
	
	printf("area = %.3lf\n", area);
	printf("circumference = %08.2lf\n", circumference);
}
