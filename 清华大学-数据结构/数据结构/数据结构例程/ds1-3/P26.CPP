float abc ( float a, float b, float c ) {
    return a + b + b*c + (a+b-c)/(a+b) + 4.0;
}

float sum (float a[], const int n ) {
    float s = 0.0;
    for ( int i = 0; i < n; i++ ) s+=a[i];
    return s;
}

float rsum ( float a[], const int n ) {
    if ( n<=0 ) return 0;
    else return rsum ( a, n-1 ) + a[ n-1 ];
}