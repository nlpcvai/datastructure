		#include <stdio.h>
		#include <iostream.h>

		template <class Type> class DblList;

		template <class Type> class DblNode {
		friend class DblList<Type>;
		private:
		  Type data;								//链表结点数据
		  DblNode<Type> *lLink, *rLink;					//链表前驱(左链)、后继(右链)指针
		  DblNode ( Type value, DblNode<Type> *left, DblNode *right ) :
		      data (value), lLink (left), rLink (right) { }				//构造函数
		  DblNode ( Type value ) : data (value), lLink (NULL), rLink (NULL) { }	//构造函数
		};

		template <class Type> class DblList {
		public:
		   DblList ( Type uniqueVal );						//构造函数: 建立双向循环链表的表头结点。
		   ~DblList ( );								//析构函数: 释放双向循环链表所用存储。
		   int Length ( ) const;							//计算双向循环链表的长度。
		   int IsEmpty ( ) { return first->rLink == first; }			//判双向循环链表空否
		   int Find ( const Type & target );					//在链表中寻找等于给定值的结点。
		   Type getData ( ) const ;						//返回当前结点中存储的值。
		   void Firster ( ) { current = first; }					//初始化: 将当前指针指到表头结点。
		   int First ( );								//当前指针指向链表表头结点。
		   int Next ( );								//当前指针指到当前结点的后继结点。
		   int Prior ( );								//当前指针指到当前结点的前驱结点。
		   int operator ! ( ) { return current != NULL; }			//重载操作符: 判当前指针current空否
		   void Insert ( const Type & value );					//插入一个包含有值value的新结点。
		   void Remove ( );						//删除当前结点。
		   void Print ();
		private:
		   DblNode<Type> *first, *current;
		};


		template <class Type> DblList<Type>::DblList ( Type uniqueVal ) {
		//构造函数: 建立双向循环链表的表头结点, 它包含了一个用于某些特定情况的值。
		   first = new DblNode<Type> ( uniqueVal );
		   first->rLink = first->lLink = first;   current = NULL;
		}

		template <class Type> DblList<Type>::~DblList() {
		    current = first->rLink;
		    while ( current != first ) { current = current->lLink; delete current->lLink; }
		    delete first;
		}

		template <class Type> int DblList<Type>::Length ( ) const {
		//计算带表头结点的双向循环链表的长度, 通过函数返回。
		   DblNode<Type> * p = first->rLink;
		   int count = 0;
		   while ( p != first ) { p = p->rLink;  count++; }
		   return count;
		}

		template <class Type> int DblList<Type>::Find ( const Type & target ) {
		//在带表头结点的双向循环链表中寻找其值等于target的结点, 若找到, 则函数返回1, 同时current指针
		//指向该结点, 否则函数返回0。
		   DblNode<Type> *p = first->rLink;
		   while ( p != first && p->data != target )  p = p->rLink;		//寻找含target的结点
		   if ( p != first ) { current = p;  return 1; }					//搜索成功, 返回1
		   return 0;										//没有找到, 返回0
		}

		template <class Type> Type DblList<Type>::getData () const {
		    if ( current == NULL ) return first->data;
		    else return current->data;
		}

		template <class Type> int DblList<Type>::First ( ) {
		//若链表非空, 则将当前指针指向链表的第一个结点且函数返回1; 若链表空, 则令当前指针为NULL且
		//函数返回0。
		   if ( !IsEmpty ( ) ) { current = first->rLink;  return 1; }
		   current = NULL;  return 0;
		}

		template <class Type> int DblList<Type>::Next ( ) {
		//若当前结点有后继结点, 则当前指针指到当前结点的后继结点且函数返回1, 否则令当前指针为NULL
		//且函数返回0。
		   if ( current->rLink == first ) { current = NULL;  return 0; }
		   current = current->rLink;  return 1;
		}

		template <class Type> int DblList<Type>::Prior ( ) {
		//若当前结点有前驱结点, 则当前指针指到当前结点的前驱结点且函数返回1; 否则令当前指针为NULL
		//且函数返回0。
		   if ( current->lLink == first ) { current = NULL;  return 0; }
		   current = current->lLink;  return 1;
		}

		template <class Type> void DblList<Type>::Insert ( const Type & value ) {
		//建立一个包含有值value的新结点, 并将其插入到当前结点之后。
		   if ( current == NULL )							//原为空表
		      current = first->rLink = new DblNode<Type> ( value, first, first );
		   else {										//原为非空表
			 current->rLink = new DblNode<Type> ( value, current, current->rLink );
			 current = current->rLink;						//新结点成为当前结点
		       }
		   current->rLink->lLink = current;						//完成重新链接
		}

		template <class Type> void DblList<Type>::Remove ( ) {
		//在带表头结点的双向循环链表中删除当前结点, 同时让当前指针指到链表中的下一个结点, 若被删结点
		//是链表最后一个结点, 则让当前指针指到表中最前端第一个结点。如果删除后链表变成空链表, 则令当
		//前指针为NULL。
		   if ( current != NULL ) {
		      DblNode<Type> *temp = current;
		      current = current->rLink;						//当前指针指到下一结点
		      current->lLink = temp->lLink;						//将被删结点从链中摘下
		      temp->lLink->rLink = current;  delete temp; 			//删除
		      if ( current == first )
			 if ( IsEmpty ( ) ) current = NULL;					//删后链表变空
			 else  current = current->rLink;
		   }
		}

		template <class Type> void DblList<Type>::Print ( ) {
		    if ( first->rLink == first ) cout << "It is empty" << endl;
		    else {
			DblNode<Type> * temp = first;
			while ( temp->rLink != first ) {
			    temp = temp->rLink;
			    cout << temp->data << "  " ;
			}
			cout << endl;
		    }
		}
