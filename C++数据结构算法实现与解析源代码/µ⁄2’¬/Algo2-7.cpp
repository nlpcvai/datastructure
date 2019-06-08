//Algo2-7.cpp 用递归函数和非递归函数求解马踏棋盘问题
#include "C.h"
#include "SqStack.h"
#include "PosType.h"
#include "PosDirect.h"
class HORSE
{
private:
	int N;
	int **Chessboard;
	int number;
	ofstream fout;
	static PosType HTry[8];
	void HorseByRecursion(PosType Now, int count)
	{
		PosType Next;
		for(int m=0; m<8; m++)
		{
			Next=Now+HTry[m];
			if(Chessboard[Next.x][Next.y]==0)
			{
				Chessboard[Next.x][Next.y]=++count;
				if(count<N*N)
					HorseByRecursion(Next, count);
				else
				{
					++number;
					print();
				}
				Chessboard[Next.x][Next.y]=0;
				count--;
			}
		}
	}
	bool HorseByStack(PosDirect &start)
	{
		int count=1;
		bool flag;
		PosDirect next, now;
		SqStack<PosDirect> S(8);
		S.Push(start);
		Chessboard[start.pos.x][start.pos.y]=1;
		while(!S.StackEmpty())
		{
			S.Pop(now);
			flag=false;
			while(++now.direct<8)
			{
				next.pos=now.pos+HTry[now.direct];
				if(Chessboard[next.pos.x][next.pos.y]==0)
				{
					Chessboard[next.pos.x][next.pos.y]=++count;
					flag=true;
					S.Push(now);
					next.direct=-1;
					S.Push(next);
					if(count==N*N)
					{
						++number;
						print();
						return true;
					}
					break;
				}
			}
			if(!flag)
			{
				--count;
				Chessboard[now.pos.x][now.pos.y]=0;
			}
		}
		return false;
	}
	void print()
	{
		fout<<"解"<<number<<endl;
		for(int k=0; k<N; k++)
		{
			for(int n=0; n<N; n++)
				fout<<setw(3)<<Chessboard[k+2][n+2];
			fout<<endl;
		}
		fout<<endl;
	}
	void print1()
	{
		for(int k=0; k<N+4; k++)
		{
			for(int n=0; n<N+4; n++)
				cout<<setw(3)<<Chessboard[k][n];
			cout<<endl;
		}
	}
public:
	HORSE(int n, PosType Init, int j, char f[])
	{
		N=n;
		number=0;
		Chessboard=new int*[N+4];
		for(int i=0; i<N+4; i++)
		{
			Chessboard[i]=new int[N+4];
			for(int j=0; j<N+4; j++)
				if(i>=2 && i<=N+1 && j>=2 && j<=N+1)
					Chessboard[i][j]=0;
				else
					Chessboard[i][j]=-1;
		}
		cout<<"Chessboard数组："<<endl;
		print1();
		PosType p={1, 1};
		Init=Init+p;
		fout.open(f, ios::out);
		if(j==0)
		{
			PosDirect First;
			First.direct=-1;
			First.pos=Init;
			fout<<"利用栈求马踏棋盘的一个解："<<endl;
			HorseByStack(First);
		}
		if(j==1)
		{
			clock_t tstart=clock();
			Chessboard[Init.x][Init.y]=1;
			fout<<"用递归方法求马踏棋盘的所有解："<<endl;
			HorseByRecursion(Init, 1);
			double t=(clock()-tstart);
			cout<<"共有"<<number<<"个解，用时"<<t<<"毫秒。";
		}
		cout<<"结果在"<<f<<"中"<<endl;
	}
	~HORSE()
	{
		for(int i=0; i<N+4; i++)
			delete[]Chessboard[i];
		delete[]Chessboard;
		fout.close();
	}
};
PosType HORSE::HTry[8]={{2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, 
{-1, -2}, {1, -2}};
void main()
{
	char FileName[13]="马踏棋盘.txt";
	int i, n=5;
	PosType Init;
	cout<<"用递归方法求马踏棋盘的所有解请输入1；用栈求马踏棋盘的一个解请输入0：";
	cin>>i;
	cout<<"请在"<<n<<"×"<<n<<"的棋盘上输入马所在的行（1～"<<n<<"）列（1～"<<n<<"）：";
	cin>>Init.x>>Init.y;
	HORSE h(n, Init, i, FileName);
	
}

