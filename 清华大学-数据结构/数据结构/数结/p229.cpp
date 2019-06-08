		#include "iostream.h"
		#include "p228.cpp"
		template <class Type> class searchList : public DataList<Type> {
		//������searchList�̳���DataList, ���������˳�Ա����Search ( )
		public:
		   searchList ( int sz = 10 ) : DataList<Type> (sz) { }
		   virtual ~searchList ( ) { }
		   virtual int Search ( const Type & x ) const;
		   int Search ( const Type & x,  int  loc ) const;
		};

	
		template <class Type> int searchList<Type>::Search ( const Type & x ) const {
		//��������searchList��˳��������ؼ���Ϊx�����ݶ���Ҫ�����ݶ����ڱ��д��±�1��ʼ��ţ���0��
		//λ����Ϊ�������������Զ������ġ������ڡ�ʹ�á����ҵ��������ظö����ڱ��е�λ��i�����򷵻�0��
		   Element[0].setKey ( x );	  int i = CurrentSize;				//��x��0��λ�����ü�����
		   while (Element[i].getKey ( ) != x ) i--;					//�Ӻ���ǰ˳������
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


