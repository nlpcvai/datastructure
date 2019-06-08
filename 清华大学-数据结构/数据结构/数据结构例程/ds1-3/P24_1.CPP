int SeqSearch ( int a[], const int n, const int x ) {
    int i = 0;
    while ( i < n && a[i] != x ) i++;
    if ( i == n ) return -1;
    return i;
}

#include <iostream.h>
void main() {
    static int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int i = SeqSearch ( a, 10, 6);
    cout << "The location is: " << i << endl;
}