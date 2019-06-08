#include "p382.cpp"
		int PageFind ( const TwoChars & key, const paddr PageNumber )
		//在由指针PageNumber所指的页块中搜索关键码key, 如果找到则返回1, 否则返回0。
		//因为在页块内的搜索方法一般为顺序搜索, 算法不再特别给出, 可参看程序9.1。
		{
			for (int i=0;i<PageNumber->Count;i++)
			{
				if (key==PageNumber->Names[i]) return 1;
			}
			return 0;
		};
		paddr Find ( const TwoChars & key ) {
		//在文件中搜索具有关键字key的记录。若找到, 则返回该记录所在页块的地址; 若没有找到, 则返回 0。
		   unsigned int id = makeAddress ( key, DicDepth );			//按key与DicDepth计算目录地址
		   paddr FoundPage;
		   FoundPage= Directory[id];					//在目录中找到相应页块地址
		   if ( PageFind ( key, FoundPage ) ) return FoundPage;		//在该页块中搜索, 找到返回页块地址
		   else return 0;
		}



		void DirDouble ( ) {							//目录成倍扩充的算法
		   unsigned int CurrentSize = Power2(DicDepth);
		   
		   paddr *TmpDir = Directory;				//创建临时目录		   
		   Directory = new paddr[2*CurrentSize];			//创建新目录
		   for ( int i=0; i<CurrentSize; i++ )					//从临时目录向新目录传送页块指针
			 { Directory[i] = TmpDir[i];  Directory[CurrentSize+i] = TmpDir[i]; } 
		   DicDepth++;
		   delete [] TmpDir;
		}

		int buddy ( const unsigned int index ) {
		//根据一个页块的二进制地址index计算该页块的伙伴的二进制地址, 前端的二进位是互补的。
		   if (DicDepth == 0 ) return 0;						//目录深度为0, 没有伙伴
		   if ( Directory[index]->PgDepth < DicDepth ) 			//该页块的局部深度小于目录深度
			 return -1;								//没有伙伴
		   unsigned int mask = 1;						//工作变量
		   mask <<= DicDepth - 1;						//左移DicDepth - 1位, 将1移到最高位 
		   unsigned int buddyAddress = index ^ mask;			//做异或操作, 求伙伴
		   return buddyAddress;
		}

		void ReDisTribute ( paddr PageNumber, paddr NewPage )
			//将老页块中所有关键码重新分布
		{
			int i=0;
			int CurrentSize=PageNumber->PgDepth;
			NewPage->Count=0;
			while (i<PageNumber->Count)
			{
				TwoChars key=PageNumber->Names[i];
				int NowPage=makeAddress ( key, CurrentSize );
				if (Directory[NowPage]==NewPage) 
				{
					NewPage->Names[NewPage->Count]=key;
					NewPage->Count++;

					PageNumber->Count--;
					PageNumber->Names[i]=PageNumber->Names[PageNumber->Count];
				}
				else
					i++;
			}
		}


		void Split ( const TwoChars key, paddr PageNumber ) {		//分裂页块
		   int CurrentSize = DicDepth;						//记下老的目录大小
		   if ( PageNumber->PgDepth == DicDepth )			//页块深度等于目录深度时
			 DirDouble( );							//页块分裂将导致目录成倍扩充
		   paddr NewPage = new page;						//为伙伴页块分配存储空间
		   PageNumber->PgDepth ++;						//老页块的局部深度加1
		   unsigned int id = makeAddress ( key, CurrentSize );		//按key与老DicDepth计算二进制地址
		   unsigned int bd = buddy ( id );					//找伙伴页块的二进制地址	
		   Directory [ bd ] = NewPage;						//建立伙伴页块的目录项		   
		   NewPage->PgDepth = PageNumber->PgDepth;			//伙伴的局部深度等于老页块的局部深度
		   ReDisTribute ( PageNumber, NewPage );				//将老页块中所有关键码重新分布
		} 

		int Add (const TwoChars & key ) ;

	   
		void Insert ( paddr PageNumber, const TwoChars & key ) {
		//将新关键码key插入到由PageNumber指定的页块中。
		   if ( PageNumber->Count != PageSize ) {				//若本页块中关键码个数未满
			 PageNumber->Names [ PageNumber->Count ] = key;
			 PageNumber->Count++;						//直接插入
		   }
		   else {									//否则
			 Split ( key, PageNumber );						//将页块一分为二
			 Add ( key);								//插入
		   }
		}


		int Add (const TwoChars & key ) {
		//将一个新关键码key插入到目录所指定的文件中。
		   paddr foundPage = Find ( key );					//按key在文件中搜索
		   if ( foundPage ) return 0;						//若找到, 则不插入, 返回主程序
		   Insert ( Directory[makeAddress ( key, DicDepth )], key );						//将关键码key插入foundPage页块
		   return 1;
		}
