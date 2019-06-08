		#include <stdio.h>
		#include <iostream.h>

		template <class Type> class List;					//前视的类定义

		template <class Type> class ListNode {					//链表结点类的定义
		friend class List<Type>;							//List类作为友元类定义
		public:
		   ListNode ( );								//不给数据的构造函数
		   ListNode ( const Type& item );					//给数据的构造函数
		   ListNode ( const Type& item, ListNode<Type>* next );
		   ListNode<Type> *NextNode ( ) { return link; }			//给出当前结点的下一个结点地址
		   void InsertAfter ( ListNode<Type> *p );				//当前结点插入
		   ListNode<Type> *GetNode ( const Type& item, ListNode<Type> *next );	//建立一个新结点
		   ListNode<Type> *RemoveAfter ( );					//删除当前结点的下一结点
		private:
		   Type data;								//数据域
		   ListNode<Type> *link;						//链指针域
		};

		template <class Type> class List {					//单链表类定义
		public:
		   List ( ) { last =first = new ListNode<Type> ( ); }	//构造函数, 建立一个空链表
		   ~List ( );									//析构函数
		   void MakeEmpty ( );							//将链表置为空表
		   int Length ( ) const;							//计算链表的长度
		   ListNode<Type> *GetNode ( const Type& item, ListNode<Type> *next );	//建立一个新结点
		   ListNode<Type> *FindValue ( Type value );				//在链表中搜索含数据value的结点
		   ListNode<Type> *FindPosition ( int i );					//搜索链表中第i个元素的地址
		   int Insert ( Type value, int i );					//将新元素value插入在链表中第i个位置
		   Type *Remove ( int i );						//将链表中的第i个元素删去
		   Type *Get ( int i );							//取出链表中第i个元素
		   void Print();
		private:
		   ListNode<Type> *first, *last;					//链表的表头指针, 表尾指针
		};

		template <class Type> void ListNode<Type>::ListNode ( ) : link (NULL) { }
		//构造函数, 仅初始化指针成员。

		template <class Type> void ListNode<Type>::ListNode ( const Type& item ) : data (item), link (NULL) { }
		//构造函数, 初始化数据与指针成员。

		template <class Type> void ListNode<Type>::ListNode ( const Type& item, ListNode<Type>* next ) : data (item), link (next) { }

		template <class Type> void ListNode<Type>::InsertAfter ( ListNode<Type> *p ) {
		//将p所指示的结点链接成为当前结点(*this)的后继结点。
			 p->link = link;  link = p;
		}

		template <class Type> ListNode<Type>* List<Type>::GetNode ( const Type& item,
		ListNode<Type> * next ){
		//以数据成员item和指针next为参数, 建立一个新结点, 函数返回新结点地址。
		   ListNode<Type> *newnode = new ListNode<Type> ( item, next );
		   return newnode;
		}

		template <class Type> ListNode<Type> *ListNode<Type>::RemoveAfter ( ) {
		//从链中摘下当前结点的下一结点, 并为删除它而返回其地址。
		   ListNode<Type> *tempptr = link;					//保存要被删除结点的地址
		   if ( link == NULL ) return NULL;					//当前结点无后继, 返回NULL
		   link = tempptr->link;							//将被删结点从链中摘下
		   return tempptr;
		}

		template <class Type> List<Type>::~List ( ) { MakeEmpty ( );  delete first;  first = last = NULL; }
		//析构函数

		template <class Type> void List<Type>::MakeEmpty ( ) {
		//将链表置为空表
		   ListNode<Type> *q;
		   while ( first->link != NULL ) {					//当链不空时, 删去链中所有结点
			 q = first->link;  first->link = q->link;
			 delete q;								//循链逐个删除，保留一个表头结点
		   }
		   last = first;								//表尾指针指向表头结点
		}

		template <class Type> int List<Type>::Length ( ) const {
		//计算带表头结点的单链表的长度
		   ListNode<Type> *p = first->link;  int count = 0;
		   while ( p != NULL ) { p = p->link;  count++; }			//循链扫描, 寻找链尾
		   return count;
		}

		template <class Type> ListNode<Type> *List <Type>::FindValue ( Type value ) {
		//在单链表中搜索含数据value的结点, 搜索成功时, 函数返回该结点地址; 否则返回NULL值。
		   ListNode<Type> *p = first->link;
		   while ( p != NULL && p->data != value )  p = p->link;	//循链找含k结点
		   return p;
		}

		template <class Type> ListNode<Type> *List<Type>::FindPosition ( int i ) {
		//定位函数。函数返回链表中第i个元素的地址。若i<-1或i超出表中结点个数，则返回NULL。
		   if ( i < -1 ) return NULL;						// i值不合理
		   if ( i == -1 ) return first;						// i = -1时函数返回表头结点地址
		   ListNode<Type> *p = first->link;  int j = 0;			//检测指针p指向表中第一个结点
		   while ( p != NULL && j < i ) { p = p->link;  j = j++; }	//寻找第i个结点的地址
		   return p;				 //函数返回第i个结点地址, 若返回NULL, 表示i值太大
		}

		template <class Type> int List<Type>::Insert ( Type value, int i ) {
		//将新元素value插入在链表中第i个位置。
		   ListNode<Type> *p = FindPosition ( i-1 );					//定位第i-1个元素 (i ( 0)
		   if ( p == NULL ) return 0;						//参数i的值不合理，函数返回0
		   ListNode<Type> *newnode = GetNode ( value, p->link );	//创建含value的结点
		   if ( p->link == NULL ) last = newnode;
		   p->link = newnode;							//插入成功，函数返回1
		   return 1;
		}

		template <class Type> Type *List<Type>::Remove ( int i ) {
		//将链表中的第i个元素删去, 通过函数返回该元素。若i不合理, 则返回NULL。
		   ListNode<Type> *p = FindPosition (i-1), *q;				// p定位于第i-1个元素
		   if ( p == NULL || p->link == NULL ) return NULL;		// i的值不合理或空表，返回NULL
		   q = p->link;  p->link = q->link;					// q指向被删结点，重新拉链
		   Type value = q->data;						//取出被删结点中的数据值
		   if ( q == last ) last = p;						//删表尾结点时, 表尾指针修改
		   delete q;  return &value;
		}

		template <class Type> Type *List<Type>::Get ( int i ) {
		//取出链表中第i个元素。
		   ListNode<Type> *p = FindPosition ( i );					//定位于第i个元素
		   if ( p == NULL || p == first ) return NULL;			//空表或参数i的值不合理
		   else return & p->data;
		}

		template < class Type > void List<Type> :: Print() {
		    int i = 0;
		    Type *p = Get (i);
		    while ( p != NULL ) {
			cout << *p << "  " ;
			p = Get ( ++i );
		    }
		    if ( i == 0 ) cout << " empty!!!! ";
		    cout << endl;
		}
