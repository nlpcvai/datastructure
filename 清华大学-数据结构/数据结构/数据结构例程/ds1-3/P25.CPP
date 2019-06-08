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
    /*const*/ long r[20]; /*= {3000000,3000000,3000000,3000000,1000000,1000000,800000,
	800000,500000,500000,250000,150000,100000,75000,70000,60000,50000,50000};*/
    for ( int i=0; i < 20; i++ ) r[i]=500000;
    for ( int j=1; j <= 1000; j++ ) a[j] = j;
    for ( j = 0; j < 10; j++ ) {
	n[j] = 10*j; n[j+10] = 100*(j+1);
    }
    cout << " n  totalTime  runTime" << endl;

    for ( j = 0; j < 20; j++) {
       long start, stop;
       time (&start);
       for (long b = 1; b <= r[j]; b++ )
	   int k = SeqSearch (a, n[j], 0);
       time (&stop);
       long totalTime = stop - start;
       float runTime = (float)(totalTime)/(float)(r[j]);
       cout << " " << n[j] << "  " << totalTime << "  " <<runTime << endl;
    }
    cout << "Times are in hundreadths of a second." << endl;
}

void main () {
    TimeSearch();
}

