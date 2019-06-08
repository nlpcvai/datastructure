#include<iostream.h>
template <class Type> class MinPQ {
  public:
    virtual int Insert ( const Type & ) = 0;
    virtual int RemoveMin ( Type & ) = 0;
  }


template <class Type> class MinHeap : public MinPQ<Type> {
  public:
    MinHeap ( int maxSize );
    MinHeap ( Type arr[ ], int n );
    ~MinHeap ( ) { delete [ ] heap; }
    const MinHeap<Type> & operator = ( const MinHeap<Type> &R );
    int Insert ( const Type &x );
    int RemoveMin ( Type &x );
    int IsEmpty ( ) const { return CurrentSize == 0; }
    int IsFull ( ) const { return CurrentSize == MaxHeapSize; }
    void MakeEmpty ( ) { CurrentSize = 0; }
    void PrintHeap();
  private:
    enum { DefaultSize =10};
    Type *heap;
    int CurrentSize;
    int MaxHeapSize;
    void FilterDown ( int i, int m );
    void FilterUp ( int i );
	}

  template <class Type> MinHeap<Type>::MinHeap ( int maxSize ) {
    MaxHeapSize = DefaultSize < maxSize ? maxSize : DefaultSize;
    heap = new Type [MaxHeapSize];
    CurrentSize = 0;
    }

  template <class Type> MinHeap<Type>::MinHeap ( Type arr[ ], int n ) {
    MaxHeapSize = DefaultSize < n ? n : DefaultSize;
    heap = new Type [MaxHeapSize];
    for(int i=0;i<=n;i++) heap[i].key=arr[i].key;
    CurrentSize = n+1;               //n is arr's maximum index.
    int currentPos = (CurrentSize-2)/2;
    while ( currentPos >= 0 ) {
      FilterDown ( currentPos, CurrentSize-1 );
      currentPos--;
      }
   }


  template <class Type> void MinHeap<Type>::FilterDown ( int start, int EndOfHeap ) {
    int i = start,   j = 2*i+1;	Type temp = heap[i];
    while ( j <= EndOfHeap ) {
      if ( j < EndOfHeap && heap[j].key > heap[j+1].key ) j++;
      if ( temp.key <= heap[j].key ) break;
	else {
	heap[i] = heap[j];
	i = j;
	j = 2*j+1; }
      }
    heap[i] = temp;
    }

  template <class Type> void MinHeap<Type>::FilterUp ( int start ) {
    int j = start,  i = (j-1)/2;   Type temp = heap[j];
    while ( j > 0 ) {
      if ( heap[i].key <= temp.key ) break;
	else {  heap[j] = heap[i];  j = i;  i = (i -1)/2; }
		   }
    heap[j] = temp;
    }


  template <class Type> int MinHeap<Type>::Insert ( const Type &x ) {
    if ( CurrentSize == MaxHeapSize ) {
    cerr << "Heap Full" << endl;
     return 0;
      }
    heap[CurrentSize] = x;
    FilterUp (CurrentSize);
    CurrentSize++;
    return 1;
  }


  template <class Type> int MinHeap<Type>::RemoveMin ( Type &x ) {    //return the minimum through the reference of x.
    if ( !CurrentSize ) { cout << "Heap empty" << endl;  return 0; }
    x = heap[0];
    heap[0] = heap[CurrentSize-1];
    CurrentSize--;
    FilterDown ( 0, CurrentSize-1 );
    return 1;
   }

  template<class Type> void MinHeap<Type>::PrintHeap(){
    for(int i=0;i<CurrentSize;i++)
    cout<<heap[i].key<<endl;
    }

void main(){
  struct  data{
    int key;
    };
  static data array[10]={{10},{9},{8},{7},{6},{5},{4},{3},{2},{1}};
  MinHeap<data> minh(array,9);
  int i;
  for(i=0;i<10;i++)cout<<array[i].key<<endl;
  cout<<"now,this is the heap:"<<endl;
  minh.PrintHeap();
  data temp;
  minh.RemoveMin(temp);
  cout<<"the heap has removed:"<<endl;
  minh.PrintHeap();
  cout<<"The minimum's key is:"<<temp.key<<endl;
  temp.key=100;
  minh.Insert(temp);
  cout<<"the heap has inserted:"<<endl;
  minh.PrintHeap();
  }
