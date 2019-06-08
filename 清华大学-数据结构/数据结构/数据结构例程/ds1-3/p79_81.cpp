		#include <stdio.h>

		enum Boolean { False, True };
		template <class Type> class List;					//链表类的前视定义
		template <class Type> class ListIterator;				//链表结点类的前视定义

		template <class Type> class ListNode {					//链表结点类的类声明
		friend class List <Type>;							//友元
		friend class ListIterator <Type>;					//友元
		public:
		   ListNode ( const Type value ) : data (value), link (NULL) { }
		   //………
		private:
		   Type data;
		   ListNode<Type> *link;
		};

		template <class Type> class List {					//链表类的类声明
		public:
		   friend class ListIterator<Type>;
		   List ( const Type value) { last =first = new ListNode<Type> (value) ; }	//构造函数
		   void Add ( const Type value ) ;
		   //………
		private:
		   ListNode<Type> *first, *last;
		};

		template <class Type> class ListIterator {				//链表游标类的类声明
		public:
		   ListIterator ( const List<Type> & l ) : list (l), current (l.first) { }
		   Boolean NotNull ( );
		   Boolean NextNotNull ( );
		   Type First ( );
		   Type Next ( );
		private:
		   const List<Type> & list;						//引用一个已存在的链表
		   ListNode<Type> *current;						//指向链表中的一个结点
		}

		template <class Type> Boolean ListIterator<Type>::NotNull ( ) {
		//检查链表中当前元素是否非空
		   if ( current != NULL ) return True; 					//链表当前结点指针非空
		   else return False;
		}

		template <class Type> Boolean ListIterator<Type>::NextNotNull ( ) {
		//检查链表中下一元素是否非空
		   if ( current != NULL && current->link != NULL ) return True;
		   else return False;
		}

		template <class Type> Type ListIterator<Type>::First ( ) {
		//返回指向链表中表头结点的指针
		   Type temp;
		   if ( list.first->link != NULL ) {
		       current = list.first;
		       temp = current->data;
		   }
		   else { current = NULL; temp = 0;}
		   return temp;
		}

		template <class Type> Type ListIterator<Type>::Next ( ) {
		//返回指向链表中下一个结点的指针
		   Type temp;
		   if ( current != NULL && current->link != NULL ) {
		      current = current->link;
		      temp = current->data;
		   }
		   else { current = NULL; temp = 0;}
		   return temp;
		}


		int sum ( const List<int> &l ) {
		   ListIterator<int> li (l);							//定义对象li为操作链表对象l的游标对象
		   if ( ! li.NextNotNull ( ) ) return 0;					//空链表, 返回0
		   int retvalue = li.First ( );						//取得第一个元素的值
		   while ( li.NextNotNull ( ) ) retvalue += li.Next ( );		//看是否下一个结点存在，若有, 累加
		   return retvalue;
		}

		template <class Type> void List<Type>::Add(const Type value) {
		   last->link = new ListNode<Type> (value);
                   last = last->link;
		}

