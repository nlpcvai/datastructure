#include <iostream.h>

void swap (int &i, int &j);

main() {
    int a = 1, b = 2;
    cout << "a and b:" << a << " " << b << endl;
    swap (a,b);
    cout << "a and b:" << a << " " << b << endl;
    return 0;
}

void swap (int &i, int &j) {
    int t=j;
    j = i;
    i = t;
}