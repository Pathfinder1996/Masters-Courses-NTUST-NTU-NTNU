#include <stdio.h>
#include <string.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    char article[10000] = "";
    char sentence[201];
    char query[31];

    for (int i = 0; i < N; i++) {
        scanf(" %[^\r\n]", sentence);
        strcat(article, sentence);
        // printf("%s\n", article);
    }

    for (int i = 0; i < M; i++) {
        scanf("%s", query);
        char* p = strstr(article, query);
        if (p) {
            printf("%d\n", p - article);
        }
        else {
            printf("Not found\n");
        }
    }

    return 0;
}
