#include "iostream.h"
#ifndef MAXKEY
#define MAXKEY 32767
#endif
		const MaxM=100;
		template <class Type> class Mtree;
		template <class Type> class Btree;
		template <class Type> class Mnode {					// B_树结点类定义
		public:
			void insertkey(int,Type,Mnode<Type>*);
			Mnode(){n=0;parent=NULL;for (int i=0;i<=MaxM;i++) ptr[i]=NULL;}
		private:
		   int n;									//当前结点中关键码个数
		   Mnode<Type> *parent;						//双亲结点指针
		   Type key[MaxM+1];								//key[MaxM]为监视哨兼工作单元, key[0]未用
		   Mnode<Type> *ptr[MaxM+1];						//子树结点指针数组, ptr[m]未用
		   friend ostream& operator <<(ostream& strm, Mnode<Type>& mn);
		   friend class Mtree<Type>;
		   friend class Btree<Type>;
		};
		
		template <class Type>
		class Triple {								//搜索结果
		public:
		   Mnode<Type> *r;							//B_树结点地址
		   int i;  char tag;							//结点中关键码序号及搜索成功标志
		   friend ostream& operator <<(ostream& strm, Triple<Type>& tp);
		};

		template <class Type> class Mtree {                 
		public:
		   Mtree(int d=3){root=NULL;m=d;};		   
		   void insertkey(Mnode<Type>*,int,Type,Mnode<Type>*);
		   Triple<Type>  Search ( const Type & );
		   friend ostream& operator <<(ostream& strm, Mtree<Type>& mt);
		protected:
			void move ( Mnode<Type>*p, Mnode<Type>*q, int s, int m );
			void print(ostream& strm,Mnode<Type> *p);
		   Mnode<Type> *root;
		   int m;
		};

		template <class Type> Triple<Type>  Mtree<Type>::Search ( const Type & x ) {
		//用关键码x搜索驻留在磁盘上的m路搜索树。各结点格式为n, A[0], (k[1],A[1]),……,  (K[n],A[n]), n < m。
		//函数返回一个类型为Triple (r, i, tag)的对象。tag=1, 表示x 在结点r找到, 是该结点的K[i];  tag=0, 表
		//示没有找到x, 这时可以插入的结点是r, 插入到该结点的K[i]与K[i+1]之间。
		   Triple<int> result;							//存放结果的工作单元
		   GetNode ( root );						//从磁盘上读取位于根root的结点
		   Mnode <Type> *p = root, *q = NULL;			//p是扫描指针, q是p的父结点指针
		   int i;
		   while ( p != NULL ) {						//继续搜索
			 i = 0;  p->key[(p->n)+1] = MAXKEY;
			 while ( p->key[i+1] < x ) i++;				//在结点内顺序搜索
			 if ( p->key[i+1] == x ) {					//搜索成功, 本结点有x
				result.r = p;  result.i = i+1;  result.tag = 0;
				return result;					//返回结果, 返回主程序
			 }
			 q = p;  p = p->ptr[i];					//本结点无x, q记下当前结点, p下降到相应子树			 GetNode (p);							//从磁盘上读取p结点
		   }
		   result.r = q;  result.i = i;  result.tag = 1;
		   return result;							//x可能落入的区间[ Ki, Ki+1 )
		}
		template <class Type> class Btree : public Mtree<Type> {		//B_树的类定义
		public:
		   //Search从Mtree继承;
		   int Insert ( const Type& x );						//插入关键码x
		   int Remove ( const Type& x );					//删除关键码x
		private:		
		void LeftAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j );
		void RightAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j );
		void compress ( Mnode<Type> *p, const int j );
		void merge ( Mnode<Type> *p, Mnode<Type> *q, Mnode<Type> *p1, int j) ;

		};
		template <class Type>
			void GetNode(Mnode<Type> *p)
		{
			//理论上应该从磁盘读入结点p,现在这里可以为空
		};		
		template <class Type>
			void PutNode(Mnode<Type> *p)
		{
			//理论上应该从磁盘写结点p,现在这里可以为空
		};		

		template <class Type>
			void Mtree<Type>::print(ostream& strm,Mnode<Type> *p)
		{
			if (p)
			{		
			strm<<*p;
			if (p->n)
			{	strm<<"(";
				for (int i=0;i<=p->n;i++)				
					print(strm,p->ptr[i]);
			
				strm<<")";
			}
			}
		}
		template <class Type>
		ostream& operator <<(ostream& strm, Mtree<Type>& mt)
		{
			mt.print(strm,mt.root);
			return strm;
		}
		template <class Type>
		ostream& operator <<(ostream& strm, Mnode<Type>& mn)
		{
			strm<<"[";
			for (int i=1;i<=mn.n;i++)
			{
				if (i!=1) strm<<',';
				strm<<mn.key[i];
			}
			strm<<"]";
			return strm;
			
		}
	template <class Type>
	 ostream& operator <<(ostream& strm, Triple<Type>& tp)
	{
		if (tp.tag) strm<<"Key Not Found";
			else
			strm<<"Key Found at :"<<*tp.r<<" No. "<<tp.i<<" key";
		return strm;
	}
	template <class Type>
		void Mnode<Type>::
	insertkey(int i,Type K,Mnode<Type>* q)
	{
		for (int j=n;j>=i;j--)
		{
			key[j+1]=key[j];
			ptr[j+1]=ptr[j];
		}
		key[i]=K;
		ptr[i]=q;
		n++;
	};
	template <class Type>
		void Mtree<Type>::
	insertkey(Mnode<Type>* p,int i,Type K,Mnode<Type>* q)
	{
		p->insertkey(i,K,q);
	}
	template <class Type>
		void Mtree<Type>::move ( Mnode<Type>*p, Mnode<Type>*q, int s, int m )
	//将 p的key[s+1..m]和ptr[s..m]移到q的key[1..s-1]和ptr[0..s-1]
	//p->n改为s, q->n改为m-s
	{
		int j=0;
		q->ptr[0]=p->ptr[s];
		if (q->ptr[0])
			q->ptr[0]->parent=q; 
		for (int i=s+1;i<=m;i++)
		{
			j++;
			q->key[j]=p->key[i];
			q->ptr[j]=p->ptr[i];
			if (q->ptr[j])
				q->ptr[j]->parent=q;
		}
		q->n=m-s;
		p->n=s-1;
	}