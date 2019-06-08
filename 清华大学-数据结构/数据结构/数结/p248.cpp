#include "iostream.h"

	template <class Type> class AVLTree 
	{					//平衡的二叉搜索树（AVL）类定义

	public:
	   struct AVLNode {							//AVL树结点的类定义  
		 Type data;  AVLNode *left, *right;  int balance;
		 AVLNode ( ) : left (NULL), right (NULL), balance (0) { }
		 AVLNode ( Type d, AVLNode *l=NULL, AVLNode *r=NULL ) :
	           data (d), left (l), right (r), balance (0) { }
	   };
	
	protected:
	   Type RefValue;										//插入结束的标志
	   AVLNode *root;										//根结点的指针
	   int Insert ( AVLNode* &tree, Type x, int & taller );				//插入
	   void RotateLeft ( AVLNode *Tree, AVLNode* &NewTree );			//左单旋转
	   void RotateRight ( AVLNode *Tree, AVLNode* &NewTree );			//右单旋转
	   void LeftBalance ( AVLNode* &Tree, int & taller );				//左平衡化
	   void RightBalance ( AVLNode* &Tree, int & taller );				//右平衡化
	   int Depth ( AVLNode *t ) const;							//求高度
	   void Traverse ( AVLNode *ptr, ostream & out )const ;
	public:
	   AVLTree ( ) : root (NULL) { }								//构造函数：构造一棵空AVL树
	   AVLTree ( Type Ref ) : RefValue (Ref), root (NULL) { }				//构造函数：构造非空AVL树
	   int Insert ( Type x ) { int taller; return Insert ( root, x, taller ); }
	   friend istream& operator >> ( istream& in, AVLTree<Type>& Tree );
	   friend ostream& operator << ( ostream& out, const AVLTree<Type>& Tree );
	   int Depth ( ) const;
	};

		template <class Type> void AVLTree<Type>::RotateLeft ( AVLNode *Tree, AVLNode* &NewTree ) {
		//右子树比左子树高: 对以Tree为根的AVL树做左单旋转(左折), 旋转后新根在NewTree。
		   NewTree = Tree->right;					//新的根为C
		   Tree->right = NewTree->left;				//结点C的左子女转为结点A的右子女
		   NewTree->left = Tree;					//结点A成为C的左子女
		}
		template <class Type> void AVLTree<Type>::RotateRight ( AVLNode *Tree, AVLNode* &NewTree ) {
		//左子树比右子树高: 对以Tree为根的AVL树做右单旋转(右折), 旋转后新根在NewTree。
		   NewTree = Tree->left;					//新的根在B
		   Tree->left = NewTree->right;				//结点B的右子女转为A的左子女
		   NewTree->right = Tree;					//结点A成为B的右子女
		}

	 
		template <class Type> void AVLTree<Type>::LeftBalance ( AVLNode * &Tree, int & taller ) {
		   AVLNode *leftsub = Tree->left,  *rightsub;
		   switch ( leftsub->balance ) {							//判断左子树的平衡因子
			 case -1 :	Tree->balance = leftsub->balance = 0;		//左高，修改平衡因子
					RotateRight ( Tree, Tree );	taller = 0;  break;	//做右单旋转
			 case 0 :	cout << "LeftBalance error: Tree already balanded.\n";  
				        break;	//没有发生不平衡
			 case 1 :	rightsub = leftsub->right;					//右高, 取左子树的右子树
					switch ( rightsub->balance ) {				//判断该右子树的平衡因子
					   case -1: Tree->balance = 1;  
								leftsub->balance = 0;  break;
					   case 0 : Tree->balance = leftsub->balance = 0;  
								break;
					   case 1 : Tree->balance = 0;  
						        leftsub->balance = -1;  
								break;
					}								//调整旋转后各结点的平衡因子
					rightsub->balance = 0;	
					RotateLeft ( leftsub, Tree->left );				//左单旋转
					RotateRight ( Tree, Tree );	taller = 0;			//右单旋转
				}
	}

		template <class Type> void AVLTree<Type>::RightBalance ( AVLNode * &Tree, int & taller ) {
		   AVLNode *rightsub = Tree->right,  *leftsub;
		   switch ( rightsub->balance ) {						//判断右子树的平衡因子
			 case 1 :	Tree->balance = rightsub->balance = 0;		//右高
					RotateLeft ( Tree, Tree );  
					taller = 0;  break;		//做左单旋转
			 case 0 :	cout << "RightBalance error:Tree already balanded.\n";  
				        break;
			 case -1 :	leftsub = rightsub->left;					//左高, 取右子树的左子树
					switch ( leftsub->balance ) {				//判断该左子树的平衡因子
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
					RotateRight ( rightsub, Tree->right );			//右单旋转
					RotateLeft ( Tree, Tree );  taller = 0;			//左单旋转
	   }
	}

		template <class Type> int AVLTree<Type>::Insert ( AVLNode* &tree, Type x, int &taller ) {
		//在以tree为根的AVL树中插入新元素x, 如果插入成功, taller返回1, 否则返回0。 
		   int success;
		   if ( tree == NULL ) {								//原为空树, 或某结点的空链域
			 tree = new AVLNode (x);							//创建新结点并插入
			 success = tree != NULL ? 1 : 0;						//成功标志: 存储分配成功为1
			 if ( success ) 
				 taller = 1;
		   }
		   else if ( x < tree->data ) {							//判断是向左插入还是向右插入
			 success = Insert ( tree->left, x, taller );					//插入到左子树
			 if ( taller )									//插入成功 
			   switch ( tree->balance ) {						//判断平衡因子
				 case -1 :	LeftBalance ( tree, taller );  
					        break;		//原左子树高，不平衡，调整
				 case 0 :	tree->balance = -1;  
					        break;			//原两子树等高，仅改平衡因子
				 case 1 :	tree->balance = 0;  
					        taller = 0;  
					        break;	//原右子树高，仅改平衡因子
			   }      
		   }
	        else {
			   success = Insert ( tree->right, x, taller );				//插入到右子树
			   if ( taller )								//插入成功
				 switch ( tree->balance ) {					//判断平衡因子
				 case -1 :	tree->balance = 0;
							taller = 0;  
							break;	//原左子树高， 仅改平衡因子
				 case 0 :	tree->balance = 1;  
							break;			//原两子树等高， 仅改平衡因子
				 case 1 :	
					        RightBalance ( tree, taller );  
							break;		//原右子树高，不平衡，调整
			   }
				}
		return success;									//向上层传送插入成功信息
		}

		template <class Type> istream & operator >> ( istream & in, AVLTree<Type> & Tree ) {
		//输入一系列的值, 建立AVL树。约定Tree中的RefValue是终止输入的标记。
		   Type item;									//输入暂存单元
		   cout << "Construct AVL tree :\n";						//提示：构造AVL树
		   cout << "Input Data (end with " << Tree.RefValue << "): ";		//提示：输入数据(以RefValue结束
		   in >> item;									//输入
		   while ( item != Tree.RefValue ) {						//当输入不等于RefValue时
		      Tree.Insert (item);								//插入到树中			 
		      cout << "Input Data (end with " << Tree.RefValue << "): ";		//提示：输入数据(以RefValue结束
		      in >> item;									//输入
		   }
		   return in;
		}

		template <class Type> ostream & operator << ( ostream & out, const AVLTree<Type> & Tree ) {
		   out << "Inorder traversal of AVL tree.\n";					//提示：AVL树的中序遍历
		   Tree.Traverse ( Tree.root, out );						//以中序次序输出树中各结点的数据
		   out << endl;
		   return out;									//返回输出对象
		}

		template <class Type> void AVLTree <Type>::Traverse ( AVLNode *ptr, ostream & out ) const {
		   if ( ptr != NULL ) {								//树非空
		      Traverse ( ptr->left, out );						//中序遍历左子树
		      out << ptr->data << ' ';							//输出根的数据
		      Traverse ( ptr->right, out );						//中序遍历右子树			  
		   }
		}
