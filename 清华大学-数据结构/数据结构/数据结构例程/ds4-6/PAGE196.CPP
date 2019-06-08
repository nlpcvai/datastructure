#include<stack.h>
#include<queue.h>
#define DefaultSize 20


template <class Type> class Tree;

template <class Type> class TreeNode {
  friend class Tree<Type>;
  private:
    Type data;
    TreeNode<Type> *firstChild, *nextSibling;
    TreeNode ( Type value=0, TreeNode<Type> *fc=NULL, TreeNode<Type> *ns=NULL ):data (value), firstChild (fc), nextSibling (ns) { }
    };


template <class Type> class Tree {
  public:
    Tree ( ) { root = current = NULL; }
    void BuildRoot(Type rootVal);
    int  Root();
    int  FirstChild();
    int  NextSibling();
    int  Parent();
    int  Find(Type target);
    void InsertChild(Type value);
    int  RemoveChild(int i);
    void RemovesubTree();
    void PreOrder();
    void NorecPreOrder();
    void PostOrder();
    void PostOrder1();
    void LevelOrder();
    int  IsEmpty();
    void visit();
  private:
    TreeNode<Type> *root, *current;
    void PreOrder ( ostream & out, TreeNode<Type> *p );
    int Find ( TreeNode<Type> *p, Type target );
    void RemovesubTree ( TreeNode<Type> *p );
    int FindParent ( TreeNode<Type> *t, TreeNode<Type> *p );
  };


  template <class Type> void Tree<Type>::BuildRoot ( Type rootVal ) {
    root = current = new TreeNode<Type> (rootVal);
    }

  template <class Type> int Tree<Type>:: Root ( ) {
    if ( root == NULL ) {
     current = NULL;
     return 0;
       }
      else {
	current = root;
	return 1;
	  }
    }

  template <class Type> int Tree<Type>::FirstChild ( ) {
    if ( current != NULL && current->firstChild != NULL ) {
      current = current->firstChild;  return 1;
      }
    current = NULL;
    return 0;
    }

  template <class Type> int Tree<Type>::NextSibling ( ) {
    if ( current != NULL && current->nextSibling != NULL ) {
      current = current->nextSibling;
      return 1;
       }
    current = NULL;  return 0;
    }

  template <class Type> int Tree<Type>::Parent ( ) {
    TreeNode<Type> *p = current,  *t;
    if ( current == NULL || current == root ) { current = NULL;  return 0; }
    t = root;
    int k = FindParent ( t, p );
    return k;
  }

  template <class Type> int Tree<Type>::FindParent ( TreeNode<Type> * t,TreeNode<Type> * p ){
    TreeNode<Type> *q = t->firstChild;
    while ( q != NULL && q != p ) {
      int i=FindParent(q,p);
      if( i )  return i;
      q = q->nextSibling;
      }
    if ( q != NULL && q ==p ) { current = t;  return 1; }
      return 0;
  }

  template <class Type> int Tree<Type>::Find ( Type target ) {
    if ( IsEmpty ( ) ) return 0;
    return Find ( root, target );
  }

  template <class Type> int Tree<Type>::Find ( TreeNode<Type> *p, Type target ) {
    int result = 0;
    if ( p->data == target ) { result = 1;  current = p; }
      else {
	TreeNode<Type> *q = p->firstChild;
	while ( q != NULL && ! ( result = Find ( q, target ) ) ) q = q->nextSibling;
		   }
		   return result;
		}

  template <class Type> void Tree<Type>::InsertChild ( Type value ) {
    TreeNode<Type> *newNode = new TreeNode<Type> (value);
    if ( current->firstChild == NULL ) current->firstChild = newNode;
      else {
	TreeNode<Type> *p = current->firstChild;
	while ( p->nextSibling != NULL ) p = p->nextSibling;
	p->nextSibling = newNode;
	}
    }

  template <class Type> int Tree<Type>::RemoveChild ( int i ) {
    TreeNode<Type> * s;
    if ( i == 1 ) {
      s = current->firstChild;
      if ( s != NULL ) current->firstChild = s->nextSibling;
      else return 0;
      }
      else {
	TreeNode<Type> *q = current->firstChild;  int k = 1;
	while ( q != NULL && k < i-1 ) { q = q->nextSibling;  k++; }
	if ( q != NULL ) {
	  s = q->nextSibling;
	  if ( s != NULL )q->nextSibling = s->nextSibling;
	  else return 0;
	 }
	 else return 0;
      }
    RemovesubTree(s);
    return 1;
    }

  template <class Type> void Tree<Type>::RemovesubTree ( TreeNode<Type> *p ) {
    TreeNode<Type> *q = p->firstChild,  *next;				
    while ( q != NULL ) {
      next = q->nextSibling;
      RemovesubTree ( q );  q = next;
      }
    delete p;
    }

  template <class Type> void Tree<Type>::RemovesubTree ( ) {
    if ( current != NULL ) {
      if ( current == root ) root = NULL;
	RemovesubTree ( current );  current = NULL;
	  }
    }

  template <class Type> void Tree<Type>::PreOrder ( ) {
    if ( !IsEmpty ( ) ) {
      visit ( );
      TreeNode<Type> *p = current;
      int i = FirstChild ( );
      while (i) { PreOrder ( );  i = NextSibling ( ); }
      current = p;
      }
    }

  template <class Type> void Tree<Type>::PostOrder ( ) {
    if ( !IsEmpty ( ) ) {
      TreeNode<Type> *p = current;
      int i = FirstChild ( );
      while (i) {
	PostOrder ( );
	i = NextSibling ( );
	  }
       current = p;
       visit ( );
	}
    }

  template <class Type> void Tree<Type>::NorecPreOrder( ) {
    Stack<TreeNode<Type>*> st;
    TreeNode<Type> *p = current;
    do {
      while ( !IsEmpty ( ) ) {
	visit ( );
	st.Push ( current );
	FirstChild ( );
	 }
      while ( IsEmpty ( ) && !st.IsEmpty ( ) ) {
       current = st.Pop ( );
       NextSibling ( );
	 }
	} while ( !IsEmpty ( ) );
    current = p;
    }

  template <class Type> void Tree<Type>::PostOrder1 ( ) {
    Stack<TreeNode<Type>* > st(DefaultSize);
    TreeNode<Type> *p = current;
    do {
      while ( !IsEmpty ( ) ) {
	st.Push(current);
	FirstChild ( );
	}
      while ( IsEmpty ( ) && !st.IsEmpty ( ) ) {
	current = st.Pop ( );
	visit ( );
	NextSibling ( );
	}
     } while ( !IsEmpty ( ) );
    current = p;
    }

  template <class Type> void Tree<Type>::LevelOrder ( ) {
    Queue<TreeNode<Type> * > Qu ;
    if ( ! IsEmpty ( ) ) {
      TreeNode<Type> *p = current;  Qu.EnQueue ( current );
      while ( !Qu.IsEmpty ( ) ) {
	current = Qu.DeQueue ( );
	visit ( );
	FirstChild ( );
	while ( !IsEmpty ( ) ) { Qu.EnQueue ( current );  NextSibling ( ); }
	}
      current = p;
    }
  }
  template<class Type> void Tree<Type>::visit(){
    cout<<current->data<<endl;
    }

  template<class Type> int Tree<Type>::IsEmpty(){
    return current==NULL;
    }


void main(){
  Tree<int> tree;
  tree.BuildRoot(100);
  for(int i=0;i<8;i++)  tree.InsertChild(i);
  tree.PreOrder();
  tree.PostOrder();
  tree.PostOrder1();
  tree.RemoveChild(5);
  tree.PreOrder();
  tree.NorecPreOrder();
  tree.LevelOrder();
  }
