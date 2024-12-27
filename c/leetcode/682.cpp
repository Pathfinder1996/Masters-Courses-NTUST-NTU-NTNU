#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int calPoints(vector<string>& operations) {
    stack<int> stack;
    for (const auto& i : operations) {
        if (i == "+") {
            int num1 = stack.top();
            stack.pop();
            int num2 = stack.top();
            stack.push(num1);
            stack.push(num1 + num2);
        } else if (i == "D") {
            stack.push(2 * stack.top());
        } else if (i == "C") {
            stack.pop();
        } else {
            stack.push(stoi(i));
        }
    }
    
    int stack_sum = 0;
    while (!stack.empty()) {
        stack_sum = stack_sum + stack.top();
        stack.pop();
    }
    
    return stack_sum;
}

int main() {
    // example 1
    vector<string> ops = {"5", "2", "C", "D", "+"};
    cout << calPoints(ops) << endl;
    // example 2
    vector<string> ops2 = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    cout << calPoints(ops2) << endl;
    // example 3
    vector<string> ops3 = {"1","C"};
    cout << calPoints(ops3) << endl;
    
    return 0;
}