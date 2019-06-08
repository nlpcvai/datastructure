//Algo7-6.cpp ∂—≈≈–Ú¿‡
#include "C.h"
#include "C4-1.h"
typedef int KeyType;
#include "SqTable.h"
template<typename D>class HSort:public SqTable<D>
{
private:
	void HeapAdjust(int low, int high, bool flag)
	{
	 
		int j;
		elem[0]=elem[low];
		for(j=2*low; j<=high; j*=2)
		{
			if(flag)
			{
				if(j<high&&LT(elem[j].key, elem[j+1].key))
					++j;
				if(!LT(elem[0].key, elem[j].key))
					break;
			}
			else
			{
				if(j<high&&GT(elem[j].key, elem[j+1].key))
					++j;
				if(!GT(elem[0].key, elem[j].key))
					break;
			}
			elem[low]=elem[j];
			low=j;
		}
		elem[low]=elem[0];
	}
public:
	void HeapSort(bool flag)
	{
		int i;
		for(i=length/2; i>=1; --i)
			HeapAdjust(i,length,flag);
		for(i=length; i>=2; --i)
		{
			swap(elem[1], elem[i]);
			
			HeapAdjust(1, i-1, flag);
		}
	}
};
#include "Func7-1.cpp"
void main()
{
	HSort<ID> hs[2];
	string s[2]={"¥Û", "–°"};
	for(int i=0; i<=1; i++)
	{
		hs[i].Creat_SeqFromFile("F7-1.txt");
		if(i==0)
		{
			cout<<"≈≈–Ú«∞£∫"<<endl;
			hs[i].Traverse(Visit);
		}
		hs[i].HeapSort(i==0);
		cout<<endl<<s[i]<<"∂•∂—≈≈–Ú∫Û£∫"<<endl;
		hs[i].Traverse(Visit);
	}
	cout<<endl;
}

