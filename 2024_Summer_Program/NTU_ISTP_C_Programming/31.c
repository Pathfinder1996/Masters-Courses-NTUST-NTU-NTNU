#include <stdio.h>
#include <string.h>

int main(void) {
	char in[201];
	char out[201];
	
	scanf("%200s", &in);
	
	int len = strlen(in);
	
	int i, num;
	for (i = 0; i < len; i++) {
		num = in[i] - '0';
		
		if (in[i] % 2 == 0) {
			out[i] = num + 'A';
		}
		else {
			out[i] = num + 'a';
		}
	}
	out[len] = '\0';
	printf("%s\n", out);
}
