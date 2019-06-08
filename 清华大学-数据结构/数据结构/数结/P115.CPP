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
    int  IsFull() const { return (rear+1)%maxSize==front;}
    int  Length() const { return (rear-front+maxSize)%maxSize;}
    friend ostream& operator <<(ostream& strm, Queue<Type>& a);
  private:
    int rear,front;
    Type* elements;
    int  maxSize;
  }


    template <class Type> Queue<Type>::Queue(int sz):front(0),rear(0),maxSize(sz+1){
    elements=new Type[maxSize];
    assert(elements!=0);
    }

  template <class Type> void Queue<Type>::EnQueue(const Type & item){
    assert(!IsFull());
    rear=(rear+1)%maxSize;
    elements[rear]=item;
    }

  template <class Type> Type Queue<Type>::DeQueue(){
    assert(!IsEmpty());
    front=(front+1)%maxSize;
    return elements[front];
    }

  template <class Type> Type Queue<Type>::GetFront(){
    assert(!IsEmpty());
    return elements[(front+1)%maxSize];
    }

template <class Type>
ostream& operator <<(ostream& strm, Queue<Type>& a)
{
  strm<<"Front:"<<a.front<<"  Rear:"<<a.rear<<endl;
  if (a.front!=a.rear)
  {
    int i=a.front;
    do
    {
      i=(i+1)%a.maxSize;
      strm<<a.elements[i];
    }while (i!=a.rear);
  };
  strm<<endl;
  return strm;
}


