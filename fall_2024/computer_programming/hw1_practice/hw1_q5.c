#include <stdio.h>

int GCD(int a, int b);

int main() {

    int N;
    while (scanf("%d", &N) && N != 0) {
        int G = 0;
        for (int i = 1; i < N; i++) {
            for (int j = i + 1; j <= N; j++) {
                G = G + GCD(i, j);
            }
        }
        
        printf("%d\n", G);
    }

    return 0;
}

int GCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}
