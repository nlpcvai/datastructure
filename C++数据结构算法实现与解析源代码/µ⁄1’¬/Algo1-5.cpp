//Algo1-5.cpp 用SqList类型和LinkList类型分别实现基于抽象类AList<T>的函数
#include "C.h"
#include "SqList.h"
#include "LinkList.h"
typedef int T;
#include "Func1-1.cpp"
void AMergeList(const AList<T> &La, const AList<T> &Lb, AList<T> &Lc)
{
 
	int i=1, j=1, k=0;
	int La_len, Lb_len;
	T ai, bj;
	La_len=La.ListLength();
	Lb_len=Lb.ListLength();
	while(i<=La_len && j<=Lb_len)
	{
		La.GetElem(i, ai);
		Lb.GetElem(j, bj);
		if(ai<=bj)
		{
			Lc.ListInsert(++k, ai);
			++i;
		}
		else
		{
			Lc.ListInsert(++k, bj);
			++j;
		}
	}
	while(i<=La_len)
	{
		La.GetElem(i++,ai);
		Lc.ListInsert(++k, ai);
	}
	while(j<=Lb_len)
	{
		Lb.GetElem(j++,bj);
		Lc.ListInsert(++k, bj);
	}
}
void main()
{
	SqList<T> La(5), Lb(5), Lc(10);
//	LinkList<T> La, Lb, Lc;//主函数第2行
	for(int j=1; j<=5; j++)
	{
		La.ListInsert(j, j);
		Lb.ListInsert(j, 2*j);
	}
	cout<<"La=";
	La.ListTraverse(print);
	cout<<"Lb=";
	Lb.ListTraverse(print);
	AMergeList(La, Lb, Lc);
	cout<<"Lc=";
	Lc.ListTraverse(print);
}

