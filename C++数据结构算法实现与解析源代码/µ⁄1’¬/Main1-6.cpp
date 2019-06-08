//Main1-6.cpp 验证不设头结点单链表LinkListNH<T>类的成员函数
#include "C.h"
#include "LinkListNH.h"
typedef int T;
#include "Func1-1.cpp"
void main()
{
	LinkListNH<T> L;
	bool i;
	int j, k;
	for(j=1; j<=5; j++)
		L.ListInsert(j, j);
	cout<<"在L的表尾依次插入1～5后，L=";
	L.ListTraverse(print);
	cout<<"表长="<<L.ListLength()<<endl;
	for(j=6; j>=5; j--)
	{
		k=L.LocateElem(j, equal);
		if(k)
			cout<<"值为"<<j<<"的元素是表L的第"<<k<<"个元素，";
		else
			cout<<"没有值为"<<j<<"的元素，";
		i=L.ListDelete(j, equal);
		if(i==false)
			cout<<"删除元素"<<j<<"失败（不存在此元素）"<<endl;
		else
			cout<<"成功删除元素"<<j<<endl;
	}
	cout<<"删除元素后，L=";
	L.ListTraverse(print);
	L.ClearList();
	cout<<"清空表L后，表L的长度="<<L.ListLength()<<endl;
}

