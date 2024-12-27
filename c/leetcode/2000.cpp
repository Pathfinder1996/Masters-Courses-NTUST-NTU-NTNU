#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string reversePrefix(string word, char ch) {
        int index = 0;
        for (auto i : word) {
            index = index + 1;
            if (i == ch) {
                break;
            }
            else if (word.length() == index) {
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
};

int main() {
    Solution s;
    // emample 1
    cout << s.reversePrefix("abcdefd", 'd') << endl;
    // emample 2
    cout << s.reversePrefix("xyxzxe", 'z') << endl;
    // emample 3
    cout << s.reversePrefix("abcd", 'z') << endl;

    return 0;
}