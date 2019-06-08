#include <iostream.h>
#include <assert.h>
template <class Type> class Stack{
  public:
    Stack(int=10);
    ~Stack(){delete []elements;}
    void Push(const Type& item);
    Type Pop();
    Type GetTop();
    void MakeEmpty() {top=-1;}
    int  IsEmpty() const {return top==-1;}
    int  IsFull() const {return top==maxsize-1;}
  private:
    int   top;
    Type* elements;
    int   maxsize;
  friend ostream & operator <<(ostream &,Stack<Type> &);
  };

  template <class Type> Stack<Type>::Stack(int s):top(-1),maxsize(s){
    elements=new Type[maxsize];
    assert(elements!=0);
    }

  template <class Type> void Stack<Type>::Push(const Type& item){
    assert(!IsFull());
    elements[++top]=item;
    }

  template <class Type> Type Stack<Type>::Pop(){
    assert(!IsEmpty());
    return elements[top--];
    }

  template <class Type> Type Stack<Type>::GetTop(){
    assert(!IsEmpty());
    return elements[top];
    }
