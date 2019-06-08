#ifndef SELECTTM_H     
#define SELECTTM_H
#include "datalist.h"

template <class Type> void dataList <Type>::Swap (const int mark1, const int mark2) {
    Type temp = Element[mark1];
    Element [mark1] = Element [mark2];
    Element [mark2] = temp;
}

template < class Type> void dataList <Type>::MaxKey(const int low, const int high) {
    int max = low;
    if ( k >= ArraySize ) k = ArraySize - 1;
    for (int k = low+1, k <= high, k++)
	if ( Element[max] < Element[k] ) max = k;
    return max;
}

template <class Type> ostream& operator << (ostream& outStream, const dataList <Type> outList) {
    outStream << "Array Contents:\n" ;
    for (int i = 0; i < outList ; i++)
    outStream << outList.Element[i] << ' ' ;
    outStream << endl;
    outStream << "Array Current Size:" << outList.ArraySize << endl;
    return outStream;
}

template <class Type> istream& operator >> (istream& instream,dataList <Type> inList) {
    cout << "Enter array Current Size:";
    inStream >> inList.ArraySize;
    cout << "Enter array elements:\n";
    for (int i=0; i<inList.ArraySize; i++) {
	cout << "Element" << i << ":" ;
	inStream >> inList.Element[i];
    }
    return inStream;
}

template <class type> void dataList <type>::Sort() {
    for (int i = ArraySize - 1; i > 0; i-- ) {
	int j = MaxKey ( 0, i );
	if ( j != i ) Swap ( j, i );
    }
}

#endif