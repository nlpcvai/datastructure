#include "iostream.h"
		template <class Type> class DataList;

		template <class Type> class Node {					//数据表中结点类的定义
		friend class DataList<Type>;
		public:
		   Node (  ) : key ( 0 ) { }			//构造函数
		   Node ( const Type & value ) : key ( value ) { }			//构造函数
		   Type getKey ( ) const { return key; }					//读取关键码
		   void setKey ( Type k ) { key = k; }					//修改关键码
		   friend ostream &operator << (ostream &OutStream, const Node<Type> & OutNode );
		   friend istream & operator >> ( istream & InStream, Node<Type> & InNode );
		private:
		   Type key;								//关键码域  
//		   other;									//其他域
		}; 

		template <class Type> class DataList {					//数据表类定义
		public:
		   DataList ( int sz = 10 ) : ArraySize (sz), Element (new Node<Type>[sz+1]) { }
		   virtual ~DataList ( ) { delete [ ] Element; }
		   int GetSize() {return CurrentSize;}
		   friend ostream &operator << (ostream &OutStream, const DataList<Type> & OutList );
		   friend istream & operator >> ( istream & InStream, DataList<Type> & InList );
		protected:
		   Node<Type> *Element;									//数据表中存储数据的数组
		   int ArraySize, CurrentSize;							//数组最大长度和当前长度
		};

		template <class Type> ostream & operator << ( ostream & OutStream, const Node<Type> & OutNode ) {
		   OutStream << OutNode.key;
		   return OutStream;
		}

		template <class Type> istream & operator >> ( istream & InStream, Node<Type> & InNode ) {
		   
		   InStream >> InNode.key;
		   return InStream;
		}


		template <class Type> ostream & operator << ( ostream & OutStream, const DataList<Type> & OutList ) {
		   OutStream << "Array Contents : \n";					//输出表的所有表项到OutStream
		   for ( int i = 1; i <=OutList.CurrentSize; i++ ) OutStream << OutList.Element[i] << ' ';
		   OutStream << endl;								//输出表的当前长度到OutStream
		   OutStream << "Array Current Size : " << OutList.CurrentSize << endl;
		   return OutStream;
		}

		template <class Type> istream & operator >> ( istream & InStream, DataList<Type> & InList ) {
		   cout << "Enter array Current Size : ";
		   InStream >> InList.CurrentSize;						//从Instream输入表的当前长度
		   cout << "Enter array elements : \n";
		   for ( int i=1; i <=InList.CurrentSize; i++ )				//从Instream输入表的全部表项
		   { cout << "Element " << i << " : ";  
		     InStream >> InList.Element[i]; 
		   }
		   return InStream;
		}
