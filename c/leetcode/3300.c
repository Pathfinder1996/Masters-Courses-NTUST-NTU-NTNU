int minElement(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        int sum = 0;
        while (nums[i] > 0) {
            sum = sum + (nums[i] % 10);
            nums[i] = nums[i] / 10;
        }
        nums[i] = sum;
    }

    int mini_num = 10001;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < mini_num) {
            mini_num = nums[i];
        }
    }

    return mini_num;
}
