#include <iostream.h>
#include <assert.h>
template <class Type> class Queue{
  public:
    Queue(int=10);
    ~Queue(){ delete []elements;}
    void EnQueue(const Type & item);
    Type DeQueue();
    Type GetFront();
    void MakeEmpty(){ front=rear=0;}
    int  IsEmpty() const { return front==rear;}
    int  IsFull() const { return (rear+1)%maxsize==front;}
    int  Length() const { return (rear-front+maxsize)%maxsize;}
  private:
    int rear,front;
    Type* elements;
    int  maxsize;
  }


    template <class Type> Queue<Type>::Queue(int sz):front(0),rear(0),maxsize(sz){
    elements=new Type[maxsize];
    assert(elements!=0);
    }

  template <class Type> void Queue<Type>::EnQueue(const Type & item){
    assert(!IsFull());
    rear=(rear+1)%maxsize;
    elements[rear]=item;
    }

  template <class Type> Type Queue<Type>::DeQueue(){
    assert(!IsEmpty());
    front=(front+1)%maxsize;
    return elements[front];
    }

  template <class Type> Type Queue<Type>::GetFront(){
    assert(!IsEmpty());
    return elements[(front+1)%maxsize];
    }




void main(){
  Queue<int> que(7);
  for(int i;!que.IsFull();i++)que.EnQueue(i);
  cout<<que.Length()<<que.GetFront();
  for(;!que.IsEmpty();)cout<<que.DeQueue();
  }