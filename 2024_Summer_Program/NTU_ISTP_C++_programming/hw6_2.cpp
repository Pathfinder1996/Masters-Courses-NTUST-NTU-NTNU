#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<int> Intersection(const vector<int>& a, const vector<int>& b) {
    vector<int> a_sorted = a;
    vector<int> b_sorted = b;
    
    sort(a_sorted.begin(), a_sorted.end());
    sort(b_sorted.begin(), b_sorted.end());
    
    vector<int> result;
    
    set_intersection(a_sorted.begin(), a_sorted.end(), b_sorted.begin(), b_sorted.end(), back_inserter(result));
    
    return result;
}

int main() {
    vector<int> a = {3, 9, 1, 7, 2, 6};
    vector<int> b = {1, 3, 5, 7};
    vector<int> c = {2, 4, 6, 8, 0, 3, 9};
    
    for (auto v : Intersection(a, b)) {
        cout << v << " ";
    }
    cout << endl;
    
    for (auto v : Intersection(a, c)) {
        cout << v << " ";
    }
    cout << endl;
    
}
