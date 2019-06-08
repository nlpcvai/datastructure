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
  }

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


void main(){
  Stack<int> st;
  for(int i=0;i<10;i++)st.Push(i);
  int g=st.GetTop();
  cout<<g<<endl;
  while(!st.IsEmpty())
    cout<<st.Pop()<<endl;
  }
