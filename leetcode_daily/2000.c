#include <string.h>

char* reversePrefix(char* word, char ch) {
    int n = strlen(word);
    int index = 0;
    for (int i = 0; i < n; i++) {
        index = index + 1;
        if (word[i] == ch) {
            break;
        }
        else if (index == n) {
            return word;
        }
    }

    int left = 0;
    int right = index - 1;
    while (left <= right) {
        char temp = word[left];
        word[left] = word[right];
        word[right] = temp;
        left = left + 1;
        right = right - 1; 
    }

    return word;
}
