#include <vector>
using namespace std;

class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        long long int chalk_sum = 0;

        for (auto i : chalk) {
            chalk_sum = chalk_sum + i;
        }

        k = k % chalk_sum;

        for (auto i = 0; i < chalk.size(); i++) {
            if (k < chalk[i]) {
                return i;
            }
            k = k - chalk[i];
        }

        return chalk.size() - 1;
    }
};
