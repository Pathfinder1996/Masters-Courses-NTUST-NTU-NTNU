#include <stdio.h>

void hanoi(int n, int p1, int p2, int p3);

int main() {
    int n;
    scanf("%d", &n);

    hanoi(n, 1, 3, 2);

    return 0;
}

void hanoi(int n, int p1, int p2, int p3) {
    if (n == 1) {
        printf("Move disk 1 from peg %d to peg %d\n", p1, p2);
        return;
    }
    hanoi(n - 1, p1, p3, p2);
    printf("Move disk %d from peg %d to peg %d\n", n, p1, p2);
    hanoi(n - 1, p3, p2, p1);
}
