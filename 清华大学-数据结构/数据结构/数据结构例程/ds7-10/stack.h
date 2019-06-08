#include <iostream.h>
#include <assert.h>
const MaxStack=100;
template <class Type> class Stack{
  public:
    Stack(const int=MaxStack);
    ~Stack(){delete []elements;}
    void Push(const Type& item);
    Type Pop();
    Type GetTop();
    void MakeEmpty() {top=-1;}
    int  IsEmpty() const {return top==-1;}
    int  IsFull() const {return top==maxsize-1;}
    friend ostream& operator <<(ostream& strm, Stack<Type>& a);
  private:
    int   top;
    Type* elements;
    int   maxsize;
  };

  template <class Type> Stack<Type>::Stack(const int s):top(-1),maxsize(s){
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


template <class Type>
ostream& operator <<(ostream& strm, Stack<Type>& a)
{
  Type *p=a.elements;
  strm<<"Top:"<<a.top<<endl;
  for (int i=0;i<=a.top;i++,p++)
  {
   strm<<*p<<' ';
  }
  strm<<endl;
   return strm;
}