#include <iostream>
using namespace std;

class IntArray {
public:
    IntArray();
    int operator[](int i) const;
    int& operator[](int i);
    int Size() const;
private:
    int data[5];
};

ostream& operator<<(ostream&, const IntArray&);

int main() {
    IntArray a;
    a[2] = 7;
    a[3] = 5;
    a[4] = 9;
    const IntArray b = a;
    cout << "a[7]: " << a[7] << endl    // a[7]  == a[2]
         << "a[18]: " << a[18] << endl  // a[18] == a[3]
         << "a[25]: " << a[25] << endl  // a[25] == a[0]
         << "b[29]: " << b[29] << endl; // b[29] == b[4]
    return 0;
}

ostream& operator<<(ostream& os, const IntArray& a) {
    os << "[" << a[0];
    for (int i = 1; i < a.Size(); i++) {
        os << ", " << a[i];
    }
    os << "]";
    return os;
}

IntArray::IntArray() {
    for (auto& v : data) {
        v = 0;
    }
}

int IntArray::operator[](int i) const {
    int index = i % 5;
    return data[index];
}

int& IntArray::operator[](int i)  {
    int index = i % 5;
    return data[index];
}

int IntArray::Size() const {
    return 5;
}
