#include <iostream.h>
#include "P170.cpp"
#include "Stack.h"
const MaxN=30;
template <class Type> class BST;							//二叉搜索树的前视声明

template <class Type> class BstNode : public BinTreeNode<Type> {			//二叉搜索树结点类
friend class BST;
public:
   BstNode ( const Type d=0, BstNode *L=NULL, BstNode *R =NULL)			//构造函数
      : data (d), leftChild (L), rightChild (R) { };
   ~BstNode ( ) { }
   friend class BST<Type>;
protected:
   Type data;										//数据域(用作关键码)
   BstNode<Type> *leftChild, *rightChild;						//左子女和右子女链域
};

template <class Type> class BST : BinaryTree <Type> {					//二叉搜索树类定义
public:
	BST ( ) :root(NULL){};								//构造函数
   BST ( Type value ) ;
   BST (const BST<Type> & T) ;//构造函数
   ~BST ( ) { MakeEmpty (  ); }							//析构函数
   const BST & operator = ( const BST & Value );
   void MakeEmpty( ) { destroy (root);  root=NULL; }
   void PrintTree ( ) const { PrintTree ( root ); }
   int Find ( const Type & x ) const { return (Find ( x, root )!=NULL) ; }	//搜索元素
   Type Min() { return Min(root)->data;};										//求最小
   Type Max() { return Max(root)->data;};										//求最大
   int Insert ( const Type & x ) { return Insert ( x, root ); }				//插入新元素
   int Remove (const Type & x ) { return Remove ( x, root ); }				//删除含x的结点
   BstNode<Type> *Split ( Type i, BST<Type> &B, Type &x, BST<Type> &C );
   void OpticBST ( int p[ ], int q[ ], Type a[ ], int n );
   friend class BSTIterator ;//中序游标类
   
private:											//在关键码i处分解二叉搜索树
   BstNode<Type> *root;								//二叉搜索树的根指针
   Type RefValue;										//数据输入停止的标志, 用于输入
   BstNode<Type> *lastfound;								//最近搜索到的结点的指针
//   void MakeEmpty ( BstNode<Type> * ptr );					//置空
   int Insert ( const Type & x, BstNode<Type> * & ptr );			//插入
   int Remove ( const Type & x, BstNode<Type> * & ptr );			//删除
   void PrintTree ( BstNode<Type> * ptr ) const;					//打印
   BstNode<Type> *Copy (const BstNode<Type> * ptr );				//复制
   BstNode<Type> *Find (const Type & x, BstNode<Type> * ptr ) const;	//搜索
   BstNode<Type> *Min ( BstNode<Type> * ptr ) const;				//求最小
   BstNode<Type> *Max ( BstNode<Type> * ptr ) const;				//求最大 
};
/*
template <class Type> 
BstNode<Type> * BST<Type>::Find (const Type & x, BstNode<Type> * ptr ) const {
//私有函数：在以ptr为根的二叉搜索树中搜索含x的结点。若找到，则函数返回该结点的地址，否则函数返回
//NULL值。
   if ( ptr == NULL ) return NULL;
   else if ( x < ptr->data ) return Find ( x, ptr->leftChild );			//到左子树中继续搜索
	 else if ( x > ptr->data ) return Find( x, ptr->rightChild );			//到右子树中继续搜索
	    else return ptr;								//搜索成功
}
*/
template <class Type> BstNode<Type> *BST<Type>::Find (const Type & x, BstNode<Type> * ptr ) const {
//私有函数: 说明与程序7.14相同
   if ( ptr != NULL ) {									//树空返回
	 BstNode<Type> * temp = ptr;							//从根开始搜索
	 while ( temp != NULL ) {								//==NULL表示搜索失败
	    if ( temp->data == x ) return temp;					//搜索成功
	    if ( temp->data < x ) temp = temp->rightChild;				//否则，继续搜索右子树
	    else temp = temp->leftChild;						//否则，继续搜索左子树
	 }
   }
   return NULL;
};
template <class Type> int BST<Type>::
Insert (const Type & x, BstNode<Type> * & ptr) {
//私有函数：在以ptr为根的二叉搜索树中插入所含值为x的结点。若在树中已经有含x的结点，则不插入。
   if ( ptr == NULL )	{							//新结点作为叶结点插入
	 ptr = new BstNode<Type> (x);						//创建新结点
	 if ( ptr == NULL ) return 0; else return 1;
   }
   else if ( x < ptr->data ) return Insert ( x, ptr->leftChild );			//小于根的关键码, 向左子树插入
	 else if ( x > ptr->data ) return Insert ( x, ptr->rightChild );		//大于, 向右子树插入
   return 1;
							//除上述情况外, 就是x已在树中的情形, 不再插入
}



