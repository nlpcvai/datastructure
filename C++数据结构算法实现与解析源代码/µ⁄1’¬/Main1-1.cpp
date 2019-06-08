//Main1-1.cpp 验证顺序表SqList<T>类的成员函数
#include "C.h"
#include "SqList.h"
//以下两行可根据需要选其一（且只能选其一），而无须改变SqList.h
typedef int T;
//typedef double T;//定义以下的数据类型T为双精度型，print()需要。第6行
#include "Func1-1.cpp"
void main()
{
	bool i;
	int j, k;
	T e, e0;
	SqList<T> L;
	for(j=1; j<=5; j++)
		L.ListInsert(1, j);
	cout<<"在L的表头依次插入1～5后，L=";
	L.ListTraverse(print);
	cout<<"L是否空？"<<boolalpha<<L.ListEmpty()<<"，表长="<<L.ListLength()<<endl;
	L.GetElem(4, e);
	cout<<"第4个元素的值为"<<e<<endl;
	for(j=L.ListLength(); j<=L.ListLength()+1; j++)
	{
		k=L.LocateElem(j, equal);
		if(k)
			cout<<"值为"<<j<<"的元素是表L的第"<<k<<"个元素，";
		else
			cout<<"没有值为"<<j<<"的元素\n";
	}
	for(j=1; j<=2; j++)
	{
		L.GetElem(j, e);
		i=L.PriorElem(e, equal, e0);
		if(i)
			cout<<"元素"<<e<<"的前驱为"<<e0<<endl;
		else
			cout<<"元素"<<e<<"无前驱，";
	}
	for(j=L.ListLength()-1; j<=L.ListLength(); j++)
	{
		L.GetElem(j, e);
		i=L.NextElem(e, equal, e0);
		if(i)
			cout<<"元素"<<e<<"的后继为"<<e0;
		else
			cout<<"，元素"<<e<<"无后继"<<endl;
	}
	k=L.ListLength();
	for(j=k+1; j>=k; j--)
	{
		i=L.ListDelete(j, e);
		if(i)
			cout<<"删除第"<<j<<"个元素成功，其值为"<<e;
		else
			cout<<"删除第"<<j<<"个元素失败。";
	}
	L.ClearList();
	cout<<endl<<"清空L后，L是否空？"<<boolalpha<<L.ListEmpty();
	cout<<"，表长="<<L.ListLength()<<endl;
}

