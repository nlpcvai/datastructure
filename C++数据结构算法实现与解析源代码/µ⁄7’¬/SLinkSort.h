//SLinkSort.h æ≤Ã¨¡¥±Ì≤Â»Î≈≈–Ú¿‡
#ifndef _SLINKSORT_H_
#define _SLINKSORT_H_
#include "SqTable.h"
template<typename D>class SLinkSort:public SqTable<D>
{
private:
	int *adr;
	void Sort()
	{
		int i=1, p=elem[0].next;
		while(p!=0)
		{
			adr[i++]=p;
			p=elem[p].next;
		}
	}
public:
	SLinkSort()
	{
		adr=NULL;
	}
	~SLinkSort()
	{
		if(adr!=NULL)
			delete[]adr;
	}
	void MakeTableSorted()
	{
		int i, p, q;
		elem[0].rc.key=INT_MAX;
		elem[0].next=0;
		for(i=1; i<=length; i++)
		{
			q=0;
			p=elem[0].next;
			while LQ(elem[p].rc.key, elem[i].rc.key)
			{
				q=p;
				p=elem[p].next;
			}
			elem[q].next=i;
			elem[i].next=p;
		}
	}
	void Arrange()
	{
		int i, p, q;
		p=elem[0].next;
		for(i=1; i<length; ++i)
		{
			while(p<i)
				p=elem[p].next;
			q=elem[p].next;
			if(p!=i)
			{
				swap(elem[p], elem[i]);
				elem[i].next=p;
			}                  
			p=q;
		}
	}
	void Rearrange()
	{
		int i, j, k;
		adr=new int[length+1];
		Sort();
		for(i=1; i<length; ++i)
			if(adr[i]!=i)
			{
				j=i;
				elem[0]=elem[i];
				while(adr[j]!=i)
				{
					k=adr[j];
					elem[j]=elem[k];
					adr[j]=j;
					j=k;
				}
				elem[j]=elem[0];
				adr[j]=j;
			}
	}
};
#endif

