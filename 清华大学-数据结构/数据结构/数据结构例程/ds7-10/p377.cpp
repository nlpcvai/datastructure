#ifndef DefaultSize
#define DefaultSize 100
#endif

		template <class Type> class HashTable;
		template <class Type> class ListNode {			//��Ͱ��ͬ����ӱ�������(����)����
		friend class HashTable<Type>;
		private:
		   Type key;		//����Ĺؼ���
		   ListNode *link;		//��ָ��
		};
 

		template <class Type>
		class HashTable {									//ɢ�б��ඨ��
		typedef ListNode<Type> * ListPtr;					//����ָ��
		public:

		   HashTable ( int sz=DefaultSize ) : buckets ( sz ) 
		   { 
			   AllocateHt ( );
			   for (int i=0;i<sz;i++) ht[i]=NULL;				   			   
		   }		//���캯��
		   ~HashTable ( ) { delete [ ] ht; }						//��������
		   int Insert ( const Type & x );							//��ɢ�б��в���x
		   int Remove ( const Type & x );						//��ɢ�б���ɾ��x
		   int IsIn ( const Type & x ) { return (  Find (x)) ? 1 : 0; }	//��x��ɢ�б��з�
		   int FindPos ( const Type & x ); 					//ɢ�к���: ���㺬x����ĳ�ʼͰ��
	       Type* Find ( const Type & x);
		private:
		   int buckets;							//����(Ͱ�ĸ���)
		   ListPtr *ht;						//ɢ�б���
		   void AllocateHt ( ) { ht = new ListPtr[buckets ]; }			//Ϊɢ�б����洢�ռ�
		};

		template <class Type> int HashTable<Type>::Insert (const Type & x ) {
		//��ht��������x�����ҵ����ٲ���, ��δ�ҵ�, ��������, ���ٲ���, �����������, ����0; ���ҵ�
		//λ�õı�־��Empty��Deleted, ���۱��Ƿ�����, x����, ����1��
		   if ( Find (x) ) return 0;					//�������и���, ���ٲ���
		   int j=FindPos ( x  );
		   ListPtr p = ht[j];
		   ht[j]=new ListNode<Type>;
		   ht[j]->key=x;
		   ht[j]->link=p;
		   	return 1;
		}

		template <class Type> int HashTable<Type>::Remove ( const Type & x ) {
		//��ht����ɾ��Ԫ��x���������Ҳ���x, ����Ȼ�ҵ�x, �����Ѿ��߼�ɾ����, �򷵻�0, �����ڱ���ɾ��
		//Ԫ��x, ����1��
		   if ( !Find (x) ) return 0;					
		   int j=FindPos ( x  );
		   ListPtr p= ht[j];

		   if (ht[j]->key==x) 
			   ht[j]=p->link;
		   else
		   {
			   ListPtr q;
			   while (p->key!=x)
			   {
				   q=p;
				   p=p->link;
			   }
			   q->link=p->link;			
		   }
		   delete p;
		   return 1;
		}


		template <class Type> Type *HashTable<Type>::Find ( const Type & x) {
		//��ɢ�б�ht����������x����������һ��ָ��ɢ�б���ĳ�����ָ��; ���������, �򷵻�0��
		   int j = FindPos ( x  );				//ͨ��һ��ɢ�к���HashFunc( )����Ͱ��
		   ListPtr p = ht[j];
		   while ( p != NULL )						// p!=NULLʱ��ͬ����ӱ���Ѱ��
			 if ( p->key == x ) return & p->key;			//�ҵ�����
			 else p = p->link;						//����, ѭ��������
			 return 0;							//��������������, δ�ҵ�x, ����0
		}
