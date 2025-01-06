#include <stdio.h>

int main() {
    int W, H, O;

    scanf("%d %d %d", &W, &H, &O);
    getchar();
    getchar();

    char c;
    while (scanf("%c", &c) != EOF) {
        if (c == '\r') {
            getchar();
            printf("\n");
        } 
        else {
            int new_char = (int)c + O;
            if (new_char > 127) {
                new_char = new_char % 127;
            }

            printf("%c", (char)new_char);
        }
    }

    return 0;
}


// OS Linux 版本
// #include <stdio.h>

// int main() {
//     int W, H, O;

//     scanf("%d %d %d", &W, &H, &O);
//     getchar();

//     char c;
//     while (scanf("%c", &c) != EOF) {
//         if (c == '\n') {
//             printf("\n");
//         } 
//         else {
//             int new_char = (int)c + O;
// 			   if (new_char > 127) {
//             	   new_char = new_char % 127;
//             }
//             if (new_char < 32) {
//                 new_char = new_char + 32;
//             }
          
//           	printf("%c", (char)new_char);
//         }
//     }

//     return 0;
// }