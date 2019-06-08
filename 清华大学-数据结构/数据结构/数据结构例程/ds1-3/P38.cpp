#include <iostream.h>
#include <stdlib.h>

#define DefaultSize 10
template < class Type>
class Array {
public:
    Array( int Size = DefaultSize );
    Array( const Array <Type> &x );
    ~Array() { destroy(); }
    Array<Type> &operator = ( const Array<Type> &A);
    Type & operator [] ( int i );
//    Array<Type> operator Type * ()const { return elements; }
    int Length() const { return ArraySize; }
    void ReSize ( int sz);
    friend ostream& operator <<(ostream& , Array<Type>&);
//    void Print();
private:
    Type *elements;
    int ArraySize;
    void getArray();
    void destroy(){delete[] elements;};
    void copyFrom(const Array<Type> &x);
}
template <class Type>
void Array<Type>::copyFrom(const Array<Type> &x)
{
    int n= x.ArraySize;
    ArraySize=n;
    elements = new Type[x.ArraySize];

    if ( elements == 0 )
    {
      cerr << "Memory Allocation Error" << endl;
      ArraySize=0;
      return;
    }
    Type *srcptr = x.elements;
    Type *destptr = elements;
    while (n--) *destptr++ = * srcptr++ ;
};


template <class Type> void Array<Type>::getArray() {
    elements = new Type[ArraySize];
    if ( elements == 0 )
    {
       cerr << "Memory Allocation Error" << endl;
       ArraySize=0;
    }
}

template <class Type> void Array<Type>::Array (int sz) {
    if ( sz <= 0 ) { cerr << "Invalid Array Size" << endl; return; }
    ArraySize = sz;
    getArray();
}

template <class Type> void Array<Type>::Array ( const Array<Type> &x ) {
   copyFrom(x);
}

template <class Type> Type& Array<Type>::operator[] (int i) {
    if ( i < 0 || i > ArraySize - 1 ) cerr << "Index out of Range" << endl;
    return elements[i];
}

template <class Type>
void Array<Type>::ReSize( int sz ) {

    if (( sz <= ArraySize )&&(sz>=0))
    {
	Type *newarray = new Type[sz];
	if (newarray == 0)
	{
	  cerr << "Memory Allocation Error" << endl;
	  return;
	}
	int n = ( sz <= ArraySize ) ? sz : ArraySize;
	Type *srcptr = elements;
	Type *destptr = newarray;
	while (n--) *destptr++ = *srcptr++ ;
	delete[] elements;
	elements = newarray;
	ArraySize = sz;
    }
}
template <class Type>
Array<Type> & Array<Type>::operator = ( const Array<Type> &a)
{
   destroy();
   copyFrom(a);
   return *this;
}
template <class Type>
ostream& operator <<(ostream& strm, Array<Type>& a)
{
  Type *p=a.elements;
  strm<<"Len:"<<a.ArraySize<<endl;
  for (int i=0;i<a.ArraySize;i++,p++)
  {
   strm<<*p<<' ';
  }
  strm<<endl;
   return strm;
}
/*
template <class Type>
void Array<Type>::Print()
{
  Type *p=elements;
  cout<<"Len:"<<ArraySize<<endl;
  for (int i=0;i<ArraySize;i++,p++)
  {
   cout<<*p<<' ';
  }
  cout<<endl;
}
*/