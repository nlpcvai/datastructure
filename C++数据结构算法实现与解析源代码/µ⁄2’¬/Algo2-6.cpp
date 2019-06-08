//Algo2-6.cpp 用递归函数和非递归函数求解皇后问题
#include "C.h"
class QUEUE
{
private:
	int *solution;
	int **MarkArray;
	int N;
	ofstream fout;
	void Mark(int m, int i, bool flag)
	{
		int j, n, k;
		if(flag)
		{
			j=-1;
			n=m;
		}
		else
		{
			j=m;
			n=-1;
		}
		for(k=0; k<N; k++)
			if(MarkArray[m][k]==j)
				MarkArray[m][k]=n;
		for(k=m+1;k<N;k++)
		{
			if(MarkArray[k][i]==j)
				MarkArray[k][i]=n;
			if((k+i-m)>=0 && (k+i-m)<N&&MarkArray[k][k+i-m]==j)
				MarkArray[k][k+i-m]=n;
			if((i+m-k)>=0 && (i+m-k)<N&&MarkArray[k][(i+m-k)]==j)
				MarkArray[k][i+m-k]=n;
		}
	}
	void PutOut()
	{
		int i, j;
		fout<<"解"<<number<<"："<<endl;
		fout<<"solution[]=";
		for(j=0; j<N; j++)
			fout<<solution[j]<<' ';
		fout<<endl<<"根据solution[]，输出皇后在棋盘中的位置："<<endl;
		for(j=0; j<N; j++)
		{
			for(i=0; i<N; i++)
				if(i==solution[j])
					fout<<" Q";
				else
					fout<<" X";
			fout<<endl;
		}
		fout<<"MarkArray[][]="<<endl;
		for(j=0; j<N; j++)
		{
			for(i=0; i<N; i++)
				fout<<setw(2)<<MarkArray[j][i];
			fout<<endl;
		}
	}
public:
	int number;
	QUEUE(int n, char f[])
	{
		N=n;
		number=0;
		solution=new int[N];
		MarkArray=new int*[N];
		for(int i=0; i<N; i++)
		{
			MarkArray[i]=new int[N];
			for(int j=0; j<N; j++)
				MarkArray[i][j]=-1;
		}
		fout.open(f, ios::out);
		fout<<N<<"皇后问题的所有解："<<endl;
	}
	~QUEUE()
	{
		for(int i=0; i<N; i++)
			delete[]MarkArray[i];
		delete[]MarkArray;
		delete[]solution;
		fout.close();
	}
	void QueenByRecursion(int m)
	{
		if(m<N)
			for(int i=0; i<N; i++)
			{
				if(MarkArray[m][i]==-1)
				{
					solution[m]=i;
					Mark(m, i, true);
					QueenByRecursion(m+1);
					Mark(m, i,false);
				}
			}
		else
		{
			number++;
			PutOut();
		}
	}
	void QueenNoRecursion()
	{
		int i, j;
		i=0;
		j=0;
		while(i>=0)
		{
			while(j<N)
			{
				if(MarkArray[i][j]==-1)
					break;
				j++;
			}
			if(j<N)
			{
				solution[i]=j;
				Mark(i, j, true);
				if(i==N-1)
				{
					number++;
					PutOut();
					Mark(i, j, false);
					i--;
					j=solution[i];
					Mark(i, j, false);
					j++;
				}
				else
				{
					i++;
					j=0;
				}
			}
			else
			{
				i--;
				if(i>=0)
				{
					j=solution[i];
					Mark(i, j, false);
					j++;
				}
			}
		}
	}
};
void main()
{
	char FileName[13]="Queen.txt";
	int m, n=4;
	QUEUE q(n, FileName);
	cout<<"求解皇后问题：欲采用递归方法，请输入1；否则输入0：";
	cin>>m;
	if(m>0)
		q.QueenByRecursion(0);
	else
		q.QueenNoRecursion();
	cout<<n<<"皇后问题共有"<<q.number<<"个解，存于文件"<<FileName<<"中。"<<endl;
}

