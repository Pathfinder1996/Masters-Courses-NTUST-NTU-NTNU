#include <stdio.h>

int main(void) {	
	int n;
	scanf("%d\n", &n);
	
	int num, pow, count = 0;
	
	while (count < n) {
		scanf("%d", &num);
		pow = num * num;
		printf("%d\n", pow);

		count = count + 1;
	}

	return 0;	
}
