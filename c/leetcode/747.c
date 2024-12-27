int dominantIndex(int* nums, int numsSize) {
    int max_num = -1;
    int sec_max_num = -1;
    int index = 0; 

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max_num) {
            sec_max_num = max_num;
            max_num = nums[i];
            index = i;
        }
        if (nums[i] > sec_max_num && nums[i] < max_num) {
            sec_max_num = nums[i];
        }
    }

    if (max_num >= sec_max_num * 2) {
        return index;
    }
    else {
        return -1;
    }
}
