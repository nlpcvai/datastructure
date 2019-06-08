void selectSort ( int a[], const int n) {
    for (int i=0; i<n-1; i++ ) {
	int k = i;
	for (int j=i+1; j<n; j++)
	    if ( a[j] < a[k] )  k=j;
	int temp = a[i]; a[i] = a[k]; a[k] = temp;
    }
}

#include <iostream.h>

void main() {
    static  int a[10] = {98,87,76,67,45,32,54,110,67,90 };
    int n = 8;
    selectSort( a, n );
    for (int i=0; i<n; i++) cout << a[i] << "  ";
    cout << endl;

}