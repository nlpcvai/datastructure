float rsum ( float a[], const int n ) {
    int count=0;
    count++;
    if ( n <= 0 ) {
	count++;
	return 0;
    }
    else {
	count++;
	return rsum ( a, n-1 ) + a[n-1];
    }
}