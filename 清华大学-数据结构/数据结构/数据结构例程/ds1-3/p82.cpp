		#include <stdio.h>
                #include <iostream.h>

		enum Boolean { False, True };
		template <class Type> class CircList;

		template <class Type> class CircListNode {
		friend class CircList<Type>;
		public:
		   CircListNode ( Type d=0, CircListNode<Type> *next=NULL ) : data (d), link (next) { }
		private:
		   Type data;
		   CircListNode<Type> *link;
		};

		template <class Type> class CircList {
		public:
		   CircList ();
		   CircList ( Type value );						//构造函数
		   ~CircList ( );								//析构函数
		   int Length ( ) const;							//计算循环链表长度
		   Boolean IsEmpty ( ) { return first->link == first; }		//判表空否
		   Boolean Find ( const Type & value );				//在循环链表中寻找其值等于value的结点
		   Type getData ( ) { return current->data; }						//返回当前结点中存放的值
		   Type getNextData () ;
		   void Firster ( ) { current = first; }					//将当前指针置于头结点
		   void First ( );							//将当前指针指向链表的第一个结点
		   void Next ( );							//将当前指针指到当前结点的后继结点
		   void Prior ( );							//将当前指针指到当前结点的前驱结点
		   void Insert ( const Type & value );					//插入新结点
		   void RemoveNext ( );
		   void Josephus ( int n, int m );								//删除当前结点
		private:
		   CircListNode<Type> *first, *current, *last;			//头指针, 当前指针, 尾指针
		};

		template <class Type> void CircList <Type> :: CircList () {
		    current = last = first = new CircListNode<Type> ();
		    first->link = first;
		}

		template <class Type> void CircList <Type> :: ~CircList () {
		    CircListNode<Type> *q;
		    while ( first->link != first ) {
			q = first->link;   first->link = q->link;
			delete q;
		    }
		    delete first;  current = first = last = NULL;
		}

		template <class Type> void CircList <Type> :: Next () {
		    if ( current->link == first ) current = first;
		    current = current->link;
		}

		template <class Type> Type CircList <Type> :: getNextData() {
		    if ( current->link == first ) return first->link->data;
		       else return current->link->data;
		}

		template <class Type> void CircList <Type> :: RemoveNext () {
		    CircListNode<Type> *p = current->link;
		    if ( p == last ) last = current;
		    if ( p != first ) current->link = p->link;
			else { p = first->link; first->link = p->link; }
		    delete p;
		}

		template <class Type> void CircList <Type> :: Insert (const Type & value) {
		    CircListNode<Type> *p = new CircListNode<Type> ( value, first );
		    last = last->link = p;
		}

		template <class Type> void CircList <Type> :: Josephus ( int n, int m ) {
		   for ( int i=0; i<n-1; i++ ) {		     				//循环n-1趟，让n-1个人出列
			 for ( int j=0; j<m-1; j++ ) Next ( );	  			//让current向后移动m-1次
			 cout << "Delete person " << getNextData ( ) << endl;
			 RemoveNext ( ); 								//删去该结点，让current指示下一结点
		   }
		   cout << "the winner is : " << getData () << endl;
		}
