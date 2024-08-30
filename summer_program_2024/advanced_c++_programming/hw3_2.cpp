#include <iostream>
using namespace std;

void MySort(int& num1, int& num2);

int main() {
  int a = 3, b = 5;
  int c = 9, d = 2;
  MySort(a, b);
  MySort(c, d);
  cout << "a : " << a << endl
       << "b : " << b << endl
       << "c : " << c << endl
       << "d : " << d << endl;
  return 0;
}

void MySort(int& num1, int& num2) {
    if (num1 > num2) {
        auto temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
