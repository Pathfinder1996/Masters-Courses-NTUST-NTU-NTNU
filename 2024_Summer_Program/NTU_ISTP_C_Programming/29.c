#include <stdio.h>

int main() {	
	int score;
	scanf("%d", &score);
	
	if (score < 60 && score >=0) {
		printf("F");
	}
	
	else if (score >= 60 && score < 70) {
		printf("C");
	}
	
	else if (score >= 70 && score < 80) {
		printf("B");
	}
	
	else if (score >= 80 && score <= 100) {
		printf("A");
	}
	
	else {
		printf("X");
	}
}
