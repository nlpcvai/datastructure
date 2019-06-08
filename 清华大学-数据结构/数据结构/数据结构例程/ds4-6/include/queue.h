#include <assert.h>
#define null 0
#include <iostream.h>
template <class Type> class Queue;


template <class Type> class QueueNode{
  friend class Queue<Type>;
  private:
    Type data;
    QueueNode<Type> * link;
    QueueNode(Type d=0,QueueNode *l=null):data(d),link(l){}
  };


template <class Type> class Queue{
  public:
    Queue():rear(null),front(null){}
    ~Queue();
    void EnQueue(const Type & item);
    Type DeQueue();
    Type GetFront();
    void MakeEmpty(){front=rear=null;}
    int  IsEmpty() const {return front==null;}
  private:
    QueueNode<Type> *front,*rear;
  };

  template <class Type> void Queue<Type>::~Queue(){
    QueueNode<Type> * p=front;
    while(front!=null){
      p=front;
      front=front->link;
      delete p;
      }
    }

  template <class Type> void Queue<Type>::EnQueue(const Type & item){
    if(front==null) front=rear=new QueueNode<Type>(item,null);
      else rear=rear->link=new QueueNode<Type>(item,null);
    }

  template <class Type> Type Queue<Type>::DeQueue(){
    assert(!IsEmpty());
    QueueNode<Type> * p=front;
    Type retvalue=p->data;
    front=front->link;
    delete p;
    return retvalue;
    }

  template <class Type> Type Queue<Type>::GetFront(){
    assert(!IsEmpty());
    return front->data;
    }




