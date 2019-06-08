		#include "iostream.h"
		#include "p228.cpp"
		template <class Type> class OrderedList : public DataList<Type> {
		public:
		   OrderedList ( int sz = 10 ) : DataList<Type> (sz) { }
		   virtual ~OrderedList ( ) { }
		   virtual int BinarySearch ( const Type & x, const int low, const int high ) const;
           virtual int BinarySearch ( const Type & x ) const ;
		};	     
     
		template <class Type> 
		int OrderedList<Type>::BinarySearch ( const Type & x, const int low, const int high ) const {
		   int mid = -1;
		   if ( low <= high ) {
			 mid = ( low + high ) / 2;
			 if ( Element[mid].getKey( ) < x )				//�е�Ĺؼ���С�ڸ���ֵ��������������
			   mid = BinarySearch ( x, mid+1, high );
			 else if ( Element[mid].getKey( ) > x )			//�е�Ĺؼ�����ڸ���ֵ��������������
			   mid = BinarySearch ( x, low, mid-1 ); 
		   }
		   return mid;
		}

		template <class Type> int OrderedList<Type>::BinarySearch ( const Type & x ) const {
		   int high = CurrentSize,  low = 1,  mid;
		   while ( low <= high ) {
			 mid = ( low + high ) / 2;
			 if ( Element[mid].getKey ( ) < x ) low = mid + 1;			//������������
			 else if ( Element[mid].getKey ( ) > x ) high = mid - 1;		//������������
			 else return mid;								//�����ɹ��������ҵ�λ��
		   }
		   return -1;									//����ʧ�ܣ�����-1
		}
