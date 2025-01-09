#include <stdio.h>
#include <string.h>
#define MAXL 51

int main(void) {	
    char P[MAXL * 2], Q[MAXL];
    scanf("%s", &P);
    getchar();
    scanf("%s", &Q);
	
	strcat(P, Q);
	
	char B[MAXL];
	int i, j, qlen = strlen(Q);
	
	for (i = 0, j = qlen - 1; i < qlen; i++, j--) {
		B[i] = Q[j];
	}
	B[qlen] = '\0';
	
	int cmpRes = strcmp(P, B);
	if (cmpRes > 0) {
		printf("%s\n", P);
		printf("%d\n", strlen(P));
	}
	else {
		printf("%s\n", B);
		printf("%d\n", strlen(B));
	}
}
