		#include <iostream.h>
                #include <stdio.h>

		enum Boolean { False, True };
		struct Triple { int row, col;  float value; };					//��Ԫ����Ķ���
		class Matrix;										//ϡ��������ǰ������

		class MatrixNode {									//��������Ķ���
		friend class Matrix;
		friend istream & operator >> ( istream &, Matrix & );			//�������
                friend ostream & operator << ( ostream &, Matrix & );
		private:
		   MatrixNode *down, *right;							//��/������ָ��
		   Boolean head;									//�������
		   union { Triple triple;  MatrixNode *next; };				//��������
		   MatrixNode ( Boolean, Triple* );						//���캯��
		};

		MatrixNode::MatrixNode ( Boolean b, Triple *t ){				//���캯��
		   head = b;									//�������
		   if ( b ) { right = next = this; }						//����/������ı�ͷ���
		   else triple = *t;									//ͷ�������ı�ͷ�����Ԫ�ؽ��
		}
		typedef MatrixNode *MatrixNodePtr;						//һ��ָ������

		class Matrix {									//ϡ�������ඨ��
		friend istream & operator >> ( istream &, Matrix & );
                friend ostream & operator << ( ostream &, Matrix & );
		public:
		   ~Matrix ( );									//��������
		private:
		   MatrixNode *headnode; 							//ϡ�����ı�ͷ
		};


		istream & operator >> ( istream & is, Matrix & matrix )	//����ϡ�����, �������������ʾ
		{
		   Triple s;  int p;
		   is >> s.row >> s.col >> s.value; 						//������������������ͷ���Ԫ�ظ���
		   if ( s.row > s.col ) p = s.row;						//ȷ����/�������ͷ������p
		   else p = s.col;									// p = max { s.row, s.col }
		   matrix.headnode = new MatrixNode ( False, &s );				//������ı�ͷ���
		   if ( !p ) { matrix.headnode->right = matrix.headnode;  return is; }	//����һ�л�һ��
		   MatrixNodePtr *H = new MatrixNodePtr [ p ];				//��ʼ����ͷָ�����飬ָ�������ͷ
		   for ( int i=0; i<p; i++ ) H[i] = new MatrixNode ( True, 0 );		//ָ�������ͷ���
		   int CurrentRow = 0;
		   MatrixNode *last = H[0];							//lastΪ��ǰ�е������ָ��
		   for ( i=0; i<s.value; i++ ) {							//������Ԫ��, s.value������Ԫ�����
			 Triple t;
		 is >> t.row >> t.col >> t.value;					//������Ԫ��
			 if ( t.row > CurrentRow ) {						//�кŴ��ڵ�ǰ�кţ��պϵ�ǰ��
			    last->right = H[CurrentRow];					//���еķ������ͷ�������
			    CurrentRow = t.row;  last = H[CurrentRow];			//��ǰ�иı�Ϊ�µ�һ��
			 }
			 last = last->right = new MatrixNode ( False, &t );			//�½������������last����
			 H[t.col]->next = H[t.col]->next->down = last;			//����������next���¸ý���ַ
		   }
		   last->right = H[CurrentRow];						//�պ����һ��
		   for ( i=0; i<s.col; i++ ) H[i]->next->down = H[i];			//�պ�����������
		   for ( i=0; i<p-1; i++ ) H[i]->next = H[i+1];				//���б�ͷ���������һ��
		   H[p-1]->next = matrix.headnode;  matrix.headnode->right = H[0];
		   delete [ ] H;
		   return is;
		}


	      /*	if ( first != NULL ) {								//������
		   CircListNode<Type> *second = first->link;			//ѭ������ĵڶ������
		   first->link = av;    av = second;					//��һ��������ӵ�av
		   first = NULL;
		}


		if ( av == NULL ) newnode = new CircListNode<Type>;	//�����ÿռ��Ϊ�գ���̬����
		else { newnode = av;  av = av->link; }				//���գ��ӿ����ÿռ�����
		*/
                MatrixNode *av;

		Matrix::~Matrix ( ) {
		//�����н����յ������ÿռ����, ���������right�����ӵġ�av��һ������MatrixNode*
		//���͵�ȫ�ֱ���, ��ָ������ǰ�˵�һ����㡣
		   if ( headnode == NULL ) return;					//������, �޷�����
		   MatrixNode *x = headnode->right, *y;
		   headnode->right = av;  av = headnode;				//���ձ�ͷ����ѭ������
		   while ( x != headnode ) {						//���л��ո��е�ѭ������
		      y = x->right;  x->right = av;  av = y;			//������ (ѭ��) ����
		      x = x->next;							//��һ��
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