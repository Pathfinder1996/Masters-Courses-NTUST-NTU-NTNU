#include <stdio.h>
#include <string.h>
#define MAXL 201

void reverseString(char *string);

int main(void) {   
    FILE *fin = fopen("58.in", "r");
    FILE *fout = fopen("58.out", "w");

    char string[MAXL];
    int length;
    while (fgets(string, sizeof(string), fin)) {
        string[strcspn(string, "\r\n")] = '\0';
        // printf("%s\n", string);
        length = strlen(string);
        
        if (length > 0 && string[length - 1] == '\n') {
            string[length - 1] = '\0';
        }

        if (strlen(string) > 0 && string[0] != '\n') {
            reverseString(string);
            fprintf(fout, "%s\n", string);
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

void reverseString(char *string) {
    int left = 0;
    int right = strlen(string) - 1;

    char temp;
    while (left < right) {
        temp = string[left];
        string[left] = string[right];
        string[right] = temp;
        left = left + 1;
        right =right - 1;
    }
}
