//Algo7-3.cpp 简单选择排序类
#include "C.h"
typedef int KeyType;
#include "SqTable.h"
template<typename D>class SelSort:public SqTable<D>
{
private:
	int SelectMinKey(int i)
	{
		int j, k=i;
		KeyType min=elem[i].key;
		for(j=i+1; j<=length; j++)
			if(elem[j].key<min)
			{
				k=j;
				min=elem[j].key;
			}
			return k;
	}
public:
	void SelectSort()
	{
		int i, j;
		for(i=1; i<length; ++i)
		{
			j=SelectMinKey(i);
			if(i!=j)
				swap(elem[i], elem[j]);
		}
	}
};
#include "Func7-1.cpp"
void main()
{
	SelSort<ID> ss;
	ss.Creat_SeqFromFile("F7-1.txt");
	cout<<"排序前："<<endl;
	ss.Traverse(Visit);
	ss.SelectSort();
	cout<<endl<<"简单选择排序后："<<endl;
	ss.Traverse(Visit);
	cout<<endl;
}

