#include <iostream>
using namespace std;

void Print(const char*);
void Print(char);
void Print(int);
void Print(double);

int main() {
    Print("Hello");
    Print('\n');
    Print(4);
    Print('\n');
    Print(8.7);
    return 0;
}

void Print(const char* str) {
    cout << str;
}

void Print(char ch) {
    cout << ch;
}

void Print(int num) {
    cout << num;
}

void Print(double num) {
    cout << num;
}
