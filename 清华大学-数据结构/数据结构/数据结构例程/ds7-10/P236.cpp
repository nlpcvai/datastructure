#include <iostream.h>
#include "P170.cpp"
#include "Stack.h"
const MaxN=30;
template <class Type> class BST;							//������������ǰ������

template <class Type> class BstNode : public BinTreeNode<Type> {			//���������������
friend class BST;
public:
   BstNode ( const Type d=0, BstNode *L=NULL, BstNode *R =NULL)			//���캯��
      : data (d), leftChild (L), rightChild (R) { };
   ~BstNode ( ) { }
   friend class BST<Type>;
protected:
   Type data;										//������(�����ؼ���)
   BstNode<Type> *leftChild, *rightChild;						//����Ů������Ů����
};

template <class Type> class BST : BinaryTree <Type> {					//�����������ඨ��
public:
	BST ( ) :root(NULL){};								//���캯��
   BST ( Type value ) ;
   BST (const BST<Type> & T) ;//���캯��
   ~BST ( ) { MakeEmpty (  ); }							//��������
   const BST & operator = ( const BST & Value );
   void MakeEmpty( ) { destroy (root);  root=NULL; }
   void PrintTree ( ) const { PrintTree ( root ); }
   int Find ( const Type & x ) const { return (Find ( x, root )!=NULL) ; }	//����Ԫ��
   Type Min() { return Min(root)->data;};										//����С
   Type Max() { return Max(root)->data;};										//�����
   int Insert ( const Type & x ) { return Insert ( x, root ); }				//������Ԫ��
   int Remove (const Type & x ) { return Remove ( x, root ); }				//ɾ����x�Ľ��
   BstNode<Type> *Split ( Type i, BST<Type> &B, Type &x, BST<Type> &C );
   void OpticBST ( int p[ ], int q[ ], Type a[ ], int n );
   friend class BSTIterator ;//�����α���
   
private:											//�ڹؼ���i���ֽ����������
   BstNode<Type> *root;								//�����������ĸ�ָ��
   Type RefValue;										//��������ֹͣ�ı�־, ��������
   BstNode<Type> *lastfound;								//����������Ľ���ָ��
//   void MakeEmpty ( BstNode<Type> * ptr );					//�ÿ�
   int Insert ( const Type & x, BstNode<Type> * & ptr );			//����
   int Remove ( const Type & x, BstNode<Type> * & ptr );			//ɾ��
   void PrintTree ( BstNode<Type> * ptr ) const;					//��ӡ
   BstNode<Type> *Copy (const BstNode<Type> * ptr );				//����
   BstNode<Type> *Find (const Type & x, BstNode<Type> * ptr ) const;	//����
   BstNode<Type> *Min ( BstNode<Type> * ptr ) const;				//����С
   BstNode<Type> *Max ( BstNode<Type> * ptr ) const;				//����� 
};
/*
template <class Type> 
BstNode<Type> * BST<Type>::Find (const Type & x, BstNode<Type> * ptr ) const {
//˽�к���������ptrΪ���Ķ�����������������x�Ľ�㡣���ҵ����������ظý��ĵ�ַ������������
//NULLֵ��
   if ( ptr == NULL ) return NULL;
   else if ( x < ptr->data ) return Find ( x, ptr->leftChild );			//���������м�������
	 else if ( x > ptr->data ) return Find( x, ptr->rightChild );			//���������м�������
	    else return ptr;								//�����ɹ�
}
*/
template <class Type> BstNode<Type> *BST<Type>::Find (const Type & x, BstNode<Type> * ptr ) const {
//˽�к���: ˵�������7.14��ͬ
   if ( ptr != NULL ) {									//���շ���
	 BstNode<Type> * temp = ptr;							//�Ӹ���ʼ����
	 while ( temp != NULL ) {								//==NULL��ʾ����ʧ��
	    if ( temp->data == x ) return temp;					//�����ɹ�
	    if ( temp->data < x ) temp = temp->rightChild;				//���򣬼�������������
	    else temp = temp->leftChild;						//���򣬼�������������
	 }
   }
   return NULL;
};
template <class Type> int BST<Type>::
Insert (const Type & x, BstNode<Type> * & ptr) {
//˽�к���������ptrΪ���Ķ����������в�������ֵΪx�Ľ�㡣���������Ѿ��к�x�Ľ�㣬�򲻲��롣
   if ( ptr == NULL )	{							//�½����ΪҶ������
	 ptr = new BstNode<Type> (x);						//�����½��
	 if ( ptr == NULL ) return 0; else return 1;
   }
   else if ( x < ptr->data ) return Insert ( x, ptr->leftChild );			//С�ڸ��Ĺؼ���, ������������
	 else if ( x > ptr->data ) return Insert ( x, ptr->rightChild );		//����, ������������
   return 1;
							//�����������, ����x�������е�����, ���ٲ���
}



template <class Type>BST<Type>::BST ( Type value ) {
//����һ��Ԫ������, ����һ�ö���������
   Type x;  root = NULL;  RefValue = value;			//�ÿ���
   cin >> x;									//��������
   while ( x != RefValue )
   {						//RefValue��һ�����������־
      Insert ( x, root );  cin >> x;					//���룬����������
   }
}

