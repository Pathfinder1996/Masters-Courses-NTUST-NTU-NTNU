#include <iostream>
using namespace std;

class Grade {
  public:
    Grade();
    Grade(int v);
    int value;

    bool operator>=(int v) const {
      return value >= v;
    }

    bool operator<(int v) const {
      return value < v;
    }
};

ostream& operator<<(ostream&, const Grade&);

int main() {
  const Grade gs[5] = { 80, 60, 59, 90, 40};
  
  cout << "PASS: ";
  for (const auto& g : gs) {
      if (g >= 60) {
         cout << " " << g;
      }
  }
  cout << endl;
  
  cout << "FAIL: ";
  for (const auto& g : gs) {
      if (g < 60) {
         cout << " " << g;
      }
  }
  cout << endl;
}

ostream& operator<<(ostream& os, const Grade& g) {
  os << g.value;
  return os;
}

Grade::Grade() {
  value = 0;
}

Grade::Grade(int v) {
  if (v < 0) {
    v = 0;
  } else if (v > 100) {
    v = 100;
  }
  value = v;
}
