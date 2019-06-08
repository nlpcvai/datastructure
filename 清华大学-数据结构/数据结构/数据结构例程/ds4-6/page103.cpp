template <class Type> class Stack{
  public:
    Stack(int=10);
    void Push(const Type& item);
    Type Pop();
    Type GetTop();
    void MakeEmpty();
    int  IsEmpty()const;
    int  IsFull()const;
  }