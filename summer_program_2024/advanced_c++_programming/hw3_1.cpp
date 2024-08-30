#include <iostream>
using namespace std;

void SplitInteger(int);

int main() {
  SplitInteger(1234);
  SplitInteger(567890);
  return 0;
}

void SplitInteger(int num) {
    while (num != 0) {
        auto temp = num % 10;
        cout << temp << " ";
        num = num / 10;
    }
    cout << endl;
}
