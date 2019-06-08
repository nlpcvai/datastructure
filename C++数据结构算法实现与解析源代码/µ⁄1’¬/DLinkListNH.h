//DLinkListNH.h 不设头结点的双向链表的类（DLinkListNH类）
#ifndef _DLINKLISTNH_H_
#define _DLINKLISTNH_H_
#include "DLNode.h"
template<typename T>class DLinkListNH
{
	friend void Joseph(int, int);
	friend class BoundaryLogo;
	friend class BuddySystem;
private:
	DLNode<T> *Head;
	DLNode<T>* GetElemP(int i)const
	{
		int j=1;
		DLNode<T> *p=Head;
		if(i<=0 || Head==NULL)
			return NULL;
		if(i==1)
			return p;
		do
		{
			p=p->next;
			j++;
		}while(p!=Head && j<i);
		if(p==Head)
			return NULL;
		else
			return p;
	}
public:
	DLinkListNH()
	{
		Head=NULL;
	}
	~DLinkListNH()
	{
		ClearList();
	}
	void ClearList()
	{
		DLNode<T> *p=Head;
		if(Head!=NULL)
		{
			Head->prior->next=NULL;
			while(p!=NULL)
			{
				p=p->next;
				delete Head;
				Head=p;
			}
		}
	}
	int ListLength()const
	{
		int i=0;
		DLNode<T> *p=Head;
		if(Head!=NULL)
			do
			{
				i++;
				p=p->next;
			}while(p!=Head);
		return i;
	}
	bool ListInsert(int i, T e)
	{
		DLNode<T> *s, *p=GetElemP(i-1);
		s=new DLNode<T>;
		if(s==NULL)
			return false;
		s->data=e;
		if(i==1)
		{
			if(Head==NULL)
				s->prior=s->next=s;
			else
			{
				s->prior=Head->prior;
				s->next=Head;
				s->prior->next=s;
				s->next->prior=s;
			}
			Head=s;
			return true;
		}
		else
		{
			if(p==NULL)
				return false;
			else
			{
				s->next=p->next;
				s->next->prior=s;
				s->prior=p;
				p->next=s;
				return true;
			}
		}
	}
/*	void ListInsert(int i, DLNode<T>* s)
	{
		DLNode<T> *p;
		assert(i>=1 || i<=ListLength()+1);
		if(Head==NULL)
		{
			Head=s;
			s->prior=s->next=s;
		}
		else
		{
			p=GetElemP(i);
			if(p!=NULL)
			{
				s->prior=p->prior;
				s->next=p;
				p->prior->next=s;
				p->prior=s;
			}
			else
			{
				s->next=Head;
				s->prior=Head->prior;
				Head->prior->next=s;
				Head->prior=s;
			}
			if(i==1)
				Head=s;
		}
	}*/
	bool ListDelete(int i, T &e)
	{
		DLNode<T> *p=GetElemP(i);
		if(p==NULL)
			return false;
		e=p->data;
		if(p->next==p)
			Head=NULL;
		else
		{
			p->next->prior=p->prior;
			p->prior->next=p->next;
			if(p==Head)
				Head=p->next;
		}
		delete p;
		return true;
	}
/*	void ListDelete(DLNode<T>* p)
	{
		if(ListLength()==1)
			Head=NULL;
		else
		{
			if(p==Head)
				Head=p->next;
			p->prior->next=p->next;
			p->next->prior=p->prior;
		}
	}*/
	void ListTraverse(void(*visit)(T*))const
	{
		DLNode<T> *p=Head;
		if(Head!=NULL)
			do
			{
				visit(&p->data);
				p=p->next;
			}while(p!=Head);
			cout<<endl;
	}
};
#endif

