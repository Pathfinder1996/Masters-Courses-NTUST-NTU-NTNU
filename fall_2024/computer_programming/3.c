#include <stdio.h>
#define DP_SIZE 30001

int main() {
    int coins[5] = {1, 5, 10, 25, 50};
    unsigned long long int dp[DP_SIZE] = {0};
    dp[0] = 1;

    for (int i = 0; i < 5; i++) {
        for (int j = coins[i]; j < DP_SIZE; j++) {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    int n;
    while (scanf("%d", &n) != EOF) {
        if (dp[n] == 1) {
            printf("There is only 1 way to produce %d cents change.\n", n);
        }
        else {
            printf("There are %llu ways to produce %d cents change.\n", dp[n], n);
        }
    }

    return 0;
}