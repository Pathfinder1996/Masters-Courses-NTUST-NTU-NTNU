#include <stdio.h>
#include <string.h>
#define MAX_L 81

int main() {

    int n;
    scanf("%d", &n);
    
    char string[MAX_L];
    int i;
    for (i = 0; i < n; i++) {
        scanf("%s", string);
        int str_len = strlen(string);

        int j;
        int seq_o = 0;
        int sum = 0;
        for (j = 0; j < str_len; j++) {
            if (string[j] == 'O') {
                seq_o = seq_o + 1;
                sum = sum + seq_o;
            }
            else if (string[j] == 'X') {
                seq_o = 0;
            }
        }
        printf("%d\n", sum);
    }

    return 0;
}
