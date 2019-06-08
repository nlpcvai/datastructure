#include <datalist.h>
#include <selecttm.h>

template < class Type > void dataList <Type> :: BubbleSort() {
    int i = 1;
    int exchange = 1;
    while ( i < ArraySize && exchange ) {
	BubbleExchange ( i, exchange );
	i++;
    }
}

template < class Type > void dataList <Type> :: BubbleExchange ( const int i, int & exchange ) {
    exchange = 0;
    for ( int j = ArraySize - 1; j>=i; j-- )
      if ( Element[j-1] > Element[j] ) {
	  Swap (j-1,j);
	  exchange = 1;
      }
}

void main() {
    dataList<int> abc;
}