template <class Type>BST<Type>::BST ( Type value ) {
//输入一个元素序列, 建立一棵二叉搜索树
   Type x;  root = NULL;  RefValue = value;			//置空树
   cin >> x;									//输入数据
   while ( x != RefValue )
   {						//RefValue是一个输入结束标志
      Insert ( x, root );  cin >> x;					//插入，再输入数据
   }
}

template <class Type>
void BST<Type>::PrintTree ( BstNode<Type> * ptr ) const					//打印
{
	if (ptr!=NULL)
	{
		cout<<ptr->data;
		cout<<"(";
		PrintTree(ptr->leftChild);
		cout<<",";
		PrintTree(ptr->rightChild);
		cout<<")";
	}
}


template <class Type> int BST<Type>::Remove (const Type &x, BstNode<Type> * &ptr) {
//私有函数：在以ptr为根的二叉搜索树中删除含x的结点。若删除成功则新根通过ptr返回。
   BstNode<Type> * temp;
   if ( ptr != NULL )
	if ( x < ptr->data ) return Remove ( x, ptr->leftChild );				//在左子树中执行删除
	else if ( x > ptr->data )  return Remove ( x, ptr->rightChild );			//在右子树中执行删除
	   else if ( ptr->leftChild != NULL && ptr->rightChild != NULL )	{
						// ptr指示关键码为x的结点，它有两个子女
		   temp = Min ( ptr->rightChild );					//在ptr的右子树中搜寻最小结点
		   ptr->data = temp->data;						//用该结点数据代替根结点数据
		   return Remove ( ptr->data, ptr->rightChild );				//在右子树中删除该结点
		 }
		 else {				// ptr指示关键码为x的结点，它只有一个或零个子女
			  temp = ptr;
			  if ( ptr->leftChild == NULL ) ptr = ptr->rightChild;		//只有右子女
			  else if ( ptr->rightChild == NULL ) ptr = ptr->leftChild;	//只有左子女
		      delete temp;
		      return 1;
		    }
   else return 0;
}
template <class Type> class InorderIterator	{	    			//中序游标类定义
public:
   InorderIterator ( BST<Type> & Tree ) : ref (Tree) { Init ( ); }
   int Init ( );									//初始化
   int operator ! ( );								//求反
   Type operator ( ) ( );								//取栈顶元素值
   int operator ++ ( );								// BST按前序进行遍历
private:
   BST<Type> & ref;								//二叉搜索树对象
   Stack < BstNode<Type> * > itrStack;					//迭代工作栈
};

template <class Type> int InorderIterator<Type>::Init ( ) {			//初始化操作
   itrStack.MakeEmpty ( );								//置迭代工作栈为空
   if ( ref.root != NULL ) itrStack.Push ( ref.root );				//若二叉搜索树不空则根指针进栈
   return ! itrStack.IsEmpty ( );							//若栈空则返回0，否则返回1
}

template <class Type> int InorderIterator<Type>::operator ! ( ) {
   return ! itrStack.IsEmpty ( );							//若栈空则返回0，否则返回1
}

template <class Type> Type InorderIterator<Type>::operator ( ) ( ) {	//返回当前结点的数据值
   Node<Type> * current = itrStack.GetTop ( );				//取栈顶结点为当前结点
   return current->data;								//返回当前结点的关键码
}

template <class Type> int InorderIterator<Type>::operator ++ ( ) {
//按二叉搜索树结点的前序序列进栈。还可以向前走则函数返回1, 否则返回0。
   BstNode<Type> * current = itrStack.GetTop ( );				//取存在栈顶上的结点
   BstNode<Type> * next = current->leftChild;				//左子女
   if ( next != NULL ) { itrStack.Push ( next );  return 1; }			//左子女非空, 进栈(向左子树遍历)
   while ( ! itrStack.IsEmpty ( ) ) {						//否则, 若栈非空
      current = itrStack.Pop ( );   next = current->rightChild;		//退栈, 取其右子女
      if ( next != NULL ) { itrStack.Push ( next );  return 1; }		//右子女非空, 进栈
   }
   return 0;
}

