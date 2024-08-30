#include <stdio.h>
#include <string.h>

int main(void) {
	char array[1000];
	scanf("%[^\n]", array);
	
	char *p = strtok(array, " ");
	while (p != NULL) {
		char *next = strtok(NULL, " ");
		if (next != NULL) {
			printf("%s\n", p);
		}
		else {
			printf("%s", p);
		}
		p = next;
	}
}
