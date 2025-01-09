#include <stdio.h>
#include <string.h>

int main(void) {
	char str[101];
	scanf("%s", str);
	
	int len = strlen(str);
//	printf("%d", len);
	
	int left = 0, right = len - 1;
	int restring = 1;
	while (left < right) {
		if (str[left] != str[right]) {
			restring = 0;
			break;
		}
		left = left + 1;
		right = right - 1;
	}
	
	if (restring) {
		printf("True");
	}
	else {
		printf("False");
	}
}
