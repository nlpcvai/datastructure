		#include <iostream.h>
                #include <stdio.h>

		enum Boolean { False, True };
		struct Triple { int row, col;  float value; };					//三元组类的定义
		class Matrix;										//稀疏矩阵类的前视声明

		class MatrixNode {									//矩阵结点类的定义
		friend class Matrix;
		friend istream & operator >> ( istream &, Matrix & );			//矩阵读入
                friend ostream & operator << ( ostream &, Matrix & );
		private:
		   MatrixNode *down, *right;							//列/行链表指针
		   Boolean head;									//结点类型
		   union { Triple triple;  MatrixNode *next; };				//无名联合
		   MatrixNode ( Boolean, Triple* );						//构造函数
		};

		MatrixNode::MatrixNode ( Boolean b, Triple *t ){				//构造函数
		   head = b;									//结点类型
		   if ( b ) { right = next = this; }						//各行/列链表的表头结点
		   else triple = *t;									//头结点链表的表头或非零元素结点
		}
		typedef MatrixNode *MatrixNodePtr;						//一个指针数组

		class Matrix {									//稀疏矩阵的类定义
		friend istream & operator >> ( istream &, Matrix & );
                friend ostream & operator << ( ostream &, Matrix & );
		public:
		   ~Matrix ( );									//析构函数
		private:
		   MatrixNode *headnode; 							//稀疏矩阵的表头
		};


		istream & operator >> ( istream & is, Matrix & matrix )	//读入稀疏矩阵, 建立它的链表表示
		{
		   Triple s;  int p;
		   is >> s.row >> s.col >> s.value; 						//读入矩阵行数、列数和非零元素个数
		   if ( s.row > s.col ) p = s.row;						//确定行/列链表表头结点个数p
		   else p = s.col;									// p = max { s.row, s.col }
		   matrix.headnode = new MatrixNode ( False, &s );				//创建表的表头结点
		   if ( !p ) { matrix.headnode->right = matrix.headnode;  return is; }	//至少一行或一列
		   MatrixNodePtr *H = new MatrixNodePtr [ p ];				//初始化表头指针数组，指向各链表头
		   for ( int i=0; i<p; i++ ) H[i] = new MatrixNode ( True, 0 );		//指向各链表头结点
		   int CurrentRow = 0;
		   MatrixNode *last = H[0];							//last为当前行的最后结点指针
		   for ( i=0; i<s.value; i++ ) {							//输入三元组, s.value给出三元组个数
			 Triple t;
		 is >> t.row >> t.col >> t.value;					//输入三元组
			 if ( t.row > CurrentRow ) {						//行号大于当前行号，闭合当前行
			    last->right = H[CurrentRow];					//在行的方向向表头结点拉链
			    CurrentRow = t.row;  last = H[CurrentRow];			//当前行改变为新的一行
			 }
			 last = last->right = new MatrixNode ( False, &t );			//新结点链入行链表，last跟上
			 H[t.col]->next = H[t.col]->next->down = last;			//链入列链表，next记下该结点地址
		   }
		   last->right = H[CurrentRow];						//闭合最后一行
		   for ( i=0; i<s.col; i++ ) H[i]->next->down = H[i];			//闭合所有列链表
		   for ( i=0; i<p-1; i++ ) H[i]->next = H[i+1];				//所有表头结点链接在一起
		   H[p-1]->next = matrix.headnode;  matrix.headnode->right = H[0];
		   delete [ ] H;
		   return is;
		}


	      /*	if ( first != NULL ) {								//链表不空
		   CircListNode<Type> *second = first->link;			//循环链表的第二个结点
		   first->link = av;    av = second;					//第一个结点链接到av
		   first = NULL;
		}


		if ( av == NULL ) newnode = new CircListNode<Type>;	//可利用空间表为空，动态分配
		else { newnode = av;  av = av->link; }				//不空，从可利用空间表分配
		*/
                MatrixNode *av;

		Matrix::~Matrix ( ) {
		//将所有结点回收到可利用空间表中, 这个表是用right域链接的。av是一个具有MatrixNode*
		//类型的全局变量, 且指向它的前端第一个结点。
		   if ( headnode == NULL ) return;					//空链表, 无法回收
		   MatrixNode *x = headnode->right, *y;
		   headnode->right = av;  av = headnode;				//回收表头结点的循环链表
		   while ( x != headnode ) {						//按行回收各行的循环链表
		      y = x->right;  x->right = av;  av = y;			//回收行 (循环) 链表
		      x = x->next;							//下一行
		   }
		   headnode = NULL;
		}

		ostream & operator << ( ostream & os, Matrix & matrix )
		{
		    MatrixNode *current = matrix.headnode , *temp;
		    cout << "row:  " << current->triple.row << endl;
		    cout << "column: " << current->triple.col << endl;
		    cout << "nonzero: " << current->triple.value << endl;
		    cout << "order in column:" << endl;
		    temp = current = current->right;
		    for (int column = 0 ; column < matrix.headnode->triple.col; column++) {
			cout << "column " << column << " : " ;
			temp = temp->down ;
			while ( temp != current ) {
			    cout << "(" << temp->triple.row << ",";
			    cout << temp->triple.col << ",";
			    cout << temp->triple.value << ") ";
			    temp = temp->down;
			};
			cout << endl;
			temp = current = current->next;
		    }

		    cout << "order in row:" << endl;
		    temp = current = current->right;
		    for (int row = 0; row < matrix.headnode->triple.row; row++) {
			cout << "row " << row << " : " ;
			temp = temp->right ;
			while ( temp != current ) {
			    cout << "(" << temp->triple.row << ",";
			    cout << temp->triple.col << ",";
			    cout << temp->triple.value << ") ";
			    temp = temp->right;
			};
			cout << endl;
			temp = current = current->next;
		    }


		    return os;
		}