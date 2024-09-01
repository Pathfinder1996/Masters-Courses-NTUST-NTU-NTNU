#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        return (getCharValue(coordinate1) == getCharValue(coordinate2));
    }

private:
    int getCharValue(string coordinate) {
        int row = coordinate[1] - '0';
        int column = coordinate[0] - 'a' + 1;
        return (row + column) % 2;
    }
};

int main() {
    Solution solution;
    // example 1
    cout << solution.checkTwoChessboards("a1", "c3") << endl;
    // example 2
    cout << solution.checkTwoChessboards("a1", "h3") << endl;
    return 0;
}
