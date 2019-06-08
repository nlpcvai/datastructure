//Algo8-4.cpp 置换-选择排序类
#include "C.h"
#include "C4-1.h"
template<typename D>class Replace_Select
{
private:
	struct WA
	{
		D rec;
		int rnum;
	};
	int k;
	WA *wa;
	int *ls;
	void Select_MiniMax(int q)
	{
		for(int t=(k+q)/2; t>0; t=t/2)
			if(LT(wa[ls[t]].rnum,wa[q].rnum)||EQ(wa[ls[t]].rnum,wa[q].rnum) && LT(wa
			[ls[t]].rec.key, wa[q].rec.key))
				swap(q, ls[t]);
		ls[0]=q;
	}
	void Construct_Loser(ifstream &f)
	{
	 
		int i;
		for(i=0; i<k; ++i)
			wa[i].rnum=ls[i]=0;
		for(i=k-1; i>=0; --i)
		{
			InputFromFile(f, wa[i].rec);
			wa[i].rnum=1;
			Select_MiniMax(i);
		}
	}
	void get_run(int rc, int &rmax, ifstream &fi, ofstream &fo)
	{
		int q;
		KeyType minimax;
		while(wa[ls[0]].rnum==rc)
		{
			q=ls[0];
			minimax=wa[q].rec.key;
			OutputFile(fo, wa[q].rec);
			Visit(wa[q].rec);
			InputFromFile(fi, wa[q].rec);
			if(fi.eof())
				wa[q].rnum=rmax+1;
			else
			{
				if LT(wa[q].rec.key, minimax)
				{
					rmax=rc+1;
					wa[q].rnum=rmax;
				}
				else
					wa[q].rnum=rc;
			}
			Select_MiniMax(q);
		}
	}
public:
	Replace_Select(int num)
	{
		k=num;
		ls=new int[k];
		wa=new WA[k];
	}
	~Replace_Select()
	{
		delete[]ls;
		delete[]wa;
	}
	void Replace_Selection(char* FileName)
	{
		ifstream fin(FileName);
		int rc, rmax;
		char s[7]="F0.txt";
		Construct_Loser(fin);
		rc=rmax=1;
		do
		{
			s[1]=rc-1+'0';
			ofstream fout(s);
			cout<<s<<"的内容为";
			get_run(rc, rmax, fin, fout);
			cout<<endl;
			fout.close();
			rc=wa[ls[0]].rnum;
		}while(rc<=rmax);
		cout<<"共产生"<<rc-1<<"个初始归并段文件"<<endl;
	}
};
typedef int KeyType;
#include "Func8-1.cpp"
void main()
{
	Replace_Select<LD> rs(6);
	rs.Replace_Selection("F8-2.txt");
	
}

