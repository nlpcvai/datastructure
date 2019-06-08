//Algo1-7.cpp 求解约瑟夫环问题的程序
#include "C.h"
#include "DLinkListNH.h"
void Joseph(int n, int m)
{
	DLinkListNH<int> L;
	int i;
	int e;
	for(i=1; i<=n; i++)
		L.ListInsert(i, i); 
	do
	{
		for(i=1; i<m; i++)
		
			L.Head=L.Head->next;
		L.ListDelete(1, e);
		cout<<setw(3)<<e;
	}while(L.ListLength());
	cout<<endl;
}
void main()
{
	int n, m;
	cout<<"请输入小孩人数n 出队报数m：";
	cin>>n>>m;
	Joseph(n, m);
}

