#include <stdio.h>

int main() {
    char ch = getchar();
    
    if (ch >= 'A' && ch < 'a') {
		ch = ch + ('a' - 'A');
		putchar(ch);
	}
    else {
		ch = ch - ('a' - 'A');
		putchar(ch);
	}
}
