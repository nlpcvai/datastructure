//SqList.h 顺序表的类（SqList类）
#ifndef _SQLIST_H_
#define _SQLIST_H_
#include "AList.h"
template<typename T>class SqList:public AList<T>
{
	friend void MergeList(const SqList<T>&, const SqList<T>&, SqList<T>&);
	
private:
	T *elem;
	int length;
	int listsize;
public:
	SqList(int k=1)
	{
		elem=new T[k];
		assert(elem!=NULL);
		length=0;
		listsize=k;
	}
	~SqList()
	{
		delete[]elem;
	}
	void ClearList()
	{
		length=0;
	}
	bool ListEmpty()const
	{
		return length==0;
	}
	int ListLength()const
	{
		return length;
	}
	bool GetElem(int i, T &e)const
	{
	 
		if(i<1 || i>length)
			return false;
		e=*(elem+i-1);
		return true;
	}
	int LocateElem(T e, bool(*eq)(T, T))const
	{
		int i=1;
		while(i<=length && !eq(*(elem+i-1), e))
		
			i++;
		if(i<=length)
			return i;
		else
			return 0;
	}
	bool PriorElem(T e, bool(*eq)(T, T), T &pre_e)const
	{
	 
		int i=LocateElem(e, eq);
		if(i<=1)
			return false;
		else
		{
			pre_e=*(elem+i-2);
			return true;
		}
	}
	bool NextElem(T e, bool(*eq)(T, T), T &next_e)const
	{
	 
		int i=LocateElem(e, eq);
		if(i==0 || i==length)
			return false;
		else
		{
			next_e=*(elem+i);
			return true;
		}
	}
	bool ListInsert(int i, T e)
	{
		T *newbase, *q, *p;
		if(i<1 || i>length+1)
			return false;
		if(length==listsize)
		{
			newbase=new T[listsize*2];
			assert(newbase!=NULL);
			for(int j=0; j<length; j++)
				*(newbase+j)=*(elem+j);
			delete[]elem;
			elem=newbase;
			listsize*=2;
		}
		q=elem+i-1;
		for(p=elem+length-1; p>=q;--p)
			*(p+1)=*p;
		*q=e;
		++length;
		return true;
	}
	bool ListDelete(int i, T &e)
	{
		T *p, *q;
		if(i<1 || i>length)
			return false;
		p=elem+i-1;
		e=*p;
		q=elem+length-1;
		for(++p; p<=q; ++p)
			*(p-1)=*p;
		length--;
		return true;
	}
	void ListTraverse(void(*visit)(T*))const;
};
template<typename T>
void SqList<T>::ListTraverse(void(*visit)(T*))const
{
	for(int i=0; i<length; i++)
		visit(elem+i);
	cout<<endl;
}
#endif

