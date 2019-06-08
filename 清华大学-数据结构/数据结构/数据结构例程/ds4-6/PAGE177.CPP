#include <bintree.h>
#include <stack.h>
#include <queue.h>
#include <process.h>

template <class Type> class TreeIterator{
  public:
    TreeIterator(const BinaryTree<Type> & BT):T(BT),current(NULL){}
    virtual ~TreeIterator(){}
    virtual void First()=0;
    virtual void operator ++ ()=0;
    int operator + () const {return current!=NULL;}
    const Type  operator()()const;
  protected:
    const BinaryTree<Type>  T;
    const BinTreeNode<Type> * current;
  private:
    TreeIterator(const TreeIterator<Type> & ){}
    const TreeIterator<Type> & operator = (const TreeIterator<Type> &);
    };

  template<class Type> const Type  TreeIterator<Type>::operator()()const{
    if(current==NULL){
      cerr<<"Illegal access"<<endl;
      exit(1);
      }
    return current->GetData();
    }

template <class Type> struct stkNode{
  const BinTreeNode<Type> * Node;
  int PopTim;
  stkNode(const BinTreeNode<Type> * N=NULL):Node(N),PopTim(0){}
  };

template <class Type> class PostOrder:public TreeIterator<Type>{
  public:
    PostOrder(const BinaryTree<Type> & BT);
    ~PostOrder(){}
    void First();
    void operator ++();
  protected:
    Stack <stkNode<Type> > st;
    };

  template <class Type> PostOrder<Type>::PostOrder(const BinaryTree<Type> & BT):
	TreeIterator<Type>(BT){
    st.Push(stkNode<Type>(BT.GetRoot()));
    }

  template <class Type> void PostOrder<Type>::First(){
    st.MakeEmpty();
    if(T.GetRoot()!=NULL) st.Push(stkNode<Type> (T.GetRoot()));
    operator ++();
    }

  template <class Type> void PostOrder<Type>::operator ++(){
    if(st.IsEmpty()){
      if(current==NULL){
	cerr<<"Advanced past end"<<endl;
	exit(1);
	}
      current=NULL;
      return;
      }
    stkNode<Type> Cnode;
    for(;;){
      Cnode=st.Pop();
      if(++Cnode.PopTim==3){
	current=Cnode.Node;
	return;
	}
      st.Push(Cnode);
      if(Cnode.PopTim==1){
	if(Cnode.Node->GetLeft()!=NULL)
	  st.Push(stkNode<Type> (Cnode.Node->GetLeft()));
	  }
	  else{
	    if(Cnode.Node->GetRight()!=NULL)
	      st.Push(stkNode<Type> (Cnode.Node->GetRight()));
	      }
	    }
	  }

template<class Type> class InOrder:public PostOrder<Type>{
  public:
    InOrder(BinaryTree<Type> & BT):PostOrder<Type> (BT){}
    void First();
    void operator ++();
    };


  template<class Type> void InOrder<Type>::First(){
    st.MakeEmpty();
    if(T.GetRoot()!=NULL) st.Push(stkNode<Type>(T.GetRoot()));
    operator ++();
    }

  template <class Type> void InOrder<Type>::operator ++(){
    if(st.IsEmpty()){
      if(current==NULL){
	cerr<<"Advanced past end"<<endl;
	exit(1);
	}
      current=NULL;
      return;
    }
    stkNode<Type> Cnode;
    for(;;){
      Cnode=st.Pop();
      if(++Cnode.PopTim==2){
	current=Cnode.Node;
	if(Cnode.Node->GetRight()!=NULL)
	  st.Push(stkNode<Type>(Cnode.Node->GetRight()));
	return;
	}
      st.Push(Cnode);
      if(Cnode.Node->GetLeft()!=NULL)
	st.Push(stkNode<Type>(Cnode.Node->GetLeft()));
      }
    }


template <class Type> class PreOrder:public TreeIterator<Type>{
  public:
    PreOrder(const BinaryTree<Type> & BT);
    ~PreOrder(){}
    void First();
    void operator ++();
  protected:
    Stack<const BinTreeNode<Type> * > st;
    };

  template <class Type> PreOrder<Type>::PreOrder(const BinaryTree<Type> & BT):
    TreeIterator<Type>(BT){
      st.Push(BT.GetRoot());
      }

  template <class Type> void PreOrder<Type>::First(){
    st.MakeEmpty();
    if(T.GetRoot())st.Push(T.GetRoot());
    operator ++();
    }

  template <class Type> void PreOrder<Type>::operator ++(){
    if(st.IsEmpty()){
      if(current==NULL){
	cerr<<"Advanced past end"<<endl;
	exit(1);
	}
      current=NULL;
      return;
      }
    current=st.Pop();
    if(current->GetRight()!=NULL) st.Push(current->GetRight());
    if(current->GetLeft()!=NULL) st.Push(current->GetLeft());
    return;
    }

template <class Type> class LevelOrder:public TreeIterator<Type>{
  public:
    LevelOrder(const BinaryTree<Type> & BT);
    ~LevelOrder(){}
    void First();
    void operator ++();
  protected:
    Queue<const BinTreeNode<Type> * > qu;
    };

  template <class Type> LevelOrder<Type>::LevelOrder(const BinaryTree<Type> & BT):
    TreeIterator<Type>(BT){qu.EnQueue(BT.GetRoot());}


  template <class Type> void LevelOrder<Type>::First(){
    qu.MakeEmpty();
    if(T.GetRoot()) qu.EnQueue(T.GetRoot());
    operator ++();
    }

  template <class Type> void LevelOrder<Type>::operator ++(){
    if(qu.IsEmpty()){
      if(current==NULL){
	cerr<<"Advanced past end"<<endl;
	exit(1);
	}
      current=NULL;
      return;
      }
    current=qu.DeQueue();
    if(current->GetLeft()!=NULL) qu.EnQueue(current->GetLeft());
    if(current->GetRight()!=NULL) qu.EnQueue(current->GetRight());
    }



void main(){
  BinaryTree<int> bt;
  cin>>bt;
  PostOrder<int> btpostorder(bt);
  btpostorder.First();
  cout<<"now,postorder:\n";
  while(+btpostorder){
    cout<<btpostorder()<<' ';
    ++btpostorder;
    }
  cout<<endl;
  InOrder<int> btinorder(bt);
  btinorder.First();
  cout<<"now,inorder:\n";
  while(+btinorder){
    cout<<btinorder()<<' ';
    ++btinorder;
    }
  cout<<endl;
  PreOrder<int> btpreorder(bt);
  btpreorder.First();
  cout<<"now,preorder:\n";
  while(+btpreorder){
    cout<<btpreorder()<<' ';
    ++btpreorder;
    }
  cout<<endl;
  LevelOrder<int> btlevelorder(bt);
  btlevelorder.First();
  cout<<"now,levelorder:\n";
  while(+btlevelorder){
    cout<<btlevelorder()<<' ';
    ++btlevelorder;
    }
  cout<<endl;
  }