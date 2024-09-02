int chalkReplacer(int* chalk, int chalkSize, int k) {
    long long int chalk_sum = 0;

    for (int i = 0; i < chalkSize; i++) {
        chalk_sum = chalk_sum + chalk[i];
    }

    k = k % chalk_sum;

    for (int i = 0; i < chalkSize; i++) {
        if (k < chalk[i]) {
            return i;
        }
        k = k - chalk[i];
    }

    return chalkSize - 1;
}
