#include <stdio.h>

int main() {
    int W, H;
    scanf("%d %d", &W, &H);
    getchar();
    getchar();

    char c;
    while (scanf("%c", &c) != EOF) {
        if (c == '\r') {
            getchar();
            printf("\n");
        } 
        else {
            printf("%d", (int)c);
        }
    }
    
    return 0;
}

// OS Linux 版本
// #include <stdio.h>

// int main() {
//     int W, H;
//     scanf("%d %d", &W, &H);
//     getchar();

//     char c;
//     while (scanf("%c", &c) != EOF) {
//         if (c == '\n') {
//             printf("\n");
//         } 
//         else {
//             printf("%d", (int)c);
//         }
//     }
    
//     return 0;
// }