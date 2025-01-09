#include <stdio.h>
#include <string.h>
#define MAXL 5001

void showString(char string[], char ch);

int main(void) {
	char S[MAXL], command[MAXL];
	char ch;
		
	while(1) {
		scanf("%s", command);
		
		if (strcmp(command, "q") == 0) {
			printf("end");
			break;
		}
		scanf(" %c", &ch);

		if (strcmp(command, "add") == 0) {
			int length = strlen(S);
//			printf("%d", length);
			
			if (length < MAXL - 1) {
				S[length] = ch;
				S[length + 1] = '\0';
			}			
		}
		else if (strcmp(command, "show") == 0) {
			showString(S, ch);
		}
	}
	
    return 0;
}

void showString(char string[], char ch) {
	int i, length = strlen(string);
	for (i = 0; i < length; i++) {
		if (i == 0) {
			printf("%c", string[i]);
		}
		else {
			printf("%c%c", ch, string[i]);
		}
	}
	printf("\n");
}
