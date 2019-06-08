		int IsPrime ( int N ) {					//测试N是否质数
		   for ( int i=3; i*i<=N; i+=2 )				//若N能分解为两个整数的乘积, 其中一个一定 
			 if ( N % i == 0 ) return 0;			//N能整除i, N不是质数
		   return 1;							//N是质数
		}

		int NextPrime ( int N ) {					//求下一个>N的质数，设N >= 5
		   if ( N % 2 == 0 ) N++;				//偶数不是质数
		   for ( ; !IsPrime (N); N+=2 );				//寻找质数
		   return N;
		}

		template <class Type> class HashTable {				//散列表类的定义
		public:
		   enum KindOfEntry { Active, Empty, Deleted };			//表项分类 (活动 / 空 / 删)
		   int Find ( const Type & x );				//在散列表中搜索x
		   int IsEmpty ( ) { return !CurrentSize ? 1 : 0; }			//判散列表空否，空则返回1 
		   int IsFull ( ) { return CurrentSize == TableSize ? 1 : 0; }	//判散列表满否，满则返回1
		   int Insert ( const Type & x );
		   int Remove ( const Type & x );
		   int IsIn ( const Type & x );
		   int WasFound ( ) const { return LastFindOK;	}		//判最近一次搜索是否成功
		   //其它共有函数与定义10.6声明线性探查散列表类相同
		   HashTable ( int sz=DefaultSize ) : TableSize ( sz ) { AllocateHt ( );  CurrentSize = 0; }		//构造函数
		   ~HashTable ( ) { delete [ ] ht; }						//析构函数
		   const HashTable & operator = ( const HashTable & ht2 );		//重载函数：表赋值
		   int FindPos ( const Type & x ); 					//散列函数: 计算含x表项的初始桶号
		   void MakeEmpty ( );								//置散列表为空

		private:
		   struct HashEntry {							//散列表的表项定义
		      Type Element;							//表项的数据, 即表项的关键码
		      KindOfEntry info;							//三种状态: Active, Empty, Deleted
		      HashEntry ( ) : info (Empty ) { }					//表项构造函数
		      HashEntry ( const Type &E, KindOfEntry i = Empty ) : Element (E), info (i) { };
		   };
		   //enum { DefualtSize = 11; };
		   HashEntry *ht; 								//散列表存储数组
		   int TableSize;								//数组长度，要求是满足4k+3的质数，k是整数
		   int CurrentSize;								//已占据散列地址数目
		   int LastFindOK;							//若最近一次搜索成功成功, 则返回1
		   void AllocateHt ( ) { ht = new HashEntry[TableSize ]; }	//分配散列表存储空间的函数
		};
		template <class Type> int HashTable<Type>::Find ( const Type & x ) {
		//共有函数： 找下一散列位置的函数
		   int i = 0,  odd = 0 ;								// i为探查次数，odd是控制加减标志
		   int CurrentPos = FindPos ( x );						//利用散列函数计算x的散列地址
		   while ( ht[CurrentPos].info != Empty && ht[CurrentPos].Element != x ) {	//搜索是否要求表项
			 if ( !odd ) {									// odd == 0为(H0 + i2)%TableSize情形
			   CurrentPos += 2*++i - 1;   odd = 1;				//求“下一个”桶
		 	   while ( CurrentPos >= TableSize ) CurrentPos -= TableSize;	//实现取模
			 }
			 else {										// odd == 1为(H0 - i2)%TableSize情形
			   CurrentPos -= 2*i-1;  odd = 0;					//求“下一个”桶
			   while ( CurrentPos < 0 ) CurrentPos += TableSize; 		//实现取模
			 }
		   }
		   LastFindOK = ht[CurrentPos].info == Active;				//记下最后是否搜索成功信息
		   return CurrentPos;								//返回桶号
		};

		template <class Type> int HashTable<Type>::Insert ( const Type & x ) {
		//将x插入到散列表中, 若x在表中已存在, 则返回0, 否则返回1。
		   int CurrentPos = Find (x);
		   if (LastFindOK ) return 0;						//该项在表中已经存在, 不再加入
		   ht[CurrentPos] = HashEntry ( x, Active );				//插入x
		   if ( ++CurrentSize < TableSize/2) return 1;				//当前已有项数加1, 不超过表长的一半返回
		   HashEntry *Oldht = ht;						//分裂空间处理: 保存原来的散列表
		   int OldTableSize = TableSize;
		   CurrentSize = 0;
		   TableSize = NextPrime ( 2 * OldTableSize );			//原表大小的2倍，取质数
		   AllocateHt ( );								//建立新的二倍大小的空表
		   for (int i=0; i<OldTableSize; i++)					//原来的元素重新散列到新表中
		      if ( Oldht[i].info == Active ) Insert ( Oldht[i].Element );	//递归调用
		   delete [ ] Oldht;
		   return 1;
		}

		template <class Type> int HashTable<Type>::IsIn ( const Type & x ) {
		//判断x是否在散列表中。若在表中, 则返回1, 否则返回0。
		   int CurrentPos = Find ( x );
		   return LastFindOK;
		}

		template <class Type> int HashTable<Type>::Remove ( const Type & x ) {
		//将x从散列表中删除。若删除成功, 则返回1, 否则返回0。
		   int CurrentPos = Find (x);
		   if (!LastFindOK ) return 0;						//该项在散列表中没有
		   ht[CurrentPos].info = Deleted;  return 1;				//作删除标记, 删除成功
		}



		//以下来自线性探查法
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
      
