#include "iostream.h"

	template <class Type> class AVLTree 
	{					//ƽ��Ķ�����������AVL���ඨ��

	public:
	   struct AVLNode {							//AVL�������ඨ��  
		 Type data;  AVLNode *left, *right;  int balance;
		 AVLNode ( ) : left (NULL), right (NULL), balance (0) { }
		 AVLNode ( Type d, AVLNode *l=NULL, AVLNode *r=NULL ) :
	           data (d), left (l), right (r), balance (0) { }
	   };
	
	protected:
	   Type RefValue;										//��������ı�־
	   AVLNode *root;										//������ָ��
	   int Insert ( AVLNode* &tree, Type x, int & taller );				//����
	   void RotateLeft ( AVLNode *Tree, AVLNode* &NewTree );			//����ת
	   void RotateRight ( AVLNode *Tree, AVLNode* &NewTree );			//�ҵ���ת
	   void LeftBalance ( AVLNode* &Tree, int & taller );				//��ƽ�⻯
	   void RightBalance ( AVLNode* &Tree, int & taller );				//��ƽ�⻯
	   int Depth ( AVLNode *t ) const;							//��߶�
	   void Traverse ( AVLNode *ptr, ostream & out )const ;
	public:
	   AVLTree ( ) : root (NULL) { }								//���캯��������һ�ÿ�AVL��
	   AVLTree ( Type Ref ) : RefValue (Ref), root (NULL) { }				//���캯��������ǿ�AVL��
	   int Insert ( Type x ) { int taller; return Insert ( root, x, taller ); }
	   friend istream& operator >> ( istream& in, AVLTree<Type>& Tree );
	   friend ostream& operator << ( ostream& out, const AVLTree<Type>& Tree );
	   int Depth ( ) const;
	};

		template <class Type> void AVLTree<Type>::RotateLeft ( AVLNode *Tree, AVLNode* &NewTree ) {
		//����������������: ����TreeΪ����AVL��������ת(����), ��ת���¸���NewTree��
		   NewTree = Tree->right;					//�µĸ�ΪC
		   Tree->right = NewTree->left;				//���C������ŮתΪ���A������Ů
		   NewTree->left = Tree;					//���A��ΪC������Ů
		}
		template <class Type> void AVLTree<Type>::RotateRight ( AVLNode *Tree, AVLNode* &NewTree ) {
		//����������������: ����TreeΪ����AVL�����ҵ���ת(����), ��ת���¸���NewTree��
		   NewTree = Tree->left;					//�µĸ���B
		   Tree->left = NewTree->right;				//���B������ŮתΪA������Ů
		   NewTree->right = Tree;					//���A��ΪB������Ů
		}

	 
		template <class Type> void AVLTree<Type>::LeftBalance ( AVLNode * &Tree, int & taller ) {
		   AVLNode *leftsub = Tree->left,  *rightsub;
		   switch ( leftsub->balance ) {							//�ж���������ƽ������
			 case -1 :	Tree->balance = leftsub->balance = 0;		//��ߣ��޸�ƽ������
					RotateRight ( Tree, Tree );	taller = 0;  break;	//���ҵ���ת
			 case 0 :	cout << "LeftBalance error: Tree already balanded.\n";  
				        break;	//û�з�����ƽ��
			 case 1 :	rightsub = leftsub->right;					//�Ҹ�, ȡ��������������
					switch ( rightsub->balance ) {				//�жϸ���������ƽ������
					   case -1: Tree->balance = 1;  
								leftsub->balance = 0;  break;
					   case 0 : Tree->balance = leftsub->balance = 0;  
								break;
					   case 1 : Tree->balance = 0;  
						        leftsub->balance = -1;  
								break;
					}								//������ת�������ƽ������
					rightsub->balance = 0;	
					RotateLeft ( leftsub, Tree->left );				//����ת
					RotateRight ( Tree, Tree );	taller = 0;			//�ҵ���ת
				}
	}

		template <class Type> void AVLTree<Type>::RightBalance ( AVLNode * &Tree, int & taller ) {
		   AVLNode *rightsub = Tree->right,  *leftsub;
		   switch ( rightsub->balance ) {						//�ж���������ƽ������
			 case 1 :	Tree->balance = rightsub->balance = 0;		//�Ҹ�
					RotateLeft ( Tree, Tree );  
					taller = 0;  break;		//������ת
			 case 0 :	cout << "RightBalance error:Tree already balanded.\n";  
				        break;
			 case -1 :	leftsub = rightsub->left;					//���, ȡ��������������
					switch ( leftsub->balance ) {				//�жϸ���������ƽ������
					   case 1 : Tree->balance = -1; 
						        rightsub->balance = 0;  
								break;
					   case 0 : Tree->balance = rightsub->balance = 0;  
						        break;
					   case -1 : Tree->balance = 0;  
						         rightsub->balance = 1;  
								 break;
					}
					leftsub->balance = 0;
					RotateRight ( rightsub, Tree->right );			//�ҵ���ת
					RotateLeft ( Tree, Tree );  taller = 0;			//����ת
	   }
	}

		template <class Type> int AVLTree<Type>::Insert ( AVLNode* &tree, Type x, int &taller ) {
		//����treeΪ����AVL���в�����Ԫ��x, �������ɹ�, taller����1, ���򷵻�0�� 
		   int success;
		   if ( tree == NULL ) {								//ԭΪ����, ��ĳ���Ŀ�����
			 tree = new AVLNode (x);							//�����½�㲢����
			 success = tree != NULL ? 1 : 0;						//�ɹ���־: �洢����ɹ�Ϊ1
			 if ( success ) 
				 taller = 1;
		   }
		   else if ( x < tree->data ) {							//�ж���������뻹�����Ҳ���
			 success = Insert ( tree->left, x, taller );					//���뵽������
			 if ( taller )									//����ɹ� 
			   switch ( tree->balance ) {						//�ж�ƽ������
				 case -1 :	LeftBalance ( tree, taller );  
					        break;		//ԭ�������ߣ���ƽ�⣬����
				 case 0 :	tree->balance = -1;  
					        break;			//ԭ�������ȸߣ�����ƽ������
				 case 1 :	tree->balance = 0;  
					        taller = 0;  
					        break;	//ԭ�������ߣ�����ƽ������
			   }      
		   }
	        else {
			   success = Insert ( tree->right, x, taller );				//���뵽������
			   if ( taller )								//����ɹ�
				 switch ( tree->balance ) {					//�ж�ƽ������
				 case -1 :	tree->balance = 0;
							taller = 0;  
							break;	//ԭ�������ߣ� ����ƽ������
				 case 0 :	tree->balance = 1;  
							break;			//ԭ�������ȸߣ� ����ƽ������
				 case 1 :	
					        RightBalance ( tree, taller );  
							break;		//ԭ�������ߣ���ƽ�⣬����
			   }
				}
		return success;									//���ϲ㴫�Ͳ���ɹ���Ϣ
		}

		template <class Type> istream & operator >> ( istream & in, AVLTree<Type> & Tree ) {
		//����һϵ�е�ֵ, ����AVL����Լ��Tree�е�RefValue����ֹ����ı�ǡ�
		   Type item;									//�����ݴ浥Ԫ
		   cout << "Construct AVL tree :\n";						//��ʾ������AVL��
		   cout << "Input Data (end with " << Tree.RefValue << "): ";		//��ʾ����������(��RefValue����
		   in >> item;									//����
		   while ( item != Tree.RefValue ) {						//�����벻����RefValueʱ
		      Tree.Insert (item);								//���뵽����			 
		      cout << "Input Data (end with " << Tree.RefValue << "): ";		//��ʾ����������(��RefValue����
		      in >> item;									//����
		   }
		   return in;
		}

		template <class Type> ostream & operator << ( ostream & out, const AVLTree<Type> & Tree ) {
		   out << "Inorder traversal of AVL tree.\n";					//��ʾ��AVL�����������
		   Tree.Traverse ( Tree.root, out );						//���������������и���������
		   out << endl;
		   return out;									//�����������
		}

		template <class Type> void AVLTree <Type>::Traverse ( AVLNode *ptr, ostream & out ) const {
		   if ( ptr != NULL ) {								//���ǿ�
		      Traverse ( ptr->left, out );						//�������������
		      out << ptr->data << ' ';							//�����������
		      Traverse ( ptr->right, out );						//�������������			  
		   }
		}
