//Algo1-6.cpp 两个单循环链表合并的算法
#include "C.h"
#include "LinkListCy.h"
typedef int T;
#include "Func1-1.cpp"
void MergeList(LinkListCy<T> &La, LinkListCy<T> &Lb)
{
	LNode<T> *p=Lb.Tail->next;
	Lb.Tail->next=La.Tail->next;
	La.Tail->next=p->next;
	La.Tail=Lb.Tail;
	Lb.Tail=p;
	Lb.Tail->next=Lb.Tail;
}
void main()
{
	LinkListCy<T> La, Lb;
	for(int i=1; i<=3; i++)
	{
		La.ListInsert(i, i);
		Lb.ListInsert(i, i+3);
	}
	cout<<"La=";
	La.ListTraverse(print);
	cout<<"Lb=";
	Lb.ListTraverse(print);
	MergeList(La, Lb);
	cout<<"New La=";
	La.ListTraverse(print);
}

