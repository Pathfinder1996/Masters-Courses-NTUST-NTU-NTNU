#include <stdio.h>

#define MAX_L 100

void printMatrix(int A[MAX_L][MAX_L], int m, int n);
void creatMatrix(int A[MAX_L][MAX_L]);
void matrixMultiply(int A[MAX_L][MAX_L], int B[MAX_L][MAX_L], int C[MAX_L][MAX_L], int m, int n, int t);

int main(void) {
    int A[MAX_L][MAX_L];
    int B[MAX_L][MAX_L];
    int C[MAX_L][MAX_L];
    int m, n, t;

    printf("矩陣 A：\n");
    creatMatrix(A);
    getchar();
    printf("矩陣 B：\n");
    creatMatrix(B);
    getchar();

    scanf("%d %d %d", &m, &n, &t);
    matrixMultiply(A, B, C, m, n, t);
    printf("矩陣 A x 矩陣 B：\n");
    printMatrix(C, m, n);
}

void printMatrix(int A[MAX_L][MAX_L], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

void creatMatrix(int A[MAX_L][MAX_L]) {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printMatrix(A, m, n);
}

void matrixMultiply(int A[MAX_L][MAX_L], int B[MAX_L][MAX_L], int C[MAX_L][MAX_L], int m, int n, int t) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < t; k++) {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
            }
        }
    }
}