template <class Type> class ExtBinTree;

template <class Type> class Element {
  friend class ExtBinTree;
  private:
    Type data;
    Element<Type> *leftChild, *rightChild;
  };

template <class Type> class ExtBinaryTree {
  public:
    ExtBinTree ( ExtBinTree<Type> &bt1, ExtBinTree<Type> &bt2 ) {
      root->leftChild = bt1.root;
      root->rightChild = bt2.root;
      root->data.key = bt1.root->data.key + bt2.root->data.key;
	}
  protected:
    const int DefaultSize = 20;
    Element<Type> *root;
    MinHeap< ExtBinTree<Type> > hp;
  }




  template <class Type> void HuffmanTree ( Type *fr, int n, ExtBinTree<Type> & newtree ) {
    ExtBinTree<Type> & first, & second;
    ExtBinTree<Type> Node[DafualtSize];
    if ( n > DefaultSize ) {
      cerr << "Size n " << n << "exceeds the boundary of Array" << endl;
      return;
      }
    for ( int i=0; i<n; i++ ) {
      Node[i].root->data.key = fr[i];
      Node[i].root->leftChild = Node[i].root->rightChild = NULL;
	}
    hp.MinHeap ( Node, n );
    for ( int i=0; i<n-1; i++ ) {
      hp.RemoveMin ( first );  hp.RemoveMin ( second );
      newtree = new ExtBinTree<Type> ( first, second );
      hp.Insert ( newtree );
      }
    return hp.RemoveMin ( newtree );
  }
