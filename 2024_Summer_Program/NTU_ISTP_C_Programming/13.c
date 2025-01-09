#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_LENGTH 3000
#define MAX_LENGTH 21
#define MAX_STRING 300

void filterAndMerge(char* input, char** output, int* count, char delimiter, char start);
int compare(const void* a, const void* b);

int main() {
    char input1[TOTAL_LENGTH], input2[TOTAL_LENGTH], input3[TOTAL_LENGTH];
    char* output[MAX_STRING];
    int count = 0;

    fgets(input1, sizeof(input1), stdin);
    fgets(input2, sizeof(input2), stdin);
    fgets(input3, sizeof(input3), stdin);

    input1[strcspn(input1, "\n")] = 0;
    input2[strcspn(input2, "\n")] = 0;
    input3[strcspn(input3, "\n")] = 0;

    filterAndMerge(input1, output, &count, ' ', 'a');
    filterAndMerge(input2, output, &count, ',', 'b');
    filterAndMerge(input3, output, &count, ';', 'c');

    qsort(output, count, sizeof(char*), compare);

    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%s", output[i]);
        free(output[i]);
    }
    printf("\n");

    return 0;
}

void filterAndMerge(char* input, char** output, int* count, char delimiter, char start) {
    char* token = strtok(input, &delimiter);
    while (token != NULL) {
        if (token[0] != start) {
            output[*count] = malloc(strlen(token) + 1);
            strcpy(output[*count], token);
            (*count) = (*count) + 1;
        }
        token = strtok(NULL, &delimiter);
    }
}

int compare(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}