template <class Type>
void BST<Type>::PrintTree ( BstNode<Type> * ptr ) const					//��ӡ
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
//˽�к���������ptrΪ���Ķ�����������ɾ����x�Ľ�㡣��ɾ���ɹ����¸�ͨ��ptr���ء�
   BstNode<Type> * temp;
   if ( ptr != NULL )
	if ( x < ptr->data ) return Remove ( x, ptr->leftChild );				//����������ִ��ɾ��
	else if ( x > ptr->data )  return Remove ( x, ptr->rightChild );			//����������ִ��ɾ��
	   else if ( ptr->leftChild != NULL && ptr->rightChild != NULL )	{
						// ptrָʾ�ؼ���Ϊx�Ľ�㣬����������Ů
		   temp = Min ( ptr->rightChild );					//��ptr������������Ѱ��С���
		   ptr->data = temp->data;						//�øý�����ݴ�����������
		   return Remove ( ptr->data, ptr->rightChild );				//����������ɾ���ý��
		 }
		 else {				// ptrָʾ�ؼ���Ϊx�Ľ�㣬��ֻ��һ���������Ů
			  temp = ptr;
			  if ( ptr->leftChild == NULL ) ptr = ptr->rightChild;		//ֻ������Ů
			  else if ( ptr->rightChild == NULL ) ptr = ptr->leftChild;	//ֻ������Ů
		      delete temp;
		      return 1;
		    }
   else return 0;
}
template <class Type> class InorderIterator	{	    			//�����α��ඨ��
public:
   InorderIterator ( BST<Type> & Tree ) : ref (Tree) { Init ( ); }
   int Init ( );									//��ʼ��
   int operator ! ( );								//��
   Type operator ( ) ( );								//ȡջ��Ԫ��ֵ
   int operator ++ ( );								// BST��ǰ����б���
private:
   BST<Type> & ref;								//��������������
   Stack < BstNode<Type> * > itrStack;					//��������ջ
};

template <class Type> int InorderIterator<Type>::Init ( ) {			//��ʼ������
   itrStack.MakeEmpty ( );								//�õ�������ջΪ��
   if ( ref.root != NULL ) itrStack.Push ( ref.root );				//�������������������ָ���ջ
   return ! itrStack.IsEmpty ( );							//��ջ���򷵻�0�����򷵻�1
}

template <class Type> int InorderIterator<Type>::operator ! ( ) {
   return ! itrStack.IsEmpty ( );							//��ջ���򷵻�0�����򷵻�1
}

template <class Type> Type InorderIterator<Type>::operator ( ) ( ) {	//���ص�ǰ��������ֵ
   Node<Type> * current = itrStack.GetTop ( );				//ȡջ�����Ϊ��ǰ���
   return current->data;								//���ص�ǰ���Ĺؼ���
}

template <class Type> int InorderIterator<Type>::operator ++ ( ) {
//����������������ǰ�����н�ջ����������ǰ����������1, ���򷵻�0��
   BstNode<Type> * current = itrStack.GetTop ( );				//ȡ����ջ���ϵĽ��
   BstNode<Type> * next = current->leftChild;				//����Ů
   if ( next != NULL ) { itrStack.Push ( next );  return 1; }			//����Ů�ǿ�, ��ջ(������������)
   while ( ! itrStack.IsEmpty ( ) ) {						//����, ��ջ�ǿ�
      current = itrStack.Pop ( );   next = current->rightChild;		//��ջ, ȡ������Ů
      if ( next != NULL ) { itrStack.Push ( next );  return 1; }		//����Ů�ǿ�, ��ջ
   }
   return 0;
}

/*template <class Type>
BST<Type>::BST (const BST<Type> & T) : root (NULL) {
//���캯�������ݲ�����ʼ����T
   InorderIterator<Type> itr ( Type );						//���������α������
   for ( itr.init ( ); ! itr; itr++) Insert ( itr ( ) );				//��ǰ��˳�����
}*/

template <class Type>
BstNode<Type> * BST<Type>::Min ( BstNode<Type> * ptr ) const				//����С
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
BstNode<Type> * BST<Type>::Max ( BstNode<Type> * ptr ) const				//����С
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
//����n����ͬ������ a[1] < a[2] < �� < a[n], �Լ����Ǿ��е�Ȩֵp[j], 1 ( j ( n, ������������֮���ⲿ
//����ϵ�Ȩֵ�ֱ�Ϊ q[i], 0 ( i ( n�����㷨����a[i+1], ����, a[j]�����Ŷ���������T[i][j]�Ĵ���C[i][j],
//T[i][j]�ĸ�R[i][j]��ȨW[i][j]��
   int R[MaxN+1][MaxN+1];
   int C[MaxN+1][MaxN+1];
   int W[MaxN+1][MaxN+1];
   for ( int i=0; i<n; i++) 
   {
	 W[i][i] = q[i];  C[i][i] = R[i][i] = 0;		//��ʼ��
	 W[i][i+1] = W[i][i] + p[i+1] + q[i+1];		//����ֻ��һ���ڲ����, �����ⲿ�������Ŷ���������
	 R[i][i+1] = i+1;					//��Щ���ĸ���i+1
	 C[i][i+1] = W[i][i+1];				//��Щ�����ܴ�Ȩ·������(����)
   }
   W[n][n] = q[n];  R[n][n] = C[n][n] = 0;
   for ( int m=2; m<=n; m++ )				//�������m���ڲ��������Ŷ���������
	 for ( i=0; i<=n-m; i++ ) 
	 {
	   int j = i + m;   W[i][j] = W[i][j-1] + p[j] + q[j];  //��ǰһ�����������ټ�һ�ڲ�����һ�ⲿ���
	   int min = C[i+1][j],  u = i+1;			//�ٶ�i+1Ϊ��, �������
	   for ( int k=i+2; k<=j; k++ )
   		if ( C[i][k-1] + C[k][j] < min ) 
		{ min = C[i][k-1] + C[k][j];  u = k; }
									//������i+2,��,jΪ��, ѡ������С����min, ���Ϊu
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
