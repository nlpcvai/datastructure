#include "iostream.h"
template <class Type> class SetList;					//用以表示集合的有序链表的类的前视定义

template <class Type> class SetNode {					//集合的结点类定义


public:
   SetNode ():link(NULL){};
   SetNode (const Type & item ) : data (item), link (NULL){};		//构造函数
friend class SetList<Type>;
friend ostream& operator <<(ostream& strm, SetList<Type>& a);
private:
   Type data;								//每个成员的数据
   SetNode<Type> *link;							//链接指针
};

template <class Type> class SetList {					//集合的类定义
public:
   SetList ( );								//构造函数
   void MakeEmpty ( );							//置空集合
   int AddMember ( const Type & x );					//把新元素x加入到集合之中
   int DelMember ( const Type & x );					//把集合中成员x删去
   void operator = ( SetList<Type> & right );			//复制集合right到this。
   void operator + ( SetList<Type> & right );			//求集合this与集合right的并
   void operator * ( SetList<Type> & right );			//求集合this与集合right的交
   void operator - ( SetList<Type> & right );				//求集合this与集合right的差
   int Contains ( const Type & x );					//判x是否集合的成员
   int operator == ( SetList<Type> & right );			//判集合this与集合right相等
   Type & Min ( );								//返回集合中的最小元素的值
   Type & Max ( );							//返回集合中的最大元素的值
   friend ostream& operator <<(ostream& strm, SetList<Type>& a);
private:
   SetNode<Type> *first, *last;						//有序链表的表头指针, 表尾指针
}
template <class Type> void SetList<Type>::SetList ( ) {
//本操作建立集合链表的头结点, 并将链表置空。
   first = last = new SetNode<Type>();  first->link = NULL;
}

template <class Type> void SetList<Type>::MakeEmpty(void){
   SetNode<Type> *tmp1=first->link,*tmp2;
   first->link=NULL;
   last=first;
   while (tmp1)
   {
     tmp2=tmp1;
     tmp1=tmp1->link;
     delete tmp2;
   }
}
template <class Type> int SetList<Type>::Contains ( const Type & x ) {
//测试函数: 如果x是集合的成员, 则函数返回1, 否则返回0。
   SetNode<Type> *temp = first->link;					//链的扫描指针
   while ( temp != NULL && temp->data < x ) temp = temp->link;	//循链搜索
   if ( temp != NULL && temp->data == x ) return 1;			//找到, 返回1
   else return 0;									//未找到, 返回0
}

template <class Type> int SetList<Type>::AddMember ( const Type & x ) {
//把新元素x加入到集合之中。若集合中已有此元素, 则函数返回0, 否则函数返回1。
   SetNode<Type> *p = first->link,  *q = first;				//p是扫描指针, q是p的前驱
   while ( p != NULL && p->data < x ) { q = p;  p = p->link; }	//循链扫描
   if ( p != NULL && p->data == x ) return 0;				//集合中已有此元素
   SetNode<Type> *s = new SetNode<Type> (x);					//创建数据值为x的新结点
   s->link = p;  q->link = s;							//链入有序链表, 插入位置在q、p之间
   if ( p == NULL ) last = s;							//链到链尾时要改链尾指针
   return 1;
}

template <class Type> int SetList<Type>::DelMember ( const Type & x ) {
//把集合中成员x删去。若集合不空且元素x在集合中, 则函数返回1, 否则返回0。
   SetNode<Type> *p = first->link,  *q = first;
   while ( p != NULL && p->data < x ) { q = p;  p = p->link; }	//循链扫描
   if ( p != NULL && p->data == x ) {					//找到
	 q->link = p->link;							//重新链接, , x位置在p所指结点
	 if ( p == last ) last = q;							//删去链尾结点时要改链尾指针
	 delete p;  return 1;							//删除含x结点
   }
   else return 0;									//集合中无此元素
}
template <class Type> void SetList<Type>::operator = ( SetList<Type> & right ) {
//复制集合right到this。
   SetNode<Type> *pb = right.first->link;				//复制源集合
   SetNode<Type> *pa = first = new SetNode<Type>;		//复制目标集合, 创建表头结点
   while ( pb != NULL ) {						//在链中逐个结点复制
	 pa->link = new SetNode<Type> (pb->data);		//创建this链下一个新结点
	 pa = pa->link;  pb = pb->link;				// pa进到新结点位置,  pb进到下一结点
   }
   pa->link = NULL;  last = pa;					//目标链表收尾
}

