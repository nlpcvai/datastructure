template<class Type> class ThreadNode{
  friend class ThreadTree;
  friend class ThreadInorderIterator;
  private:
    int leftThread,rightThread;
    ThreadNode<Type> * leftChild,* rightChild;
    Type data;
  public:
    ThreadNode(const Type item):data(item),leftChild(NULL),rightChild(NULL),
	  leftThread(0),rightThread(0){}
	  };

template<class Type>class ThreadTree{
  friend class ThreadInorderIterator;
  public:
    void InThread(ThreadNode<Type> *,ThreadNode<Type> *);
    void CreateInThread();
    void InsertRight(ThreadNode<Type> *,ThreadNode<Type> *);
  private:
    ThreadNode<Type> * root;
    };

template<class Type> class ThreadInorderIterator{
  public:
    ThreadInorderIterator(ThreadTree<Type> & Tree): T(Tree){current=T.root;}
    ThreadNode<Type> * First();
    ThreadNode<Type> * Last();
    ThreadNode<Type> * Next();
    ThreadNode<Type> * Prior();
  private:
    ThreadTree<Type> & T;
    ThreeNode<Type> * current;
    }

  template<class Type> ThreadNode<Type> * ThreadInorderIterator<Type>::First(){
    while(current->leftThread==0)current=current->leftChild;
    return current;
    }

  template<class Type> ThreadNode<Type> * ThreadInorderIterator<Type>::Next(){
    ThreadNode<Type> * p=current->rightChild;
    if(current->rightThread==0)
      while(p->leftThread==0)p=p->leftChild;
    current=p;
    if(current==T.root) return NULL;
    else return current;
    }

  template<class Type> void ThreadInorderIterator<Type>::Inorder(){
    ThreadNode<Type> * p;
    for(p=First();p!=NULL;p=Next())cout<<p->data<<endl;
    }

  template<class Type> void ThreadTree<Type>::InThread(ThreadNode<Type> * current,ThreadNode<Type> * pre){
    if(current!=NULL){
      InThread(current->leftChild,pre);
      if(current->leftChild==NULL){
	current->leftChild=pre;
	current->leftThread=1;
	}
      if(pre->rightChild==NULL){
	pre->rightChild=current;
	pre->rightThread=1;
	}
      pre=current;
      InThread(current->rightChild,pre);
      }
    }

  template<class Type> void ThreadTree<Type>::CreateInThread(){
    ThreadNode<Type> * pre;
    root=new ThreadNode<Type>;
    root->leftThread=1;
    root->rightThread=0;
    if(this==NULL){
      root->leftChild=root;
      root->rightChild=root;
      }
      else{
	current=root->leftChild=this;
	root->leftThread=0;
	pre=root;
	InThread(current,pre);
	pre->rightChild=root;
	pre->rightThread=1;
	}
      }


  template <class Type> void ThreadTree<Type>::InsertRight ( ThreadNode<Type> *s,
	    ThreadNode<Type> *r ) {
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;  r->leftThread = 1;
    s->rightChild = r;  s->rightThread = 0;
    if ( r->rightThread == 0 ) {
      current = r->rightChild;
      ThreadNode<Type> *temp = First ( );
      temp->leftChild = r;
    }

  }



