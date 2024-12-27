#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int generateKey(int num1, int num2, int num3) {
        string str1 = padZero(num1);
        string str2 = padZero(num2);
        string str3 = padZero(num3);

        string key = "";
        for (int i = 0; i < 4; i++) {
            char min_num = min({str1[i], str2[i], str3[i]});
            key = key + min_num;
        }

        int key_to_int = stoi(key);

        return key_to_int;
    }

private:
    string padZero(int number) {
        string str = to_string(number);
        while (str.length() < 4) {
            str = "0" + str;
        }
        return str;
    }
};

int main() {
    Solution solution;
    // example 1
    int num1 = 1, num2 = 10, num3 = 1000;
    cout << "Output: " << solution.generateKey(num1, num2, num3) << endl;
    // example 2
    num1 = 987, num2 = 879, num3 = 798;
    cout << "Output: " << solution.generateKey(num1, num2, num3) << endl;
    // example 3
    num1 = 1, num2 = 2, num3 = 3;
    cout << "Output: " << solution.generateKey(num1, num2, num3) << endl;

    return 0;
}