template <class Type> void SetList<Type>::operator + ( SetList<Type> & right ) {
//求集合this与集合right的并, 计算结果在this集合中, right集合不变。
   SetNode<Type> *pb = right.first->link;				//right集合的链扫描指针
   SetNode<Type> *pa = first->link;					//this集合的链扫描指针
   SetNode<Type> *pc = first;						//结果链的头结点和存放指针
   while ( pa != NULL && pb != NULL ) {				//两链数据两两比较
	 if ( pa->data == pb->data )					//两集合共有元素
	   { pc->link = pa;  pa = pa->link;  pb = pb->link; }
	 else if ( pa->data < pb->data )
	   { pc->link = pa;  pa = pa->link; }				//this中元素值小
	 else					//right集合中元素值小, 创建新结点, 链入结果链
	   { pc->link = new SetNode<Type> (pb->data);  pb = pb->link; }
	 pc = pc->link;
   }
   if ( pa != NULL ) pc->link = pa;					//this集合未扫完, 链接
   else {									//right集合未扫完,
	 while ( pb != NULL )						//向this集合逐个复制
	   { pc->link = new SetNode<Type> (pb->data);  pc = pc->link;  pb = pb->link; }
	 pc->link = NULL;  last = pc;					//链表收尾
   }
}

template <class Type> void SetList<Type>::operator * ( SetList<Type> & right ) {
//求两个集合的交, 结果保存在this集合中, right集合不变
   SetNode<Type> *pb = right.first->link;				//right集合的链扫描指针
   SetNode<Type> *pa = first->link;					//this集合的链扫描指针
   SetNode<Type> *pc = first;						//结果链的头结点和存放指针
   while ( pa != NULL && pb != NULL ) {				//两链数据两两比较
	 if ( pa->data == pb->data )					//两集合公有的元素
	   { pc = pc->link;  pa = pa->link;  pb = pb->link; }
	 else if ( pa->data < pb->data )				//this集合中元素值小, 删去这个元素
	   { pc->link = pa->link;  delete pa;  pa = pc->link; }
	 else pb = pb->link;						//right集合中元素值小, pb指针进1
   }
   while ( pa != NULL )							//逐个删去this集合中非公共元素
	 { pc->link = pa->link;  delete pa;  pa = pc->link; }
   last = pc;									//置链尾指针
}

template <class Type> void SetList<Type>::operator - ( SetList<Type> & right ) {
//求集合this与集合right的差。结果保留在集合this中, 集合right不变。
   SetNode<Type> *pb = right.first->link;				//right集合的链扫描指针
   SetNode<Type> *pa = first->link;					//this集合的链扫描指针
   SetNode<Type> *pc = first;						//结果链的头结点和存放指针
   while ( pa != NULL && pb != NULL ) {				//两两比较
	 if ( pa->data == pb->data )					//两集合共有的元素, 从this链中删去
	   { pc->link = pa->link;  delete pa;  pa = pc->link;  pb = pb->link; }
	 else if ( pa->data < pb->data )				//this集合中的元素值小, 保留
	   { pc = pc->link;  pa = pa->link; }
	 else pb = pb->link;						//不要, 向前继续检测
   }
   if ( pa == NULL ) last = pc;						//pa!=NULL时, 原来的last不变
}

template <class Type> int SetList<Type>::operator == ( SetList<Type> & right ) {
//当且仅当集合this与集合right相等时, 函数返回1, 否则返回0。
   SetNode<Type> *pb = right.first->link;				//right集合的链扫描指针
   SetNode<Type> *pa = first->link;					//this集合的链扫描指针
   while ( pa != NULL && pb != NULL )
	 if ( pa->data == pb->data )					//相等, 继续检测
	   { pa = pa->link;  pb = pb->link; }
	 else return 0;							//扫描途中不等时退出, 返回0
   if ( pa != NULL || pb != NULL ) return 0;			//链不等长时, 返回0
   return 1;
}
template <class Type>
ostream& operator <<(ostream& strm, SetList<Type>& a)
{
  SetNode<Type> *p=a.first;
  if (a.first!=a.last)
  {
    do
    {
     p=p->link;
     strm<<p->data<<' ';
    }while (p!=a.last);
  }
  strm<<endl;
   return strm;
}