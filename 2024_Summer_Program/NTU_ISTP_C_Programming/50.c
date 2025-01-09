#include <stdio.h>
#include <string.h>
#define MAX_L 151

int main(void) {
	char str[MAX_L];
	gets(str);
	
	char *p = strtok(str, ",");
    while (p != NULL) {
        printf("%s\n", p);
        p = strtok(NULL, ",");
    }
}
