//SqTable.h 静态查找表类（SqTable类）
#ifndef _SQTABLE_H_
#define _SQTABLE_H_
template<typename D>class SqTable
{
protected:
	D *elem;
	int length;
public:
	SqTable()
	{
		elem=NULL;
		length=0;
	}
	~SqTable()
	{
		if(elem!=NULL)
			delete[]elem;
	}
	void Creat_SeqFromFile(char* FileName)
	{
		ifstream fin(FileName);
		fin>>length;
		elem=new D[length+1];
		assert(elem!=NULL);
		for(int i=1; i<=length; i++)
			InputFromFile(fin, elem[i]);
		fin.close();
	}
	void OutputToFile(char* FileName)const
	{
		ofstream fout(FileName);
		if(elem!=NULL)
			for(int i=1; i<=length; i++)
				OutputFile(fout, elem[i]);
		fout.close();
	}
	int Search_Seq(KeyType k)const
	{
	 
		int i;
		elem[0].key=k;
		for(i=length; !EQ(k, elem[i].key); --i);
		return i;
	}
	int Search_Bin(KeyType k)const
	{
	 
		int mid, low=1, high=length;
		while(low<=high)
		{
			mid=(low+high)/2;
			if EQ(k, elem[mid].key)
				return mid;
			else if LT(k, elem[mid].key)
				high=mid-1;
			else
				low=mid+1;
		}
		return 0;
	}
	bool GetElem(int i, D &e)const
	{
		if(i<1 || i>length)
			return false;
		e=elem[i];
		return true;
	}
	void Traverse(void(*visit)(D*))const
	{
		for(int i=1; i<=length; i++)
			visit(&elem[i]);
	}
};
#endif

