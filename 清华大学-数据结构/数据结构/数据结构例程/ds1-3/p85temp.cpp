		#include <stdio.h>

		enum Boolean { False, True };
		template <class Type> class List;					//链表类的前视定义
		template <class Type> class ListIterator;				//链表结点类的前视定义

		template <class Type> class ListNode {					//链表结点类的类声明
		friend class List <Type>;							//友元
		friend class ListIterator <Type>;					//友元
		friend class Polynomial;
		friend Polynomial operator + ( const Polynomial & ah, const Polynomial & bh );
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
		   int sum ();
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
		   ListNode<Type>* First ( );
		   ListNode<Type>* Next ( );
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

		template <class Type> ListNode<Type>* ListIterator<Type>::First ( ) {
		//返回指向链表中表头结点的指针
		   if ( list.first->link != NULL ) { current = list.first; }
		   else { current = NULL; }
		   return current ;
		}

		template <class Type> ListNode<Type>* ListIterator<Type>::Next ( ) {
		//返回指向链表中下一个结点的指针
		   if ( current != NULL && current->link != NULL ) { current = current->link; }
		   else { current = NULL; }
		   return current;
		}

		char compare ( int a, int b ) {
		    if ( a > b ) return '>';
		    else if ( a == b ) return '=';
		    else return '<';
		}

		struct Term {						//用链表表示的多项式中, 链表结点的定义
		   int coef;							//系数
		   int exp;							//指数
		   void Init ( int c, int e ) { coef = c;  exp = e; }
		};

		class Polynomial	{					//多项式类的定义
		friend Polynomial operator + ( const Polynomial &, const Polynomial & );
		private:
		   List<Term> poly;					//单链表结构, 数据部分是Term
		};


		Polynomial operator + ( const Polynomial & ah, const Polynomial & bh ) {
		//两个带头结点的按降幂排列的多项式链表的头指针分别是ah和bh, 返回是结果多项式链表的表头指针,
		//指向ah的表头结点, 且结果不另外占用存储, 覆盖ah和bh链表
		   ListNode<Term> *pa, *pb, *pc, *p;
		   ListIterator<Term> Aiter ( ah.poly );
		   ListIterator<Term> Biter ( bh.poly );
		   pa = pc = Aiter.First ( );  pb = Biter.First ( );			//取得ah与bh的表头结点
		   pa = Aiter.Next ( );  pb = Biter.Next ( );				//pa、pb是链表ah、bh的检测指针
		   delete pb;								//保留ah的表头结点, 删去bh的表头结点
		   while ( Aiter.NotNull ( ) && Biter.NotNull ( ) )			//两两比较
			  switch ( compare ( pa->data.exp, pb->data.exp ) ) {
				case '=' :							//pa→exp==pb→exp
				   pa->data.coef = pa->data.coef+pb->data.coef;			//系数相加
				   p = pb;  pb = Biter.Next ( );  delete p;		//删去原pb所指结点
				   if ( !pa->data.coef ) { p = pa;  pa = Aiter.Next ( );  delete p; }	//相加为零, 不要
				   else { pc->link = pa;  pc = pa;  pa = Aiter.Next ( ); }		//相加不为零, 加入ch链
				   break;
				case '<' :							//pa→exp < pb→exp
				   pc->link = pb;  pc = pb;  pb = Biter.Next ( );
				   break;
				case '>' :							//pa→exp > pb→exp
				   pc->link = pa;  pc = pa;  pa = Aiter.Next ( );
			  }
		   if ( Aiter.NotNull ( ) )  pc->link = pa;				//剩余部分链入ch链
		   else  pc->link = pb;
		   return ah;
		}

		Polynomial operator * ( const Polynomial & ah, const Polynomial & bh )


		void Calc ( ) {
		   Polynomial a, b, c, d, t;
		   cin >> a;  cin >> b;  cin >> c;				//读入3个多项式
		   t = a * b;  d = t + c;
		   cout << d;
		}
