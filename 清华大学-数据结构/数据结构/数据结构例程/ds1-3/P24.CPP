int SeqSearch ( int a[], const int n, const int x ) {
    int i = 0;
    while ( i < n && a[i] != x ) i++;
    if ( i == n ) return -1;
    return i;
}

#include <iostream.h>
#include <time.h>

void TimeSearch() {
    int a[1001], n[20];
    for ( int j=1; j <= 1000; j++ ) a[j] = j;
    for ( j = 0; j < 10; j++ ) {
	n[j] = 10*j; n[j+10] = 100*(j+1);
    }
    cout << " n  time" << endl;
    for ( j = 0; j < 20; j++) {
       long start, stop;
       time (&start);
       int k = SeqSearch (a, n[j], 0);
       time (&stop);
       long runTime = stop - start;
       cout << " " << n[j] << "  " << runTime << endl;
    }
    cout << "Times are in hundreadths of a second." << endl;
}

void main () {
    TimeSearch();
}

