//Algo7-4.cpp œ£∂˚≈≈–Ú¿‡
#include "C.h"
#include "C4-1.h"
typedef int KeyType;
#include "SqTable.h"
template<typename D>class SheSort:public SqTable<D>
{
private:
	int n;
	int *dt;
	void ShellInsert(int dk)
	{
		for(int i=dk+1; i<=length; ++i)
			if LT(elem[i].key, elem[i-dk].key)
			{
				elem[0]=elem[i];
				for(int j=i-dk; j>0 && LT(elem[0].key, elem[j].key); j-=dk)
					elem[j+dk]=elem[j];
				elem[j+dk]=elem[0];
			}
	}
public:
	SheSort(int* DT, int N)
	{
		n=N;
		dt=new int[N];
		for(int i=0; i<N; i++)
			dt[i]=DT[i];
		assert(dt[n-1]==1);
	}
	~SheSort()
	{
		delete[]dt;
	}
	void ShellSort()
	{
		for(int k=0; k<n; ++k)
		{
			ShellInsert(dt[k]);
			cout<<endl<<"dt["<<k<<"]="<<dt[k]<<"£¨µ⁄"<<k+1<<"ÃÀ≈≈–ÚΩ·π˚£®Ωˆ ‰≥ˆπÿº¸◊÷£©£∫";
			for(int i=1; i<=length; i++)
				cout<<elem[i].key<<' ';
		}
	}
};
#include "Func7-1.cpp"
void main()
{
	int DT[3]={5, 3, 1};
	SheSort<ID> shs(DT, 3);
	shs.Creat_SeqFromFile("F7-1.txt");
	cout<<"≈≈–Ú«∞£∫"<<endl;
	shs.Traverse(Visit);
	shs.ShellSort();
	cout<<endl<<"œ£∂˚≈≈–Ú∫Û£∫"<<endl;
	shs.Traverse(Visit);
	cout<<endl;
}

