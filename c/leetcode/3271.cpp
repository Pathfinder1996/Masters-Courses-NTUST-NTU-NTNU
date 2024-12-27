#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string stringHash(string s, int k) {
        int n = s.length();
        string result = "";

        for (int i = 0; i < n; i = i + k) {
            string sub_string = s.substr(i, k);
            int sum = 0;

            for (char c : sub_string) {
                sum = sum + (c - 'a');
            }

            int hash_char = sum % 26;
            char result_char = 'a' + hash_char;
            result = result + result_char;
        }

        return result;
    }
};

int main() {
    Solution solution;
    // example 1
    string s = "abcd";
    int k = 2;
    cout << "Output: " << solution.stringHash(s, k) << endl;
    // example 2
    s = "mxz";
    k = 3;
    cout << "Output: " << solution.stringHash(s, k) << endl;

    return 0;
}
