		//Test is T74_75.cpp

		#include <stdio.h>
		#include <iostream.h>

		class List;							//List类的前视声明

		class ListNode {						//结点类定义
		friend class List;
		friend ostream & operator << ( ostream&, List & );						//声明List类为友元类
		public:
		   //ListNode() { data = 0; link = NULL; );
		   ListNode( int x, ListNode * p ) { data = x; link = p; }
		private:
		   int data;							//数据元素域
		   ListNode *link;						//链指针域
		};

		class List {							//List类定义
		friend ostream & operator << ( ostream&, List & );						//声明List类为友元类
		public:
		   List(): first( NULL ) {};
		   //链表公共操作
		   //………
		   int Insert ( const int x, const int i );
		   int Remove ( int i );
		private:
		   ListNode *first, *last;					//指向链表表头的指针
		};

		#include <iostream.h>

		int List::Insert ( const int x, const int i ) {
		//将新元素x插入到第i结点之前。i是结点号，从0开始。
		   ListNode *p = first;  int k = 0;
		   while ( p != NULL && k< i-1 ) { p = p->link;  k++; }		//循链找第i-1个结点
		   if ( p == NULL && first != NULL ) {				//非空表而且链短，找不到第i-1个结点
			 cout << "Invalid position for Insertation!\n";  return 0;	//终止插入, 函数返回0
		   }
		   ListNode *newnode= new ListNode( x, NULL );				//建立一个newnode指示的新结点, 数据为x
		   if ( first == NULL || i == 0 ) {					//插入空表或非空表第一个结点之前
			  newnode->link = first;						//新结点成为第一个结点
			  if ( first == NULL ) last = newnode;				//原为空表时，表尾指针指向这个新结点
			  first = newnode;
		   }
		   else {									//插入在链表的中间或尾部
			  newnode->link = p->link;
			  if ( p->link == NULL ) last = newnode;
			  p->link = newnode;
		}
		   return 1;									//正常插入，函数返回1
		}

		int List::Remove ( int i ) {
		//将链表中的第i个元素删去, 通过函数返回该元素。若i不合理, 则返回NULL。
		   if ( i < 0 ) { cout << "Invalid position for Deletion!\n";  return 0;}	//不能删除, 函数返回0
		   ListNode *p = first, *q;  int k = 0;
		   while ( p != NULL && k< i-1 ) { p = p->link; k++; }		//循链找第i-1个结点
		   if ( p == NULL || p->link == NULL ) {							//空表或者链短，找不到第i-1个结点
			  cout << "Invalid position for Deletion!\n";  return 0;	//不能删除, 函数返回0
		   }
		   if ( i == 0 ) {	q = first;  p = first = first->link; } 		//删第一个结点时，重新拉链
		   else { q = p->link;  p->link = q->link; }			//删中间一个结点或尾结点时
		   if ( q == last ) last = p;						//删表尾结点时, 表尾指针修改
		   k = q->data;  delete q;  return k;					//取出被删结点中的数据值
		}

		ostream & operator << ( ostream& os , List & onelist) {
		    ListNode * p = onelist.first;
		    if ( p == NULL ) os << "It is empty";
		    else while ( p != NULL ) {
			     os << p->data << " " ;
			     p = p->link;
			 }
		    return os;
		}