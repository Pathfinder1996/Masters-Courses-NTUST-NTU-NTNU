#include <vector>
using namespace std;

class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        auto n = nums.size();
        auto sum = 0;
        for (auto i = 0; i < n; i++) {
            if (n % (i + 1) == 0) {
                sum = sum + (nums[i] * nums[i]);
            }
        }

        return sum;
    }
};
