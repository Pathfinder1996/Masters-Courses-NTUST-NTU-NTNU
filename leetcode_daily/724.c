int pivotIndex(int* nums, int numsSize) {
    int* array_left = malloc(sizeof(int) * numsSize);
    int left_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        left_sum = left_sum + nums[i];
        array_left[i] = left_sum;
    }

    int* array_right = malloc(sizeof(int) * numsSize);
    int right_sum = 0;
    for (int i = numsSize - 1; i > -1; i--) {
        right_sum = right_sum + nums[i];
        array_right[i] = right_sum;
    }

    for (int i = 0; i < numsSize; i++) {
        if (array_left[i] == array_right[i]) {
            free(array_left);
            free(array_right);
            return i;
        }
    }

    free(array_left);
    free(array_right);
    
    return -1;
}
