#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_POINTS 10

// 多項式表格
typedef struct {
    double coeff[MAX_POINTS];
    int degree;
} Polynomial;

void init_polynomial(Polynomial *p);
void add_polynomial(Polynomial *result, Polynomial *p1, Polynomial *p2);
void multiply_polynomial(Polynomial *result, Polynomial *p1, Polynomial *p2);
void calculate_li(Polynomial *li, int i, double points[][2], int n);
void print_process(Polynomial *p, const char *name, int max_degree);
void print_final_polynomial(Polynomial *p, const char *name, int max_degree);

int main() {
    int n;
    scanf("%d", &n);

    double points[MAX_POINTS][2]; // 存點 改為 double 型別
    Polynomial li[MAX_POINTS];   // 存 L_i(x)
    Polynomial p;                // result
    init_polynomial(&p);         // initialize

    // 輸入點
    for (int i = 0; i <= n; i++) {
        scanf("%lf %lf", &points[i][0], &points[i][1]);
        // printf("%.2f, %.2f\n", points[i][0], points[i][1]);
    }

    // L_i(x)
    for (int i = 0; i <= n; i++) {
        calculate_li(&li[i], i, points, n);

        // 當前 L_i(x)
        // printf("L_%d(x): ", i);
        // print_process(&li[i], "", li[i].degree);
        // printf("\n");

        // yi * L_i(x)
        Polynomial term;
        init_polynomial(&term);
        for (int j = 0; j <= li[i].degree; j++) {
            term.coeff[j] = li[i].coeff[j] * points[i][1];
        }
        term.degree = li[i].degree;

        // 當前 yi * L_i(x)
        // printf("y_%d * L_%d(x): ", i, i);
        // print_process(&term, "", term.degree);
        // printf("\n");

        // (yi * L_i(x)) 累加到 P(x)
        add_polynomial(&p, &p, &term);

        // 當前 P(x)
        // printf("P(x) 累加到目前為止: ");
        // print_process(&p, "", p.degree);
        // printf("\n");
    }

    print_final_polynomial(&p, "f(x)", p.degree);

    return 0;
}

//======================================//
//            多項式操作區               //
//======================================//
void init_polynomial(Polynomial *p) {
    for (int i = 0; i < MAX_POINTS; i++) {
        p->coeff[i] = 0.0;
    }
    p->degree = 0;
}

void add_polynomial(Polynomial *result, Polynomial *p1, Polynomial *p2) {
    Polynomial temp;
    init_polynomial(&temp);
    temp.degree = (p1->degree > p2->degree) ? p1->degree : p2->degree;

    for (int i = 0; i <= temp.degree; i++) {
        double c1 = (i <= p1->degree) ? p1->coeff[i] : 0.0;
        double c2 = (i <= p2->degree) ? p2->coeff[i] : 0.0;
        temp.coeff[i] = c1 + c2;
    }

    *result = temp;
}

void multiply_polynomial(Polynomial *result, Polynomial *p1, Polynomial *p2) {
    Polynomial temp;
    init_polynomial(&temp);

    for (int i = 0; i <= p1->degree; i++) {
        for (int j = 0; j <= p2->degree; j++) {
            temp.coeff[i + j] += p1->coeff[i] * p2->coeff[j];
        }
    }

    temp.degree = p1->degree + p2->degree;
    *result = temp;
}

//======================================//
//               L_i(x)                 //
//======================================//
void calculate_li(Polynomial *li, int i, double points[][2], int n) {
    init_polynomial(li);

    li->coeff[0] = 1.0;
    li->degree = 0;

    for (int j = 0; j <= n; j++) {
        if (j != i) {
            Polynomial term;
            init_polynomial(&term);

            // (x - x_j)
            term.coeff[0] = -points[j][0];
            term.coeff[1] = 1.0;
            term.degree = 1;

            // printf(" (x - %.2f)", points[j][0]);

            // 除以 (x_i - x_j)
            double denominator = points[i][0] - points[j][0];
            for (int k = 0; k <= term.degree; k++) {
                term.coeff[k] /= denominator;
            }

            // printf(" / (%.2f - %.2f)", points[i][0], points[j][0]);

            // * 到 L_i(x)
            multiply_polynomial(li, li, &term);
        }
    }

    // print_process(li, "", li->degree);
}

//======================================//
//                check                 //
//======================================//
// void print_process(Polynomial *p, const char *name, int max_degree) {
//     char result[1024] = ""; // 多項式 string
//     char term[128];         // 單項式 string
//     int first = 1;          // 第一項

//     for (int i = max_degree; i >= 0; i--) {
//         double coeff = p->coeff[i];
//         if (fabs(coeff) > 1e-9) {
//             if (!first && coeff > 0) {
//                 strcat(result, " + ");
//             }
//             if (coeff < 0) {
//                 if (first) {
//                     strcat(result, "-");
//                 } else {
//                     strcat(result, " - ");
//                 }
//             }

//             sprintf(term, "%.2f", fabs(coeff));
//             strcat(result, term);

//             if (i > 0) {
//                 strcat(result, "x");
//                 if (i > 1) {
//                     sprintf(term, "^%d", i);
//                     strcat(result, term);
//                 }
//             }
//             first = 0;
//         }
//     }

//     if (first) {
//         strcat(result, "0");
//     }

//     printf("%s%s\n", name, result);
// }

//======================================//
//               result                 //
//======================================//
void print_final_polynomial(Polynomial *p, const char *name, int max_degree) {
    char result[1024] = ""; // 多項式 string
    char term[128];         // 單項式 string
    int first = 1;          // 第一項

    for (int i = max_degree; i >= 0; i--) {
        double coeff = round(p->coeff[i]);
        if (fabs(coeff) > 1e-9) {
            if (!first && coeff > 0) {
                strcat(result, " + ");
            }
            if (coeff < 0) {
                if (first) {
                    strcat(result, "-");
                } else {
                    strcat(result, " - ");
                }
            }

            // x 的係數為 1 or -1 時省略數字
            if (!(fabs(coeff) == 1.0 && i > 0)) {
                sprintf(term, "%.0f", fabs(coeff));
                strcat(result, term);
            }

            // 顯示變數與次方
            if (i > 0) {
                strcat(result, "x");
                if (i > 1) {
                    sprintf(term, "^%d", i);
                    strcat(result, term);
                }
            }
            first = 0;
        }
    }

    if (first) {
        strcat(result, "0");
    }

    printf("%s = %s\n", name, result);
}
