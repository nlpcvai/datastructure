//LinkListNH.h 不设头结点的单链表的类（LinkListNH类）
#ifndef _LINKLISTNH_H_
#define _LINKLISTNH_H_
#include "LNode.h"
template<typename T>class LinkListNH
{
private:
	LNode<T> *Head;
public:
	LinkListNH()
	{
		Head=NULL;
	}
	~LinkListNH()
	{
		ClearList();
	}
	void ClearList()
	{
		LNode<T> *p;
		while(Head!=NULL)
		{
			p=Head;
			Head=Head->next;
			delete p;
		}
	}
	int ListLength()const
	{
		int i=0;
		LNode<T> *p=Head;
		while(p!=NULL)
		{
			i++;
			p=p->next;
		}
		return i;
	}
	int LocateElem(T e, bool(*eq)(T, T))const
	{
		int i=0;
		LNode<T> *p=Head;
		while(p!=NULL)
		{
			i++;
			if(eq(p->data, e))
				return i;
			p=p->next;
		}
		return 0;
	}
	LNode<T>* Point(T e, bool(*eq)(T, T), LNode<T>* &p)const
	{
	 
		if(Head)
			if(eq(Head->data, e))
			{
				p=NULL;
				return Head;
			}
			else
			{
				p=Head;
				while(p->next!=NULL)
					if(eq(p->next->data, e))
						return p->next;
					else
						p=p->next;
			}
		return NULL;
	}
	bool ListInsert(int i, T e)
	{
		int j=1;
		LNode<T> *s, *p=Head;
		if(i<1)
			return false;
		s=new LNode<T>;
		if(s==NULL)
			return false;
		s->data=e;
		if(i==1)
		{
			s->next=Head;
			Head=s;
		}
		else
		{
			while(p!=NULL && j<i-1)
			{
				j++;
				p=p->next;
			}
			if(p==NULL)
				return false;
			else
			{
				s->next=p->next;
				p->next=s;
			}
		}
		return true;
	}
	bool ListDelete(T e, bool(*eq)(T, T))
	{
		LNode<T> *p, *q;
		q=Point(e, eq, p);
		if(q==NULL)
			return false;
		else
		{
			if(p==NULL)
				Head=q->next;
			else
				p->next=q->next;
			delete q;
			return true;
		}
	}
	void ListTraverse(void(*visit)(T*))const
	{
		LNode<T> *p=Head;
		while(p!=NULL)
		{
			visit(&p->data);
			p=p->next;
		}
		cout<<endl;
	}
};
#endif

