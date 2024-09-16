
#include <iostream>
using namespace std;

template<typename T, int N>
void MySort(T (&v)[N]) {
    for (int k = 1; k <= N; k++) {
        for (int i = 0; i < N - k; i++) {
            if (v[i] < v[i + 1]) {
                continue;
            }
            swap(v[i], v[i + 1]);
        }
    }
}

// void MySort(int (&v)[5]) {
//     for (int k = 1; k <= 5; k++) {
//         for (int i = 0; i < 5-k; i++) {
//             if (v[i] < v[i+1]) {
//                 continue;
//             }
//             swap(v[i], v[i+1]);
//         }
//     }
// }

// void MySort(double (&v)[5]) {
//     for (int k = 1; k <= 5; k++) {
//         for (int i = 0; i < 5-k; i++) {
//             if (v[i] < v[i+1]) {
//                 continue;
//             }
//             swap(v[i], v[i+1]);
//         }
//     }
// }

template<typename T, int N, typename = enable_if_t<!is_same<T, const char>::value>>
ostream& operator<<(ostream& os, T (&v)[N]) {
    if (N == 0) {
        return os << "[]";
    }
    os << "[" << v[0];
    for (int i = 1; i < N; i++) {
        cout << ", " << v[i];
    }
    return os << "]";
}

int main() {
    int    a[3] = {7, 3, 5};
    int    b[5] = {7, 3, 5, 9, 2};    
    double c[5] = {3.1, 7.5, 4.0, 9.7, 2.5};

    MySort(a);
    MySort(b);
    MySort(c);
    
    cout << "a: " << a << endl
         << "b: " << b << endl
         << "c: " << c << endl;
}
