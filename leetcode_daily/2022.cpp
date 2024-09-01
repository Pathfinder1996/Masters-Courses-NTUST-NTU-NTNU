#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (original.size() != (m * n)) {
            return {}; 
        }

        vector<vector<int>> result(m, vector<int>(n));

        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = original[count];
                count = count + 1;
            }
        }

        return result;
    }
};

int main() {
    Solution solution;
    // example 1
    vector<int> original = {1, 2, 3, 4};
    int m = 2;
    int n = 2;

    vector<vector<int>> result = solution.construct2DArray(original, m, n);

    for (auto& i : result) {
        cout << '[' << " ";
        for (int j : i) {
            cout << j << " ";
        }
        cout << ']' << endl;
    }
    cout << endl;
    // example 2
    vector<int> original2 = {1, 2, 3};
    int m2 = 1;
    int n2 = 3;

    vector<vector<int>> result2 = solution.construct2DArray(original2, m2, n2);

    for (auto& i : result2) {
        cout << '[' << " ";
        for (int j : i) {
            cout << j << " ";
        }
        cout << ']' << endl;
    }
    cout << endl;

    return 0;
}
