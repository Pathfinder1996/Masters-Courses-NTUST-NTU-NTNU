#include <iostream>
using namespace std;

class IntArray {
public:
    IntArray();
    int operator[](int i) const;
    int& operator[](int i);
    int Size() const;

    void Fill(int i) {
        for (auto& d : data) {
            d = i;
        }
    }

private:
    int data[5];
};

ostream& operator<<(ostream&, const IntArray&);

int main() {
    IntArray a;
    cout << "a : " << a << endl;
    a.Fill(5);
    cout << "a : " << a << endl;
    a[3] = 7;
    cout << "a : " << a << endl;
    a.Fill(0);
    cout << "a : " << a << endl;
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
    return data[i];
}

int& IntArray::operator[](int i)  {
    return data[i];
}

int IntArray::Size() const {
    return 5;
}
