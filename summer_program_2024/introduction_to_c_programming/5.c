#include <stdio.h>

int main(void) {
	long long int num;
	
	scanf("%lld", &num);
	
	while (num > 0) {
		num = (num * 2) / 3;
		printf("%lld\n", num);
	}
}
