#define NULL 0
#define Max(x1,x2)  (x1>x2?x1:x2)
#include <iostream.h>

template <class Type> class BinaryTree;

template <class Type> class BinTreeNode{
  friend class BinaryTree<Type>;
  public:
    BinTreeNode():leftChild(NULL),rightChild(NULL){}
    BinTreeNode(Type item,BinTreeNode<Type> * left=NULL,BinTreeNode<Type> * right=NULL):data(item),leftChild(left),rightChild(right){}
    Type GetData() const {return data;}
    BinTreeNode<Type> * GetLeft() const {return leftChild;}
    BinTreeNode<Type> * GetRight() const {return rightChild;}
    void SetData(const Type & item){data=item;}
    void SetLeft(BinTreeNode<Type> * L){leftChild=L;}
    void SetRight(BinTreeNode<Type> * R){rightChild=R;}
    Type & GetData(){return data;}
    friend int equal(BinTreeNode<Type> *,BinTreeNode<Type> *);
  private:
    BinTreeNode<Type> * leftChild,* rightChild;
    Type data;
    };


template <class Type> class BinaryTree{
  public:
    void InOrder();
    void PreOrder();
    void PostOrder();
    int Depth(const BinTreeNode<Type> *) const;
    int Size(const BinTreeNode<Type> *)const;
    BinaryTree():root(NULL){}
    BinaryTree(Type value):RefValue(value),root(NULL){}
    BinaryTree(const BinaryTree<Type> &);
    virtual ~BinaryTree(){destroy(root);}
    virtual int IsEmpty(){return root==NULL;}
    virtual BinTreeNode<Type> * Parent(BinTreeNode<Type> * current){
      return root==NULL||root==current?NULL:Parent(root,current);
      }
    virtual BinTreeNode<Type> * LeftChild(BinTreeNode<Type> * current){
      return root!=NULL?current->leftChild:NULL;
      }
    virtual BinTreeNode<Type> * RightChild(BinTreeNode<Type> * current){
      return root!=NULL?current->rightChild:NULL;
      }
    virtual int Insert(const Type & item){ return Insert(root,item);}
    virtual int Find(const Type & item) const { return Find(root,item);}
    const BinTreeNode<Type> * GetRoot() const {return root;}
    friend istream & operator >> (istream & in,BinaryTree<Type> & Tree);
    friend ostream & operator << (ostream & out,BinaryTree<Type> & Tree);
    friend int operator == (const BinaryTree<Type> &,const BinaryTree<Type> &);
    BinTreeNode<Type> * GetRoot() {return root;}
  private:
    BinTreeNode<Type> * root;
    Type RefValue;
    BinTreeNode<Type> * Parent(BinTreeNode<Type> * start,BinTreeNode<Type> * current);
    int Insert(BinTreeNode<Type> * current,const Type & item);
    void Traverse(BinTreeNode<Type> * current,ostream & out) const;
    int Find(BinTreeNode<Type> * current,const Type & item) const;
    void destroy(BinTreeNode<Type> * current);
    void InOrder(BinTreeNode<Type> *);
    void PreOrder(BinTreeNode<Type> *);
    void PostOrder(BinTreeNode<Type> *);
    BinTreeNode<Type> * Copy(BinTreeNode<Type> *);
    };


  template <class Type> void BinaryTree<Type>::destroy(BinTreeNode<Type> * current){
    if(current!=NULL){
      destroy(current->leftChild);
      destroy(current->rightChild);
      delete current;
      }
    }

  template <class Type> BinTreeNode<Type> * BinaryTree<Type>::Parent(BinTreeNode<Type> * start,
	    BinTreeNode<Type> * current){
    if(start==NULL) return NULL;
    if(start->leftChild==current||start->rightChild==current) return start;
    BinTreeNode<Type> * p;
    if((p=Parent(start->leftChild,current))!=NULL) return p;
      else return Parent(start->rightChild,current);
    }

  template <class Type> void BinaryTree<Type>::Traverse(BinTreeNode<Type> * current,
	      ostream & out) const{
    if(current!=NULL){
      out<<current->data<<' ';
      Traverse(current->leftChild,out);
      Traverse(current->rightChild,out);
      }
   if(root==NULL) cout<<"The root is null."<<endl;
    }

  template <class Type> istream & operator >>(istream & in,BinaryTree<Type> & Tree){
    Type item,ref;
    cout<<"Construct binary tree:\n"<<"First,input the refvalue:";
    cin>>Tree.RefValue;
    cout<<"Input data (end with "<<Tree.RefValue<<"):";
    in>>item;
    while(item!=Tree.RefValue){
      Tree.Insert(item);
      cout<<"Input data (end with "<<Tree.RefValue<<"):";
      in>>item;
      }
    return in;
    }

  template <class Type> ostream & operator << (ostream & out,BinaryTree<Type> & Tree){
    out<<"Preorder traversal of bianry tree.\n";
    Tree.Traverse(Tree.root,out);
    out<<endl;
    return out;
    }

  template <class Type> void BinaryTree<Type>::InOrder(){
    InOrder(root);
    }

  template <class Type> void BinaryTree<Type>::InOrder(BinTreeNode<Type> * current){
    if(current!=NULL){
      InOrder(current->leftChild);
      cout<<current->data<<' ';
      InOrder(current->rightChild);
      }
    }

  template <class Type> void BinaryTree<Type>::PreOrder(){
    PreOrder(root);
    }

  template <class Type> void BinaryTree<Type>::PreOrder(BinTreeNode<Type> * current){
    if(current!=NULL){
      cout<<current->data<<' ';
      PreOrder(current->leftChild);
      PreOrder(current->rightChild);
      }
    }


  template <class Type> void BinaryTree<Type>::PostOrder(){
    PostOrder(root);
    }

  template <class Type> void BinaryTree<Type>::PostOrder(BinTreeNode<Type> * current){
    if(current!=NULL){
      PostOrder(current->leftChild);
      PostOrder(current->rightChild);
      cout<<current->data<<' ';
      }
    }

  template <class Type> int BinaryTree<Type>::Size(const BinTreeNode<Type> * t)const{
    if(t==NULL) return 0;
    return 1+Size(t->leftChild)+Size(t->rightChild);
    }

  template <class Type> int BinaryTree<Type>::Depth(const BinTreeNode<Type> * t)const{
    if(t==NULL) return -1;
    return 1+Max(Depth(t->leftChild),Depth(t->rightChild));
    }


  template <class Type> BinaryTree<Type>::BinaryTree(const BinaryTree<Type> & s){
    root=Copy(s.root);
    }

  template <class Type> BinTreeNode<Type> * BinaryTree<Type>::Copy(BinTreeNode<Type> * orignode){
    if(orignode==NULL) return NULL;
    BinTreeNode<Type> * temp=new BinTreeNode<Type>;
    temp->data=orignode->data;
    temp->leftChild=Copy(orignode->leftChild);
    temp->rightChild=Copy(orignode->rightChild);
    return temp;
    }

  template <class Type> int operator ==(const BinaryTree<Type> & s,const BinaryTree<Type> & t){
    return equal(s.root,t.root);
    }

  template <class Type> int equal(BinTreeNode<Type> * a,BinTreeNode<Type> * b){
    if(a==NULL && b==NULL) return 1;
    if(a!=NULL && b!=NULL && a->data==b->data
      && equal(a->leftChild,b->leftChild) && equal(a->rightChild,b->rightChild))
      return 1;
    return 0;
    }

  template<class Type> int BinaryTree<Type>::Find(BinTreeNode<Type>* current,const Type & item) const{
    if(current==NULL) return 0;
    if(current->data==item) return 1;
    return(Find(current->leftChild,item)||Find(current->rightChild,item));
    }

  template<class Type> int BinaryTree<Type>::Insert(BinTreeNode<Type>* current,const Type& item){
    if(current==root&&root==NULL){
       root=new BinTreeNode<Type>(item,NULL,NULL);
       root->data=item;
       return 1;
       }
    if(current==NULL) return 0;
    if(current->leftChild==NULL){
      BinTreeNode<Type>* temp=new BinTreeNode<Type>(item,NULL,NULL);
      current->leftChild=temp;
      return 1;
      }
    if(current->rightChild==NULL){
      BinTreeNode<Type>* temp=new BinTreeNode<Type>(item,NULL,NULL);
      current->rightChild=temp;
      return 1;
      }
    if(Depth(current->leftChild)<=Depth(current->rightChild)) return Insert(current->leftChild,item);
    return Insert(current->rightChild,item);
    }

