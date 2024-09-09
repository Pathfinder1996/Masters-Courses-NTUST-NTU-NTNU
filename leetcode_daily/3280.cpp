#include <iostream>
#include <string>
#include <bitset>
using namespace std;

class Solution {
public:
    string convertDateToBinary(string date) {
        int year = stoi(date.substr(0, 4)); 
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        string year_to_binary = decimalToBinary(year);
        string month_to_binary = decimalToBinary(month);
        string day_to_binary = decimalToBinary(day);

        return year_to_binary + "-" + month_to_binary + "-" + day_to_binary;
    }

private:
    string decimalToBinary(int num) {
        string binary = bitset<32>(num).to_string();
        binary = binary.substr(binary.find('1'));

        return binary;
    }
};

int main() {
    Solution s;
    // example 1
    string date1 = "2080-02-29";
    cout << s.convertDateToBinary(date1) << endl;

    // example 2
    string date2 = "1900-01-01";
    cout << s.convertDateToBinary(date2) << endl;

}
