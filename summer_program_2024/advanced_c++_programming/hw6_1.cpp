#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void ReverseString(string& s);

int main() {
    string words[3] = {"Hello", "c++", "world!"};
    for (string& word : words) {
        cout << "Before: " << word << endl;
        ReverseString(word);
        cout << "After : " << word << endl;
    }
}

void ReverseString(string& s) {
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = temp;
    }
}