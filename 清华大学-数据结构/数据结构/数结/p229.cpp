		#include "iostream.h"
		#include "p228.cpp"
		template <class Type> class searchList : public DataList<Type> {
		//搜索表searchList继承了DataList, 并且增加了成员函数Search ( )
		public:
		   searchList ( int sz = 10 ) : DataList<Type> (sz) { }
		   virtual ~searchList ( ) { }
		   virtual int Search ( const Type & x ) const;
		   int Search ( const Type & x,  int  loc ) const;
		};

	
		template <class Type> int searchList<Type>::Search ( const Type & x ) const {
		//在搜索表searchList中顺序搜索其关键码为x的数据对象，要求数据对象在表中从下标1开始存放，第0号
		//位置作为控制搜索过程自动结束的“监视哨”使用。若找到则函数返回该对象在表中的位置i，否则返回0。
		   Element[0].setKey ( x );	  int i = CurrentSize;				//将x送0号位置设置监视哨
		   while (Element[i].getKey ( ) != x ) i--;					//从后向前顺序搜索
		   return i;
		}

		template <class Type> int searchList<Type>::Search ( const Type & x,  int  loc )
		const 
		{
		   if ( loc > CurrentSize ) return 0;
		   else
		   if ( Element[loc].getKey( ) == x )
		     return loc;
		   else {return Search ( x, loc+1 );}
		}


