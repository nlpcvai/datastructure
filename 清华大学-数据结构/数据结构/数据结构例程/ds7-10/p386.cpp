#include "P384.cpp"

			void PageRemove ( const TwoChars & key, const paddr p )
			//从p所指的页块中删去关键码key。这是顺序表的删除算法, 可参看第2章。
			{
				for (int i=0;i<p->Count;i++)
					if (p->Names[i]==key)
					{
						p->Count--;
						p->Names[i]=p->Names[p->Count];
						return;
					}				
			}
     	   void combine ( unsigned int index ) {		
		   if ( DicDepth == 0 ) return;					   
		   int buddyid= buddy (index);					//伙伴页块的二进制 地址	
		   paddr p = Directory[index];						//index页块和伙伴页块指针
		   paddr s = Directory[buddyid];
		   if ( (buddyid>=0) && ((p->Count + s->Count) <= PageSize )) {
				//看该页块与其伙伴的总关键码个数是否超出一页限制, 未超出, 合并页块
			 			 
			 for ( int i=0; i<s->Count; i++ ) {				//将伙伴中内容全部移到index页块			   
			   p->Names[p->Count] = s->Names[i];
			   p->Count++; 
			 }
			 delete s;   p->PgDepth--;					//释放伙伴页块, index页块深度减1
			 Directory[buddyid] = p;				

			 unsigned int DirSize = Power2(DicDepth);				//计算目录项数
			 unsigned int NewDirSize = DirSize / 2;					//如果紧缩,新的目录项数
			 for ( i=0; i<NewDirSize; i++ )					//判断是否要紧缩目录
			   if ( Directory[i] != Directory[NewDirSize+i] ) return; 
															//不需紧缩目录, 结束处理返回			 
			 paddr *NewDir = Directory;
			 DicDepth--;				//目录深度减1
			 Directory = new paddr[NewDirSize];			//创建新目录
			 for ( i=0; i<NewDirSize; i++ ) Directory[i] = NewDir[i];
			 delete [ ] NewDir;
			 if (index<NewDirSize) combine ( index ); else combine(buddyid);							//递归, 看是否继续合并 
		   }
		}


		void Remove ( const TwoChars & key ) {				//搜索并删去关键码key
		   unsigned int id = makeAddress ( key, DicDepth );			//寻找关键码key所在页块的二进制地址
		   paddr p = Directory [id];						//搜索key所在页块
		   if ( p ) {									//找到, p是指向该页块的指针
			 PageRemove ( key, p );						//从p所指页块中删去关键码key
			 combine ( id );							//判断是否合并页块与紧缩目录
		   }
		}

		