#include <assert.h>
#include <iostream.h>
#include <stdio.h>
const int maxpqsize=20;

template <class Type> class PQueue{
  public:
    PQueue();
    ~PQueue(){ delete []pqelements;}
    void PQInsert(const Type & item);
    Type PQRemove();
    void MakeEmpty(){ count=-1;}
    int  IsEmpty() const { return count==-1;}
    int  IsFull() const {return count==maxpqsize;}
    int  Length() const {return count+1;}
  private:
    Type * pqelements;
    int  count;
  }

  template <class Type> PQueue<Type>::PQueue():count(-1){
    pqelements=new Type[maxpqsize];
    assert(pqelements!=0);
    }

  template <class Type> void PQueue<Type>::PQInsert(const Type & item){
    assert(!IsFull());
    count++;
    pqelements[count]=item;
    }

  template <class Type> PQueue<Type>::PQRemove(){
    assert(!IsEmpty());
    Type min=pqelements[0];
    int minindex=0;
    for(int i=0;i<=count;i++)
      if(pqelements[i]<min){
	min=pqelements[i];
	minindex=i;
	}
    pqelements[minindex]=pqelements[count];
    count--;
    return min;
  }





void main(){
  PQueue<int> pq;
  static int arr[10]={2,9,1,-100,23,98,16,56};
  for(int i=0;i<10;i++)pq.PQInsert(arr[i]);
  while(!pq.IsEmpty())cout<<pq.PQRemove()<<endl;
  pq.MakeEmpty();
  while(!pq.IsFull())pq.PQInsert(i++);
  while(!pq.IsEmpty())cout<<pq.PQRemove()<<endl;
  }

