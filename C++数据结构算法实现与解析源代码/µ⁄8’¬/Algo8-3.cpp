//Algo8-3.cpp 败者树类
#include "C.h"
#include "C4-1.h"
template<typename D>class LoserTree
{
private:
	int k;
	int *ls;
	D *b;
	ifstream *fin;
	ofstream fout;
	void Adjust(int i)
	{
		int t;
		t=(i+k)/2;
		while(t>0)
		{
			if GT(b[i].key, b[ls[t]].key)
				swap(i, ls[t]);
			t=t/2;
		}
		ls[0]=i;
	}
	void CreateLoserTree()
	{
		int i;
		b[k].key=MIN;
		for(i=1; i<k; ++i)
			ls[i]=k;
		for(i=k-1; i>=0; --i)
			Adjust(i);
	}
public:
	LoserTree(int num)
	{
		k=num;
		ls=new int[k];
		b=new D[k+1];
		fin=new ifstream[k];
		char s[7]="F0.txt";
		for(int i=0; i<k; ++i)
		{
			s[1]=i+'0';
			fin[i].open(s, ios::in);
		}
		s[1]=k+'0';
		fout.open(s, ios::out);
	}
	~LoserTree()
	{
		delete[]ls;
		delete[]b;
		for(int i=0; i<k; ++i)
			fin[i].close();
		delete[]fin;
		fout.close();
	}
	void K_Merge()
	{
		int j=0;
		for(int i=0; i<k; ++i)
			InputFromFile(fin[i], b[i]);
		CreateLoserTree();
		
		char s[7]="F0.txt";
		s[1]=k+'0';
		cout<<"有序大文件"<<s<<"的数据为"<<endl;
		while(b[ls[0]].key!=MAX)
		{
			Visit(b[ls[0]]);
			if(++j%M==0)
				cout<<endl;
			OutputFile(fout, b[ls[0]]);
			if(!fin[ls[0]].eof())
				InputFromFile(fin[ls[0]], b[ls[0]]);
				
			else
				b[ls[0]].key=MAX;
			Adjust(ls[0]);
			
		}
	}
};
typedef int KeyType;
#include "Func8-1.cpp"
void main()
{
	int i;
	cout<<"请输入有序子文件的个数：";
	cin>>i;
	LoserTree<LD> lt(i);
	lt.K_Merge();
	cout<<endl;
}

