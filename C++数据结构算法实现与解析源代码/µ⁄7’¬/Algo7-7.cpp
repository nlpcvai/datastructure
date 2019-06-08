//Algo7-7.cpp 二路归并排序类
#include "C.h"
#include "C4-1.h"
typedef int KeyType;
#include "SqTable.h"
template<typename D>class MerSort:public SqTable<D>
{
private:
	D *temp;
	void Merge(int low, int m, int high)
	{
		int i=low, j=m+1, k=low, p;
		
		for(; i<=m && j<=high; ++k)
			if LQ(elem[i].key, elem[j].key)
				temp[k]=elem[i++];
			else
				temp[k]=elem[j++];
		if(i<=m)
			for(p=0; p<=m-i; p++)
				temp[k+p]=elem[i+p];
		if(j<=high)
			for(p=0; p<=high-j; p++)
				temp[k+p]=elem[j+p];
		for(p=low; p<=high; p++)
		
			elem[p]=temp[p];
		cout<<endl<<"Merge("<<low<<", "<<m<<", "<<high<<")后："<<endl;
		Traverse(Visit);
	}
	void MSort(int low, int high)
	{
		if(low<high)
		{
			int m=(low+high)/2;
			MSort(low, m);
			MSort(m+1, high);
			Merge(low, m, high);
		}
	}
public:
	~MerSort()
	{
		if(temp!=NULL)
			delete[]temp;
	}
	void MergeSort()
	{
		temp=new D[length+1];
		MSort(1, length);
		
	}
};
#include "Func7-1.cpp"
void main()
{
	MerSort<ID> ms;
	ms.Creat_SeqFromFile("F7-1.txt");
	
	cout<<"排序前："<<endl;
	ms.Traverse(Visit);
	ms.MergeSort();
	cout<<endl<<"二路归并排序后："<<endl;
	ms.Traverse(Visit);
	cout<<endl;
}

