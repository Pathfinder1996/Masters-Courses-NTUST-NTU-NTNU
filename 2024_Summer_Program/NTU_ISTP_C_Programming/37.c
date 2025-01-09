#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXL 101

int isInteger(const char *str);

int main() {
    char string[MAXL];
    
    while (fgets(string, sizeof(string), stdin) != NULL) {
        string[strcspn(string, "\n")] = 0;
        
        char *end = string + strlen(string) - 1;
		while (end > string && isspace(*end)) {
			end = end - 1;
		}

        *(end + 1) = '\0';
        
        if (isInteger(string)) {
            printf("%d\n", atoi(string));
        } 
		else {
            printf("not an integer\n");
        }
    }
    return 0;
}

int isInteger(const char *string) {
    if (string[0] == '-' || string[0] == '+') {
		string = string + 1;
	}
    
    while (*string) {
        if (!isdigit(*string)) {
			return 0;
		}
        string = string + 1;
    }
    return 1;
}
