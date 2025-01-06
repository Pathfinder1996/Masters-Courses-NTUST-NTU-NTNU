#include <stdio.h>

int main(void) {
	int num, pow;

	do {	
		scanf("%d", &num);
		
		if (num != -1) {
			pow = num * num;
			printf("%d\n", pow); 
		}
	} while(num != -1);
}
