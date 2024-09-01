#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        vector<int> result;
        priority_queue<int> maxHeap;

        for (auto& i : queries) {
            int x = i[0];
            int y = i[1];
            int distance = abs(x) + abs(y);

            if (maxHeap.size() < k) {
                maxHeap.push(distance);
            }
            else if (distance < maxHeap.top()) {
                maxHeap.pop();
                maxHeap.push(distance);
            }

            if (maxHeap.size() < k) {
                result.push_back(-1);
            }
            else {
                result.push_back(maxHeap.top());
            }
        }

        return result;
    }
};

int main() {
    Solution solution;
    // example 1
    vector<vector<int>> queries = {{1, 2}, {3, 4}, {2, 3}, {-3, 0}};
    int k = 2;

    vector<int> result = solution.resultsArray(queries, k);

    for (int r : result) {
        cout << r << " ";
    }
    cout << endl;
    // example 2
    vector<vector<int>> queries2 = {{5,5},{4,4},{3,3}};
    int k2 = 1;

    vector<int> result2 = solution.resultsArray(queries2, k2);

    for (int r : result2) {
        cout << r << " ";
    }
    cout << endl;

    return 0;
}
