int minOperations(int* nums, int numsSize){
    int sum = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] <= nums[i - 1]) {
            sum = sum + (nums[i - 1] + 1 - nums[i]);
            nums[i] = nums[i - 1] + 1;
        }
    }

    return sum;
}
