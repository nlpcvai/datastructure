#include <iostream.h>

void example ( float** x, const int m, int n )
{
    float *sum ;
    for ( int i=0; i<m; i++ ) {
	sum[i] = 0.0;
	for ( int j=0; j<n; j++ )
	  sum[i] += x[i][j];
    }
    for ( i=0; i<m; i++ )
      cout << "Line" << i << ":" << sum[i] << endl;
}

void main() {
   static float a[3][2]={1,2,3,4,5,6};
   example(a,3,2);
}