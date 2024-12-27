#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);

        if ((b - a) == (d - c)) {
            printf("%d %d %d %d %d\n", a, b, c, d, d + d - c);
        }
        else {
            printf("%d %d %d %d %d\n", a, b, c, d, d * (d / c));
        }
    }
    return 0;
}
