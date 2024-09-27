#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        int a, b;
        int sum = 0;
        scanf("%d", &a);
        scanf("%d", &b);
        for (int j = a; j <= b; j++) {
            if (j % 2 != 0) {
                sum = sum + j;
            }
        }
        printf("Case %d: %d\n", i + 1, sum);
    }
	
	return 0;
}