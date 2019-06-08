#include <assert.h>
#include <iostream.h>
#define NULL 0
template <class Type> class Stack;

template <class Type> class StackNode{
  friend class Stack<Type>;
  friend ostream& operator <<(ostream& strm, Stack<Type>& a);
  private:
    Type data;
    StackNode<Type>* link;
    StackNode(Type d=0,StackNode<Type>* l=NULL):data(d),link(l){}
  };




template <class Type> class Stack{
  public:
    Stack():top(NULL){}
    ~Stack();
    void Push(const Type& item);
    Type Pop();
    Type GetTop();
    void MakeEmpty(){top=NULL;}
    int  IsEmpty() const {return top==NULL;}
    friend ostream& operator <<(ostream& strm, Stack<Type>& a);
  private:
    StackNode<Type>* top;
  }

  template <class Type> void Stack<Type>::~Stack(){
    StackNode<Type>* p;
    while(top!=NULL){p=top;top=top->link;delete p;}
    }

  template <class Type> void Stack<Type>::Push(const Type& item){
    top=new StackNode<Type>(item,top);
    }

  template <class Type> Type Stack<Type>::Pop(){
    assert(!IsEmpty());
    StackNode<Type>* p=top;
    Type retvalue=p->data;
    top=top->link;
    delete p;
    return retvalue;
    }

  template <class Type> Type Stack<Type>::GetTop(){
    assert(!IsEmpty());
    return top->data;
    }

template <class Type>
ostream& operator <<(ostream& strm, Stack<Type>& a)
{
  StackNode<Type>* p=a.top;
  while (p!=NULL)
  {
   strm<<p->data<<' ';
   p=p->link;
  }
  strm<<endl;
   return strm;
}