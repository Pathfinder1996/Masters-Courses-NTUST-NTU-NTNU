#include <stdio.h>
#include <string.h>
#define MAX_L 151

int main(void) {
	char str[MAX_L];
	scanf("%[^\n]", str);
	
	char *p = strtok(str, ",");
	char *store[MAX_L];
	int count = 0;
	while (p != NULL) {
		store[count++] = p;
		p = strtok(NULL, ",");
	}
	
	int i;
	for (i = count - 1; i >= 0; i--) {
		if (i != 0) {
			printf("%s\n", store[i]);
		}
		else {
			printf("%s", store[i]);
		}
	}
}
