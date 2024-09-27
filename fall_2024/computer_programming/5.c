#include <stdio.h>
#define MAX_SIZE 3

int main() {
    int T;
    scanf("%d", &T);

    int salaries[MAX_SIZE];
    for (int i = 0; i < T; i++) {
        scanf("%d %d %d", &salaries[0], &salaries[1], &salaries[2]);
        // printf("%d %d %d\n", salaries[0], salaries[1], salaries[2]);

        int max_salary = salaries[0];
        int min_salary = salaries[0];
        for (int j = 1; j < MAX_SIZE; j++) {
            if (salaries[j] > max_salary) {
                max_salary = salaries[j];
            }
            if (salaries[j] < min_salary) {
                min_salary = salaries[j];
            }
        }
        // printf("%d %d\n", max_salary, min_salary);

        int survives = salaries[0] + salaries[1] + salaries[2] - max_salary - min_salary;
        printf("Case %d: %d\n", i + 1, survives);
    }

    return 0;
}
