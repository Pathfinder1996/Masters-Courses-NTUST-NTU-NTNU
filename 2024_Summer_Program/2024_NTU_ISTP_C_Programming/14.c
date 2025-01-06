#include <stdio.h>
#include <string.h>
#define N 1000
#define STR_L 8

int main(void) {
	char idList[N][STR_L + 1];
	char id[STR_L + 1];
	
	int count = 0;
	while (1) {
		scanf("%s", id);
		if (id[0] == 'q' && id[1] == '\0') {
			break;
		}
		strcpy(idList[count], id);
		count = count + 1;
	}
	
	int index;
	while (1) {
		int feedback = scanf("%d", &index);
		if (feedback == 0) {
			break;
		}
		char *p = idList[index];
		printf("%s\n", p);
	}
}
