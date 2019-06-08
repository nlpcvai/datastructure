template <class Type> class Queue{
  public:
    Queue(int=10);
    void EnQueue(const Type & item);
    Type DeQueue();
    Type GetFront();
    void MakeEmpty();
    int  IsEmpty() const;
    int  IsFull() const;
  }


