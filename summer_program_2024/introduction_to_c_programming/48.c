#include <stdio.h>
#include <string.h>
#define MAXL 100

int main(void) {
    int n;
    scanf("%d", &n);
    getchar();

    char str[MAXL + 1];
    int i, j;
    for (i = 0; i < n; i++) {
    	gets(str);
        for (j = 0; j <= i; j++) {
            putchar('*');
        }
        
        printf("%s", str);
        
        for (j = 0; j <= i; j++) {
            putchar('*'); 
        }
        putchar('\n');
    }
    return 0; 
}
