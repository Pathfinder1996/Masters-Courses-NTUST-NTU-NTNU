#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int big, small;
    if (a > b) {
        big = a;
        small = b;
    }
    else {
        big = b;
        small = a;
    }

    while (small != 0) {
        int temp = big;
        big = small;
        small = temp % small;
    }

    printf("%d", big);

    return 0;
}
