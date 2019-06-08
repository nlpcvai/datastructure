#include "iostream.h"
		template <class Type> class DataList;

		template <class Type> class Node {					//���ݱ��н����Ķ���
		friend class DataList<Type>;
		public:
		   Node (  ) : key ( 0 ) { }			//���캯��
		   Node ( const Type & value ) : key ( value ) { }			//���캯��
		   Type getKey ( ) const { return key; }					//��ȡ�ؼ���
		   void setKey ( Type k ) { key = k; }					//�޸Ĺؼ���
		   friend ostream &operator << (ostream &OutStream, const Node<Type> & OutNode );
		   friend istream & operator >> ( istream & InStream, Node<Type> & InNode );
		private:
		   Type key;								//�ؼ�����  
//		   other;									//������
		}; 

		template <class Type> class DataList {					//���ݱ��ඨ��
		public:
		   DataList ( int sz = 10 ) : ArraySize (sz), Element (new Node<Type>[sz+1]) { }
		   virtual ~DataList ( ) { delete [ ] Element; }
		   int GetSize() {return CurrentSize;}
		   friend ostream &operator << (ostream &OutStream, const DataList<Type> & OutList );
		   friend istream & operator >> ( istream & InStream, DataList<Type> & InList );
		protected:
		   Node<Type> *Element;									//���ݱ��д洢���ݵ�����
		   int ArraySize, CurrentSize;							//������󳤶Ⱥ͵�ǰ����
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
		   OutStream << "Array Contents : \n";					//���������б��OutStream
		   for ( int i = 1; i <=OutList.CurrentSize; i++ ) OutStream << OutList.Element[i] << ' ';
		   OutStream << endl;								//�����ĵ�ǰ���ȵ�OutStream
		   OutStream << "Array Current Size : " << OutList.CurrentSize << endl;
		   return OutStream;
		}

		template <class Type> istream & operator >> ( istream & InStream, DataList<Type> & InList ) {
		   cout << "Enter array Current Size : ";
		   InStream >> InList.CurrentSize;						//��Instream�����ĵ�ǰ����
		   cout << "Enter array elements : \n";
		   for ( int i=1; i <=InList.CurrentSize; i++ )				//��Instream������ȫ������
		   { cout << "Element " << i << " : ";  
		     InStream >> InList.Element[i]; 
		   }
		   return InStream;
		}
