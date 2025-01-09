#include <stdio.h>

class OutputStream {
public:
    OutputStream& operator<<(const char* s) {
        printf("%s", s);
        return *this;
    }

    OutputStream& operator<<(int s) {
        printf("%d", s);
        return *this;
    }

    OutputStream& operator<<(double s) {
        printf("%f", s);
        return *this;
    }

    OutputStream& operator<<(char s) {
        printf("%c", s);
        return *this;
    }
};

OutputStream myCout;
char myEndl = '\n';

int main() {
    myCout << "3 + 5 == " << 3 + 5  << myEndl
           << "3 / 5 == " << 3 / 5. << myEndl;
    return 0;
}
