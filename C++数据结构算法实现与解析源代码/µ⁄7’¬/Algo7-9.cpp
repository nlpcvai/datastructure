//Algo7-9.cpp 静态链式基数排序类
#include "C.h"
typedef string KeyType;
#include "SLinkSort.h"
const int RADIX=5;
template<typename D>class LinkRadix:public SLinkSort<D>
{
private:
	int f[RADIX+1], e[RADIX+1];
	int keylength;
	int ord(char c)
	{
		return c-'`';
	}
	void Distribute(int i)
	{
	 
	 
		int j, p;
		for(j=0; j<=RADIX; ++j)
			f[j]=0;
		for(p=elem[0].next; p!=0; p=elem[p].next)
		{
			if(elem[p].rc.key.length()<=i)
				j=0;
			else
				j=ord(elem[p].rc.key[i]);
				
			if(!f[j])
				f[j]=p;
			else
				elem[e[j]].next=p;
			e[j]=p;
		}
		cout<<"按key["<<i<<"]分配后：";
		Print();
		cout<<"f[]=";
		for(j=0; j<=RADIX; ++j)
			cout<<setw(3)<<f[j];
		cout<<endl<<"e[]=";
		for(j=0; j<=RADIX; ++j)
			if(f[j])
				cout<<setw(3)<<e[j];
			else
				cout<<setw(3)<<0;
		cout<<endl;
	}
	void Collect()
	{
		
		int j, t;
		for(j=0; f[j]==0; j++);
		elem[0].next=f[j];
		t=e[j];
		while(j<RADIX)
		{
			for(j++; j<=RADIX-1 && f[j]==0; j++);
			if(f[j])
			{
				elem[t].next=f[j];
				t=e[j];
			}
		}
		elem[t].next=0;
		cout<<"收集后："<<endl;
		Print();
		PrintLL();
	}
	void PrintLL()
	{
		int i=elem[0].next;
		cout<<"按静态链表顺序输出关键字："<<endl;
		while(i)
		{
			cout<<elem[i].rc.key<<' ';
			i=elem[i].next;
		}
		cout<<endl;
	}
	void Print()
	{
		cout<<"elem[0].next="<<elem[0].next<<endl;
		for(int i=1; i<=length; i++)
			cout<<"i="<<i<<" key="<<setiosflags(ios::left)
			<<setw(3)<<elem[i].rc.key<<" next="<<elem[i].next<<endl;
	}
public:
	void Creat_SeqFromFile(char* FileName)
	{
		SqTable<D>::Creat_SeqFromFile(FileName);
		keylength=0;
		elem[0].next=1;
		for(int i=1; i<=length; i++)
		{
			elem[i].next=i+1;
			if(elem[i].rc.key.length()>keylength)
				keylength=elem[i].rc.key.length();
		}
		elem[length].next=0;
	}
	void RadixSort()
	{
		int i;
		for(i=keylength-1; i>=0; --i)
		{
			Distribute(i);
			Collect();
		}
	}
	void Print3()
	{
		cout<<"elem[0].next="<<elem[0].next<<endl;
	}
};
#include "Func7-3.cpp"
void main()
{
	LinkRadix<LR> lr;
	lr.Creat_SeqFromFile("F7-2.txt");
	cout<<"静态链表排序前："<<endl;
	lr.Print3();
	lr.Traverse(Visitn);
	lr.RadixSort();
	lr.Rearrange();
	cout<<"Rearrange()重排数据后："<<endl;
	lr.Traverse(Visit);
}

