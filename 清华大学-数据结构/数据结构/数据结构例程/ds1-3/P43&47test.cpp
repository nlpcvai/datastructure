template <class type> class SeqList {

public:
    SeqList ( int MaxSize = DefaultSize );
    ~SeqList() { delete[] data; }
    int Length() const { return last + 1; }
    int Find( Type & x ) const;
    int IsIn ( Type & x);
    int Insert ( Type & x, int i );
    int Remove ( Type & x);
    int Next ( Type & x );
    int Prior ( Type & x );
    int IsEmpty() { return last == -1; }
    int IsFull()  { return last == Maxsize - 1; }
    Type & Get( int i ) { return i < 0 || i > last ? NULL:data[i]; }
private:
    Type *data;
    int MaxSize;
    int last;
}

template < class Type > SeqList <Type>::SeqList( int sz ) {
    if ( sz > 0 ) {
       MaxSize = sz;  last = -1;
       data = new Type[MaxSize];
    }
}

template < class Type > int SeqList <Type>::Find( Type & x ) const {
    int i = 0;
    while ( i <= last && data[i] != x ) i++;
    if ( i > last ) return -1;
    else return i;
}

template < class Type > int SeqList <Type>::IsIn( Type & x ) {
    int i = 0, found = 0;
    while ( i <= last && !found)
	if ( data[i] != x ) i++;
	else found = 1;
    return found;
}

template < class Type > int SeqList <Type>::Insert( Type & x, int i ) {
    if ( i < 0 || i > last+1 || last == MaxSize - 1 ) return 0;
    else {
	last++;
	for ( int j = last; j > i; j-- ) data[j] = data[j-1];
	data[i] = x;
	return 1;
    }
}

template < class Type > int SeqList <Type>::Remove( Type & x ) {
    int i = Find(x);
    if ( i >= 0 ) {
	last--;
	for ( int j = i; j <= last; j++ ) data[j] = data[j+1];
	return 1;
    }
}

template < class Type > int SeqList <Type>::Next( Type & x ) {
    int i = Find(x);
    if ( i >= 0 && i < last ) return i+1;
    else return -1;
}

template < class Type > int SeqList <Type>::Prior( Type & x ) {
    int i = Find(x);
    if ( i > 0 && i < last ) return i-1;
    else return -1;
}

template < class Type > void Union( SeqList <Type> & LA, SeqList <Type> & LB ) {
    int n = LA.Length(); int m = LB.Length();
    for ( int i=1; i <= m; i++ ) {
	Type x = LB.Get(i);
	int k = LA.Find(x);
	if ( k == -1 ) { LA.Insert( n+1, x );  n++;}
    }
}

template < class Type > void Intersection ( SeqList <Type> & LA, SeqList <Type> & LB ) {
    int n = LA.Length();  int m = LB.Length();  int i = 1;
    while ( i < n ) {
	Type x = LA.Get(i);
	int k = LB.Find(x);
	if ( k == -1 ) { LA.Remove(i); n--; }
	else i++;
    }
}