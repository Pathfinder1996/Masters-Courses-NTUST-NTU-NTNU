#include <stdio.h>

void multiplicationGame(unsigned long long int n);

int main() {
    unsigned long long int n;

    while (scanf("%llu", &n) != EOF) {
        multiplicationGame(n);
    }

    return 0;
}

void multiplicationGame(unsigned long long int n) {
    unsigned long long int p = 1;
    int round = 1;

    while (p < n) {
        if (round) {
            p = p * 9;
        }
        else {
            p = p * 2;
        }
        round = 1 - round;
    }

    if (round == 0) {
        printf("Stan wins.\n");
    }
    else {
        printf("Ollie wins.\n");
    }
}
