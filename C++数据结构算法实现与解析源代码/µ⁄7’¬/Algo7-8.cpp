//Algo7-8.cpp 验证静态链表插入排序类
#include "C.h"
#include "C4-1.h"
typedef int KeyType;
#include "SLinkSort.h"
#include "Func7-2.cpp"
void main()
{
	SLinkSort<SL> sls[2];
	for(int i=0; i<2; i++)
	{
		sls[i].Creat_SeqFromFile("F7-1.txt");
		if(i==0)
		{
			cout<<"排序前："<<endl;
			sls[i].Traverse(Visit);
		}
		sls[i].MakeTableSorted();
		if(i==0)
		{
			cout<<endl<<"链式有序后："<<endl;
			sls[i].Traverse(Visitn);
		}
		if(i==0)
		{
			sls[i].Arrange();
			cout<<endl<<"Arrange排序后："<<endl;
		}
		else
		{
			sls[i].Rearrange();
			cout<<endl<<"Rearrange排序后："<<endl;
		}
		sls[i].Traverse(Visit);
	}
	cout<<endl;
}

