//AList.h 线性表抽象类的定义
#ifndef _ALIST_H_
#define _ALIST_H_
template<typename T>class AList
{
public:
	void ClearList();
	bool ListEmpty()const;
	int LocateElem(T e, bool(*eq)(T, T))const;
	
	bool PriorElem(T e, bool(*eq)(T, T), T &pre_e)const;
	
	
	bool NextElem(T e, bool(*eq)(T, T), T &next_e)const;
	
	
	bool ListDelete(int i, T &e);
	
	void ListTraverse(void(*visit)(T*))const;
	
	virtual bool GetElem(int i, T &e)const=0;
	
	virtual bool ListInsert(int i, T e)=0;
	
	virtual int ListLength()const=0;
};
#endif

