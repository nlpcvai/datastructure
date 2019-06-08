//Algo7-5.cpp 快速排序类
#include "C.h"
typedef int KeyType;
#include "SqTable.h"
template<typename D>class QkSort:public SqTable<D>
{
private:
	int Partition(int low, int high)
	{
	 
		int i=low, j=high;
		elem[0]=elem[low];
		while(low<high)
		{
			while(low<high && elem[high].key>=elem[0].key)
				--high;
			elem[low]=elem[high];
			while(low<high&&elem[low].key<=elem[0].key)
				++low;
			elem[high]=elem[low];
		}
		elem[low]=elem[0];
		cout<<endl<<"pivotloc="<<low<<" Partition("<<i<<", "<<j<<")="<<endl;
		Traverse(Visit);
		return low;
	}
	void QSort(int low, int high)
	{
		if(low<high)
		{
			int pivotloc=Partition(low, high);
			
			QSort(low, pivotloc-1);
			QSort(pivotloc+1, high);
		}
	}
public:
	void QuickSort()
	{
		QSort(1, length);
	}
};
#include "Func7-1.cpp"
void main()
{
	QkSort<ID> qs;
	qs.Creat_SeqFromFile("F7-1.txt");
	cout<<"排序前："<<endl;
	qs.Traverse(Visit);
	qs.QuickSort();
	cout<<endl<<"快速排序后："<<endl;
	qs.Traverse(Visit);
	cout<<endl;
}

