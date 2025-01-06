#include <stdio.h>

void fuckingTower(int n, int peg1, int peg2, int peg3);

int main() {
    int n;
    scanf("%d", &n);

    fuckingTower(n, 1, 2, 3);

    return 0;
}

void fuckingTower(int n, int peg1, int peg2, int peg3) {
    if (n == 1) {
        printf("Move disk %d from peg %d to peg %d\n", 1, peg1, peg3);
    }
    else {
        fuckingTower(n - 1, peg1, peg3, peg2);
        printf("Move disk %d from peg %d to peg %d\n", n, peg1, peg3);
        fuckingTower(n - 1, peg2, peg1, peg3);
    }
}
