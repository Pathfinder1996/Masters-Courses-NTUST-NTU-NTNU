#include <stdio.h>

int main(void) {
    double num, sum = 0.0, average;
    int count;

    while (scanf("%lf", &num) != EOF) {
		sum = sum + num;
		count = count + 1;
    }
    
    average = (sum / count);
    printf("%.3lf\n", sum);
    printf("%.3lf\n", average);

    return 0;
}
