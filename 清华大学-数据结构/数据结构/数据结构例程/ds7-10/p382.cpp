		const int PageSize = 2;						//一个页块的最大容量
		const int CharNum = 2;						//关键码中的字符数（包括串结束符）
		struct TwoChars 
		{ 
			char str[CharNum]; 			
		};			//每个关键码两个字符
		struct page {								//页块构造
		   int PgDepth;							//区分关键码的二进位位数, 即局部深度
		   TwoChars Names[PageSize];					//关键码数组, 每页最大可容纳的关键码个数
		   int Count;							//在本页块中的实际关键码数目
		};
		typedef page *paddr;						//页块指针
		int DicDepth;							//目录深度, 即最大局部深度, 不超过WordSize
		paddr *Directory;


		int hash (  TwoChars  key ) {
		//使用一个均匀分布的散列函数对关键字key进行计算, 函数返回一个随机化的地址
		   int Sum = 0,  j = 0,  len = 0;
		   for ( int i=0; i<=CharNum; i++ ) 
			 if ( key.str[i] == '\0' || key.str[i] == '\n') break;
			 else len++; 					//计算关键码的字符数
		   if ( len % 2 == 1)				//如果len是奇数, 在关键码尾加一空白, 使len成为偶数
			 { key.str[len+1] = key.str[len];  key.str[len] = ' ';  len++; }	
		   while ( j < len ) { 
			 Sum = ( Sum + 100 * key.str[j] + key.str[j+1] ) % 19937;  j += 2;
		   }   
		   return Sum;
		}

		unsigned int makeAddress ( const TwoChars & key , const int depth ) {			
		//将由关键码key转换成的散列值按指定的低阶二进位数depth再转换成二进位序列， 作为页块地址返回。
		   int hashval = hash ( key );			//将关键码转换成为一个整型的散列值
		   unsigned int retval = 0,  mask = 1;		//累加结果位串置初值及抽取最低位的屏蔽单元
		   for ( int j=1; j<=depth; j++ ) {		//按照指定二进位数循环， 逐位转换
			 retval = retval << 1;				//结果左移一位			 
			 retval = retval | mask;			//将最低位拼入结果			 
		   }
		   retval=retval&hashval;
		   return retval;
		}

		int operator ==(const TwoChars& left,const TwoChars& right)
		{
			return ((left.str[0]==right.str[0])&&(left.str[1]==right.str[1]));
		}

        inline unsigned int Power2(unsigned int n)
		{	
			return 1<<n;
		}

		void InitHash(void)
		{
			DicDepth=0;
			Directory=new paddr[1];
			Directory[0]=new page;
			Directory[0]->Count=0;
			Directory[0]->PgDepth=0;
		}
