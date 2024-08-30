#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n;
	scanf("%d", &n);
	
	int *array = malloc(sizeof(int) * n);
	
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &array[i]);
	}
	
	int w, x, y, z;
	scanf("%d", &w);
	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &z);
	
	long long int total = 0;
	int age;
	for (i = 0; i < n; i++) {
		age = array[i];
		if (age >= 65 && age <= 79) {
			total = total + w;
		}
		else if (age >= 80 && age <= 89) {
			total = total + x;
		}
		else if (age >= 90 && age <= 99) {
			total = total + y;
		}
		else if (age >= 100) {
			total = total + z;
		}
	}
	printf("%lld", total);
}
