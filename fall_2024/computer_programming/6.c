#include <stdio.h>

int main() {
    int a, b;
    while(scanf("%d %d", &a, &b) != EOF) {
        if (a == -1 && b == -1) {
            break;
        }

        int clockwise = (b - a + 100) % 100;
        int counter_clockwise = (a - b + 100) % 100;

        int result;
        if (clockwise < counter_clockwise) {
            result = clockwise;
        } 
        else {
            result = counter_clockwise;
        }

        printf("%d\n", result);
    }

    return 0;
}
