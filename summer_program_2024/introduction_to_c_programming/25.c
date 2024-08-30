#include <stdio.h>

int main(void) {
	int i, pixel[3];
	
	for (i=0; i<3; i++) {
		scanf("%d", &pixel[i]);
		
		if  (pixel[i] < 0) {
			pixel[i] = 0;
		}
		else if (pixel[i] > 255) {
			pixel[i] = 255;
		}
	}
  
	printf("%d %d %d\n", pixel[0], pixel[1], pixel[2]);
}
