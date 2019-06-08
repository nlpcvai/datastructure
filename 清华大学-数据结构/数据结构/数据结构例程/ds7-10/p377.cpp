#ifndef DefaultSize
#define DefaultSize 100
#endif

		template <class Type> class HashTable;
		template <class Type> class ListNode {			//各桶中同义词子表的链结点(表项)定义
		friend class HashTable<Type>;
		private:
		   Type key;		//表项的关键码
		   ListNode *link;		//链指针
		};
 

		template <class Type>
		class HashTable {									//散列表类定义
		typedef ListNode<Type> * ListPtr;					//链表指针
		public:

		   HashTable ( int sz=DefaultSize ) : buckets ( sz ) 
		   { 
			   AllocateHt ( );
			   for (int i=0;i<sz;i++) ht[i]=NULL;				   			   
		   }		//构造函数
		   ~HashTable ( ) { delete [ ] ht; }						//析构函数
		   int Insert ( const Type & x );							//在散列表中插入x
		   int Remove ( const Type & x );						//在散列表中删除x
		   int IsIn ( const Type & x ) { return (  Find (x)) ? 1 : 0; }	//判x在散列表中否
		   int FindPos ( const Type & x ); 					//散列函数: 计算含x表项的初始桶号
	       Type* Find ( const Type & x);
		private:
		   int buckets;							//容量(桶的个数)
		   ListPtr *ht;						//散列表定义
		   void AllocateHt ( ) { ht = new ListPtr[buckets ]; }			//为散列表分配存储空间
		};

		template <class Type> int HashTable<Type>::Insert (const Type & x ) {
		//在ht表中搜索x。若找到则不再插入, 若未找到, 但表已满, 则不再插入, 以上两种情况, 返回0; 若找到
		//位置的标志是Empty或Deleted, 不论表是否已满, x插入, 返回1。
		   if ( Find (x) ) return 0;					//表中已有该项, 不再插入
		   int j=FindPos ( x  );
		   ListPtr p = ht[j];
		   ht[j]=new ListNode<Type>;
		   ht[j]->key=x;
		   ht[j]->link=p;
		   	return 1;
		}

		template <class Type> int HashTable<Type>::Remove ( const Type & x ) {
		//在ht表中删除元素x。若表中找不到x, 或虽然找到x, 但它已经逻辑删除过, 则返回0, 否则在表中删除
		//元素x, 返回1。
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
		//在散列表ht中搜索表项x。函数返回一个指向散列表中某表项的指针; 若表项不存在, 则返回0。
		   int j = FindPos ( x  );				//通过一个散列函数HashFunc( )计算桶号
		   ListPtr p = ht[j];
		   while ( p != NULL )						// p!=NULL时在同义词子表中寻找
			 if ( p->key == x ) return & p->key;			//找到返回
			 else p = p->link;						//否则, 循链向下找
			 return 0;							//整个链都搜索完, 未找到x, 返回0
		}
