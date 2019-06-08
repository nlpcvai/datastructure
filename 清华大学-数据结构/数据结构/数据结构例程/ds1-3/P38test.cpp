#include <iostream.h>
#include <stdlib.h>

template < class Type > class Array {
public:
    Array ( int Size = DefaultSize );
    Array ( const Array <Type> &x );
    ~Array() { delete[] element; }
    Array <type> &operator = ( const Array<Type> &A);
    Type& operator [] ( int i );
    Array <Type> operator Type *() const { return elements; }
    int Length() const { return ArraySize; }
    void ReSize ( int sz;);
private:
    Type *elements;
    int ArraySize;
    void getArray();
}



template <class Type> void Array<Type>::getArray() {
    elements = new Type[ArraySize];
    if ( elements == 0 ) cerr << "Memory Allocation Error" << endl;
}

template <class Type> void Array<Type>::Array (int sz) {
    if ( sz <= 0 ) { cerr << "Invalid Array Size" << endl; return; }
    ArraySize = sz;
    getArray();
}

template <class Type> void Array<Type>::Array ( const Array<Type> &x ) {
    int ArraySize = n = x.ArraySize;
    elements = new Type[n];

    if ( elements == 0 ) { cerr << "Memory Allocation Error" << endl; return; }
    Type *srcptr = x.elements;
    Type *destptr = elements;
    while (n--) *destptr++ = * srcptr++ ;
}

template <class Type> Type& Array<Type>::operator[] (int i) {
    if ( i < 0 || i > ArraySize - 1 ) cerr << "Index out of Range" << endl;
    return elements[i];
}

template <class Type> void Array<Type>::Resize( int sz ) {
    if ( sz <= ArraySize ) {
	Type *newarray = new Type[sz];
	if (newarray == 0) cerr << "Memory Allocation Error" << endl;
	int n = ( sz <= ArraySize ) ? sz : ArraySize;
	Type *srcptr = elements;
	Type *destptr = newarray;
	while (n--) *destptr++ = *srcptr++ ;
	delete[] elements;
	elements = newarray;   ArraySize = sz;
    }
}