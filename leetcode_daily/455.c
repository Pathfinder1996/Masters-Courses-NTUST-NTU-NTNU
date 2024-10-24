int compare(const void* a, const void* b);

int findContentChildren(int* g, int gSize, int* s, int sSize) {
    qsort(g, gSize, sizeof(int), compare);
    qsort(s, sSize, sizeof(int), compare);

    int p1, p2, count = 0;
    while (1) {
        if (p1 == gSize || p2 == sSize) {
            break;
        }

        if (s[p2] >= g[p1]) {
            p1 = p1 + 1;
            p2 = p2 + 1;
            count = count + 1;
        }

        else if (s[p2] < g[p1] && p2 < sSize) {
            p2 = p2 + 1;
        }
    }

    return count;
}

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
