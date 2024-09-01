#include <vector>
using namespace std;

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int m = mat.size();

        int sum = 0;
        for (int i = 0; i < m; i++) {
            sum = sum + mat[i][i];

            if (i != m - 1 - i) {
                sum = sum + mat[i][m - 1 - i];
            }
        }

        return sum;
    }
};
