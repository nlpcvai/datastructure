//Algo2-9.cpp 带有效用的背包问题
#include "C.h"
class KNAP01
{
private:
	struct goods
	{
		int vaule;
		int weight;
	};
	int N, V, W;
	goods *G;
public:
	KNAP01(char *FileName)
	{
		ifstream fin(FileName);
		fin>>N;
		G=new goods[N+1];
		V=0;
		W=0;
		cout<<"物品件数="<<N<<"，每件物品的效用和权值：";
		G[0].vaule=G[0].weight=0;
		for(int i=1; i<=N; i++)
		{
			fin>>G[i].vaule>>G[i].weight;
			V+=G[i].vaule;
			W+=G[i].weight;
			cout<<'('<<G[i].vaule<<", "<<G[i].weight<<')';
		}
		cout<<endl<<"总效用V="<<V<<" 总权值W="<<W<<endl;
		fin.close();
	}
	~KNAP01()
	{
		delete[]G;
	}
	void Knapsack()
	{
		int i, j, k;
		int *B=new int[W+1];
		bool **t=new bool*[W+1];
		for(i=0; i<=W; i++)
			t[i]=new bool[N+1];
		for(i=1; i<=W; i++)
			for(j=1; j<=N; j++)
				t[i][j]=false;
		for(i=0; i<=W; i++)
			B[i]=0;
		for(j=1; j<=N; j++)
		{
			cout<<"物品数j="<<j<<' ';
			for(i=W; i>=G[j].weight; i--)
			{
				if(B[i-G[j].weight]+G[j].vaule>B[i])
				{
					B[i]=B[i-G[j].weight]+G[j].vaule;
					for(k=1; k<N; k++)
						t[i][k]=t[i-G[j].weight][k];
					t[i][j]=true;
				}
				cout<<"B["<<i<<"]="<<B[i]<<' ';
			}
			cout<<endl;
		}
		for(i=1; i<=W; i++)
		{
			for(j=1; j<=N; j++)
				cout<<" t["<<setw(2)<<i<<"]["<<j<<"]="<<setw(5)<<boolalpha<<t[i][j];
			cout<<endl;
		}
		for(i=0; i<=W; i++)
		{
			cout<<"B["<<i<<"]="<<B[i]<<' ';
			if(i%6==5)
				cout<<endl;
		}
		delete[]B;
		for(i=0; i<=W; i++)
			delete[]t[i];
		delete[]t;
	}
};
void main()
{
	KNAP01 k("F2-3.txt");
	k.Knapsack();
}

