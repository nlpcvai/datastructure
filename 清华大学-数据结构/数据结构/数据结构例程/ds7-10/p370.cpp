#ifndef DefaultSize
#define DefaultSize 100
#endif
		template <class Type>
		class HashTable {									//散列表类定义
		public:
		   enum KindOfEntry { Active, Empty, Deleted };				//表项分类 (活动 / 空 / 删)
		   HashTable ( int sz=DefaultSize ) : TableSize ( sz ) { AllocateHt ( );  CurrentSize = 0; }		//构造函数
		   ~HashTable ( ) { delete [ ] ht; }						//析构函数
		   const HashTable & operator = ( const HashTable & ht2 );		//重载函数：表赋值
		   int Find ( const Type & x );							//在散列表中搜索x
		   int Insert ( const Type & x );							//在散列表中插入x
		   int Remove ( const Type & x );						//在散列表中删除x
		   int IsIn ( const Type & x ) { return (  Find (x)  >= 0 ) ? 1 : 0; }	//判x在散列表中否
		   void MakeEmpty ( );								//置散列表为空
		   int FindPos ( const Type & x ); 					//散列函数: 计算含x表项的初始桶号
		private:
		   struct HashEntry {								//表项定义
		      Type Element;								//表项的数据, 即表项的关键码
		      KindOfEntry info;								//三种状态: Active, Empty, Deleted
		      int operator== ( HashEntry & );			//重载函数：表项判等运算
		      int operator!= ( HashEntry & );				//重载函数：表项判不等运算
		      HashEntry ( ) : info (Empty ) { }						//表项构造函数, 置空
		      HashEntry (const Type & E, KindOfEntry i = Empty ) : Element (E), info (i) { }
		   };
		   enum { DefualtSize = 11 };
		   HashEntry *ht;									//散列表存储数组
		   int CurrentSize, TableSize;							//当前桶数及最大桶数
		   void AllocateHt ( ) { ht = new HashEntry[TableSize ]; }			//为散列表分配存储空间
		};
		template <class Type> int HashTable<Type>::Find ( const Type & x ) {
		//使用线性探查法在散列表ht (每个桶容纳一个表项)中搜索x。如果x在表中存在, 则函数返回x所在
		//位置j, 即ht[j]=x。如果x不在表中, 则返回 -j。
		   int i = FindPos ( x ),  j = i; 						//i是计算出来的散列地址, j是下一空桶
		   while ( ht[j].info != Empty && ht[j].Element != x ) {		//ht[j]不空, 且不等于x，冲突
			 j = ( j + 1 ) % TableSize;						//当做循环表处理, 找下一个空桶 
			 if ( j == i ) return -TableSize-1;					//转一圈回到开始点, 表已满, 失败
		   }
		   if ( ht[j].info == Active ) return j;					//找到满足要求的表项, 返回桶号j
		   else return -j-1;									//失败
		}
//	在利用散列表进行各种处理之前，必须首先将散列表中原有的内容清掉，这时我们可以将表中所有表项的info域置为Empty即可。因为散列表存放的是表项集合，不应有重复的关键码，所以在插入新表项时，如果发现表中已经有关键码相同的表项，则不再插入。	特别要注意的是，在闭散列的情形下不能随便物理删除表中已有的表项。因为若删除表项会影响其它表项的搜索。如在图10.26所示的例子中，若把关键码为Broad的表项真正删除，把它所在位置的info域置为Empty，那么以后在搜索关键码为Blum和Alton的表项时就查不下去，从而会错误地判断表中没有关键码为Blum和Alton的表项。所以若想删除一个表项时，只能给它做一个删除标记deleted，进行逻辑删除。但这样做的副作用是：在执行多次删除后，表面上看起来散列表很满，实际上有许多位置没有利用。因此，当散列表经常变动时，最好不用闭散列方法处理溢出，可改用开散列方法来处理溢出。
//	下面给出散列表其它一些操作的实现。
		template <class Type> void HashTable<Type>::MakeEmpty ( ) {		//清除散列表
		   for ( int i=0; i<TableSize; i++) ht[i].info = Empty;
		   CurrentSize = 0;
		}

		template <class Type> const HashTable<Type> & HashTable<Type>::operator= ( const HashTable<Type> &ht2 ) {
		//重载函数：复制一个散列表ht2
		   if ( this != &ht2 ) {
			 delete [ ] ht;  TableSize = ht2.TableSize;  AllocateHt ( );		//重新分配目标散列表存储空间
			 for ( int i=0; i<TableSize; i++ ) ht[i] = ht2.ht[i];			//从源散列表向目标散列表传送
			 CurrentSize = ht2.CurrentSize;						//传送当前表项个数
		   }
		   return *this;									//返回目标散列表结构指针
		}
      
		template <class Type> int HashTable<Type>::Insert (const Type & x ) {
		//在ht表中搜索x。若找到则不再插入, 若未找到, 但表已满, 则不再插入, 以上两种情况, 返回0; 若找到
		//位置的标志是Empty或Deleted, 不论表是否已满, x插入, 返回1。
		   int i = Find (x);
		   if ( i >= 0 ) return 0;					//表中已有该项, 不再插入
		   i++;
		     if ( i != -TableSize && ht[-i].info != Active ) {			//否则若表项为空插入, i为负数
			 ht[-i].Element = x;  ht[-i].info = Active;  CurrentSize++;		//插入
			 return 1;									//返回插入成功标志1
		   }
		   else return 0; 									//表满不插入, 返回不成功标志
		}

		template <class Type> int HashTable<Type>::Remove ( const Type & x ) {
		//在ht表中删除元素x。若表中找不到x, 或虽然找到x, 但它已经逻辑删除过, 则返回0, 否则在表中删除
		//元素x, 返回1。
			int i = Find (x);
		   if ( i >= 0 ) 
		   {						//找到要删元素, 且是活动元素
			 ht[i].info = Deleted;  CurrentSize--;					//做逻辑删除标志, 并不真正物理删除
			 return 1;									//删除操作完成, 返回成功标志
		   }
		   else return 0;									//表中无被删表项, 返回不成功标志
		}
