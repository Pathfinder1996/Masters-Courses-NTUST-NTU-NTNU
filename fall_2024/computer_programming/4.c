#include <stdio.h>

void compareNumbers(int a, int b);

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        compareNumbers(a, b);
    }

    return 0; 
}

void compareNumbers(int a, int b) {
    if (a > b) {
        printf(">\n");
    }
    else if (a < b) {
        printf("<\n");
    }
    else {
        printf("=\n");
    }
}
