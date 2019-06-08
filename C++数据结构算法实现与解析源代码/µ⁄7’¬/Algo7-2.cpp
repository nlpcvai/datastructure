//Algo7-2.cpp √∞≈›≈≈–Ú¿‡
#include "C.h"
#include "C4-1.h"
typedef int KeyType;
#include "SqTable.h"
template<typename D>class BubSort:public SqTable<D>
{
public:
	void BubbleSort()
	{
		int i, j;
		bool change;
		for(i=length, change=true; i>1 && change; --i)
		{
			change=false;
			for(j=1; j<i; ++j)
				if LT(elem[j+1].key, elem[j].key)
				{
					swap(elem[j], elem[j+1]);
					change=true;
				}
		}
	}
};
#include "Func7-1.cpp"
void main()
{
	BubSort<ID> bs;
	bs.Creat_SeqFromFile("F7-1.txt");
	cout<<"≈≈–Ú«∞£∫"<<endl;
	bs.Traverse(Visit);
	bs.BubbleSort();
	cout<<endl<<"√∞≈›≈≈–Ú∫Û£∫"<<endl;
	bs.Traverse(Visit);
	cout<<endl;
}

