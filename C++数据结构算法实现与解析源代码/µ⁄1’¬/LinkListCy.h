//LinkListCy.h 设立尾指针的单循环链表的类（LinkListCy类）
#ifndef _LINKLISTCY_H_
#define _LINKLISTCY_H_
#include "AList.h"
#include "LNode.h"
template<typename T>class LinkListCy:public AList<T>
{
	friend void MergeList(LinkListCy<T>&, LinkListCy<T>&);
private:
	LNode<T> *Tail;
public:
	LinkListCy()
	{
		Tail=new LNode<T>;
		assert(Tail!=NULL);
		Tail->next=Tail;
	}
	~LinkListCy()
	{
		ClearList();
		delete Tail;
	}
	void ClearList()
	{
		LNode<T> *p, *q;
		Tail=Tail->next;
		p=Tail->next;
		while(p!=Tail)
		{
			q=p->next;
			delete p;
			p=q;
		}
		Tail->next=Tail;
	}
	bool ListEmpty()const
	{
		return Tail->next==Tail;
	}
	int ListLength()const
	{
		int i=0;
		LNode<T> *p=Tail->next;
		while(p!=Tail)
		{
			i++;
			p=p->next;
		}
		return i;
	}
	bool GetElem(int i, T &e)const
	{
		int j=1;
		LNode<T> *p=Tail->next->next;
		if(i<=0 || i>ListLength())
			return false;
		while(j<i)
		{
			j++;
			p=p->next;
		}
		e=p->data;
		return true;
	}
	int LocateElem(T e, bool(*eq)(T, T))const
	{
		int i=0;
		LNode<T> *p=Tail->next->next;
		while(p!=Tail->next)
		{
			i++;
			if(eq(p->data, e))
				return i;
			p=p->next;
		}
		return 0;
	}
	bool PriorElem(T e, bool(*eq)(T, T), T &pre_e)const
	{
	 
		LNode<T> *q, *p=Tail->next->next;
		q=p->next;
		while(q!=Tail->next)
		{
			if(eq(q->data, e))
			{
				pre_e=p->data;
				return true;
			}
			p=q;
			q=q->next;
		}
		return false;
	}
	bool NextElem(T e, bool(*eq)(T, T), T &next_e)const
	{
	 
		LNode<T> *p=Tail->next->next;
		while(p!=Tail)
		{
			if(eq(p->data, e))
			{
				next_e=p->next->data;
				return true;
			}
			p=p->next;
		}
		return false;
	}
	bool ListInsert(int i, T e)
	{
		LNode<T> *p=Tail->next, *s;
		int j=0;
		if(i<=0 || i>ListLength()+1)
			return false;
		while(j<i-1)
		{
			j++;
			p=p->next;
		}
		s=new LNode<T>;
		if(s==NULL)
			return false;
		s->data=e;
		s->next=p->next;
		p->next=s;
		if(p==Tail)
			Tail=s;
		return true;
	}
	bool ListDelete(int i, T &e)
	{
		LNode<T> *q, *p=Tail->next;
		int j=0;
		if(i<=0 || i>ListLength())
			return false;
		while(j<i-1)
		{
			j++;
			p=p->next;
		}
		q=p->next;
		p->next=q->next;
		e=q->data;
		if(Tail==q)
			Tail=p;
		delete q;
		return true;
	}
	void ListTraverse(void(*visit)(T*))const
	{
		LNode<T> *p=Tail->next->next;
		while(p!=Tail->next)
		{
			visit(&p->data);
			p=p->next;
		}
		cout<<endl;
	}
};
#endif

