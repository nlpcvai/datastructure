//Main1-7.cpp 验证不设头结点双循环链表DLinkListNH<T>类的成员函数
#include "C.h"
#include "DLinkListNH.h"
typedef int T;
#include "Func1-1.cpp"
void main()
{
	DLinkListNH<T> L;
	bool i;
	int j;
	T e;
	for(j=1; j<=5; j++)
		L.ListInsert(j, j);
	cout<<"在L的表尾依次插入1～5后，L=";
	L.ListTraverse(print);
	cout<<"表长="<<L.ListLength()<<endl;
	for(j=0; j<=3; j++)
	{
		i=L.ListDelete(j, e);
		if(i==false)
			cout<<"删除第"<<j<<"个元素失败（不存在此元素）"<<endl;
		else
			cout<<"成功删除第"<<j<<"个元素"<<endl;
	}
	cout<<"删除3个元素后，L=";
	L.ListTraverse(print);
	L.ClearList();
	cout<<"清空表L后，表L的长度="<<L.ListLength()<<endl;
}