/*template <class Type>
BST<Type>::BST (const BST<Type> & T) : root (NULL) {
//构造函数：根据参数初始化树T
   InorderIterator<Type> itr ( Type );						//声明中序游标类对象
   for ( itr.init ( ); ! itr; itr++) Insert ( itr ( ) );				//按前序顺序插入
}*/

template <class Type>
BstNode<Type> * BST<Type>::Min ( BstNode<Type> * ptr ) const				//求最小
{
  BstNode<Type> * temp1,*temp2;
  temp1=ptr;
  if (ptr!=NULL)
  {
    if (ptr->leftChild!=NULL)
    {
	temp2=Min(ptr->leftChild);
	if (temp1->data>temp2->data) temp1=temp2;
    }
    if (ptr->rightChild!=NULL)
    {
	temp2=Min(ptr->rightChild);
	if (temp1->data>temp2->data) temp1=temp2;
    }
  }
  return temp1;
}

template <class Type>
BstNode<Type> * BST<Type>::Max ( BstNode<Type> * ptr ) const				//求最小
{
  BstNode<Type> * temp1,*temp2;
  temp1=ptr;
  if (ptr!=NULL)
  {
    if (ptr->leftChild!=NULL)
    {
	temp2=Max(ptr->leftChild);
	if (temp1->data<temp2->data) temp1=temp2;
    }
    if (ptr->rightChild!=NULL)
    {
	temp2=Max(ptr->rightChild);
	if (temp1->data<temp2->data) temp1=temp2;
    }
  }
  return temp1;
}


template <class Type> void BST<Type>::OpticBST ( int p[ ], int q[ ], Type a[ ], int n ) {
//给定n个不同的数据 a[1] < a[2] < … < a[n], 以及它们具有的权值p[j], 1 ( j ( n, 另外落在它们之间外部
//结点上的权值分别为 q[i], 0 ( i ( n。本算法计算a[i+1], ……, a[j]的最优二叉搜索树T[i][j]的代价C[i][j],
//T[i][j]的根R[i][j]和权W[i][j]。
   int R[MaxN+1][MaxN+1];
   int C[MaxN+1][MaxN+1];
   int W[MaxN+1][MaxN+1];
   for ( int i=0; i<n; i++) 
   {
	 W[i][i] = q[i];  C[i][i] = R[i][i] = 0;		//初始化
	 W[i][i+1] = W[i][i] + p[i+1] + q[i+1];		//构造只有一个内部结点, 两个外部结点的最优二叉搜索树
	 R[i][i+1] = i+1;					//这些树的根在i+1
	 C[i][i+1] = W[i][i+1];				//这些树的总带权路径长度(代价)
   }
   W[n][n] = q[n];  R[n][n] = C[n][n] = 0;
   for ( int m=2; m<=n; m++ )				//构造具有m个内部结点的最优二叉搜索树
	 for ( i=0; i<=n-m; i++ ) 
	 {
	   int j = i + m;   W[i][j] = W[i][j-1] + p[j] + q[j];  //在前一棵树基础上再加一内部结点和一外部结点
	   int min = C[i+1][j],  u = i+1;			//假定i+1为根, 计算代价
	   for ( int k=i+2; k<=j; k++ )
   		if ( C[i][k-1] + C[k][j] < min ) 
		{ min = C[i][k-1] + C[k][j];  u = k; }
									//轮流以i+2,…,j为根, 选代价最小的送min, 其根为u
		C[i][j] = W[i][j] + min;  R[i][j] = u;
	 }
    Stack < int > nodeStack;
	MakeEmpty();
	nodeStack.Push(0);
	nodeStack.Push(n);
	while (!nodeStack.IsEmpty()) 
	{
		int j=nodeStack.Pop();
		int i=nodeStack.Pop();
		Insert(a[R[i][j]]);
		if ((i+1)<R[i][j])
		{
			nodeStack.Push(i);
			nodeStack.Push(R[i][j]-1);
		};
		if ((R[i][j])<j)
		{
			nodeStack.Push(R[i][j]);
			nodeStack.Push(j);
		};
	}
}
