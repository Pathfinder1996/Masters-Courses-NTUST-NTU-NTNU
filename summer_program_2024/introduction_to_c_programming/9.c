#include <stdio.h>
#include <string.h>
#define MAXL 151

int main(void) {
	char str[MAXL];
	gets(str);
//	printf("%s", str);
//	printf("%d", strlen(str));
	int length = strlen(str);
	
	int i, sum = 0;
	for (i = 0; i < length; i++) {
		if (str[i] >= 48 && str[i] < 58) {
			str[i] = str[i] - 48;
			sum = sum + str[i];
		}
		else if (str[i] >= 65 && str[i] < 97) {
			str[i] = str[i] - 65;
			sum = sum + str[i];
		}
		else if (str[i] >= 97 && str[i] < 123) {
			str[i] = str[i] - 97;
			sum = sum + str[i];
		}
		else {
			sum = sum + str[i];
		}
//		printf("索引%d: %d\n", i, str[i]);
//		printf("總和%d: %d\n", i, sum);
	}
	printf("%d", sum);
	
    return 0;
}
