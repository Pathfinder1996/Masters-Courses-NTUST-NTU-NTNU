#include <stdio.h>
#include <string.h>
#define MAX_L 151

int main(void) {
	char str[MAX_L];
	scanf("%[^\n]", str);
	
	char *p = strtok(str, " ");
	while (p != NULL) {
		char *next = strtok(NULL, " ");
		if (next != NULL) {
			printf("%s ", p);
		}
		else {
			printf("%s", p);
		}
		p = next;
	}
}
