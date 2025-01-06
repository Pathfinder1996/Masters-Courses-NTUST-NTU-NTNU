#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 100

long long int digitTrans(long long int n, long long int p, long long int q);

int main(void) {
    long long int n, p, q;
    scanf("%lld", &n);
    scanf("%lld %lld", &p, &q);

    long long int result;
    result = digitTrans(n, p, q);

    printf("%lld\n", result);

    return 0;
}

long long int digitTrans(long long int n, long long int p, long long int q) {
    char string[MAXL];
    sprintf(string, "%lld", n);

    long long int length = q - p;
    char substring[MAXL];
    strncpy(substring, &string[p], length);
    substring[length] = '\0';

    long long int a = atoll(substring);
    int i;
    char temp;
    for (i = 0; i < (length / 2); i++) {
        temp = substring[i];
        substring[i] = substring[length - i - 1];
        substring[length - i - 1] = temp;
    }

    long long int b = atoll(substring);

    // printf("%lld %lld\n", a, b); 

    if (a < b) {
        return a + b;
    } 
    else {
        return a - b;
    }
}
