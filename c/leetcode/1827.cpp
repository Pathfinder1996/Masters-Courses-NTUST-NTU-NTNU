#include <vector>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        auto n = nums.size();
        auto sum = 0;
        for (auto i = 1; i < n; i++) {
            if (nums[i] <= nums[i - 1]) {
                sum = sum + (nums[i - 1] + 1 - nums[i]);
                nums[i] = nums[i - 1] + 1;
            }
        }

        return sum;
    }
};
