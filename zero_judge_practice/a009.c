#include <stdio.h>

int main() {
    char c;
    while(c = getchar()) {
        if (c == EOF) {
            break;
        }
        c = (int)c - 7;
        printf("%c", c);
    }

    return 0;
}
