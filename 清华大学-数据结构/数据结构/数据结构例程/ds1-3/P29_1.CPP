float sum ( float a[], const int n ) {
    float s = 0.0;
    int count=0;
    count++;
    for ( int i=0; i<n; i++) {
	count++;
	s += a[i];
	count++;
    }
    count++;
    count++;
    return s;
}