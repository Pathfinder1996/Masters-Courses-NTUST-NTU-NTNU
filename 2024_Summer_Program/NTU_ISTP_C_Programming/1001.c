#include <stdio.h>

int main(void) {
	int high;
	scanf("%d", &high);
	
	int i, number[high];
	for (i = 0; i < high; i++){
		scanf("%d", &number[i]);
	}
	
	int down = 0;
	for (i = 1; i < high; i++){
		if (number[i] < number[i - 1]){
			down = 1;
			break;
		}
	}
	
	if (down) {
		printf("NO\n");
	}
	else{
		printf("YES\n");
	}
  
	return 0;
}
