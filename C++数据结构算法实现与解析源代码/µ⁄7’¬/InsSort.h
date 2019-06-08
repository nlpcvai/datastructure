//InsSort.h ≤Â»Î≈≈–Ú¿‡
#ifndef _INSSORT_H_
#define _INSSORT_H_
#include "SqTable.h"
template<typename D>class InsSort:public SqTable<D>
{
public:
	void InsertSort()
	{
		int i, j;
		for(i=2; i<=length; ++i)
			if LT(elem[i].key, elem[i-1].key)
			{
				elem[0]=elem[i];
				for(j=i-1; LT(elem[0].key, elem[j].key); --j)
				
					elem[j+1]=elem[j];
				elem[j+1]=elem[0];
			}
	}
	void BInsertSort()
	{
		int i, j, m, low, high;
		for(i=2; i<=length; ++i)
			if LT(elem[i].key, elem[i-1].key)
			{
				elem[0]=elem[i];
				low=1;
				high=i-1;
				while(low<=high)
				{
					m=(low+high)/2;
					if LT(elem[0].key, elem[m].key)
						high=m-1;
					else
						low=m+1;
				}
				for(j=i-1; j>=high+1; --j)
					elem[j+1]=elem[j];
				elem[high+1]=elem[0];
			}
	}
	void P2_InsertSort()
	{
		int i, j, first, final, mid;
		D *d;
		d=new D[length];
		d[0]=elem[1];
		first=final=0;
		for(i=2; i<=length; ++i)
		{
			if(first>final)
				j=length;
			else
				j=0;
			mid=(first+final+j)/2%length;
			if(elem[i].key<d[mid].key)
			{
				j=first;
				first=(first-1+length)%length;
				while(elem[i].key>d[j].key)
				{
					d[(j-1+length)%length]=d[j];
					j=(j+1)%length;
				}
				d[(j-1+length)%length]=elem[i];
			}
			else
			{
				j=final++;
				while(elem[i].key<d[j].key)
				{
					d[(j+1)%length]=d[j];
					j=(j-1+length)%length;
				}
				d[(j+1)%length]=elem[i];
				
			}
		}
		for(i=1; i<=length; i++)
			elem[i]=d[(first+i-1)%length];
		delete[]d;
	}
};
#endif

