//Algo2-5.cpp 用递归函数和非递归函数求解迷宫问题
#include "C.h"
#include "SqStack.h"
#include "PosType.h"
#include "PosDirect.h"
const int MAXLENGTH=10;
class MAZE
{
private:
	int maze[MAXLENGTH][MAXLENGTH];
	int row, col;
	int count;
	PosType begin, end;
	static PosType direc[4];
	void Try(PosType curpos, int curstep)
	{
		PosType nextpos;
		for(int i=0; i<=3; i++)
		{
			nextpos=curpos+direc[i];
			if(maze[nextpos.x][nextpos.y]==-1)
			{
				maze[nextpos.x][nextpos.y]=++curstep;
				if(nextpos==end)
				{
					cout<<"解"<<++count<<endl;
					Print();
				}
				else
					Try(nextpos, curstep);
				maze[nextpos.x][nextpos.y]=-1;
				
				curstep--;
			}
		}
	}
	void Print()const
	{
		for(int i=0; i<row; i++)
		{
			for(int j=0; j<col; j++)
				cout<<setw(3)<<maze[i][j];
			cout<<endl;
		}
	}
public:
	MAZE(char* FileName)
	{
		ifstream fin(FileName);
		fin>>row>>col;
		for(int i=0; i<row; i++)
			for(int j=0; j<col; j++)
				fin>>maze[i][j];
		cout<<"迷宫结构如下："<<endl;
		Print();
		fin>>begin.x>>begin.y;
		fin>>end.x>>end.y;
		cout<<"迷宫的起点：("<<begin.x<<", "<<begin.y<<')'<<endl;
		cout<<"迷宫的终点：("<<end.x<<", "<<end.y<<')'<<endl;
		fin.close();
	}
	bool MazePathByStack()
	{
		SqStack<PosDirect> S(8);
		PosDirect e;
		PosType curpos=begin;
		int curstep=1;
		do
		{
			if(maze[curpos.x][curpos.y]==-1)
			{
				maze[curpos.x][curpos.y]=curstep;
				e.pos=curpos;
				e.direct=0;
				S.Push(e);
				curstep++;
				if(curpos==end)
				{
					cout<<"此迷宫从入口到出口的一条路径如下："<<endl;
					Print();
					return true;
				}
				else
					curpos=curpos+direc[e.direct];
					
			}
			else
				if(!S.StackEmpty())
				{
					S.Pop(e);
					curstep--;
					while(e.direct==3 && !S.StackEmpty())
					{
						maze[e.pos.x][e.pos.y]=-2;
						
						S.Pop(e);
						curstep--;
					}
					if(e.direct<3)
					{
						e.direct++;
						S.Push(e);
						curstep++;
						curpos=e.pos+direc[e.direct];
						
					}
				}
		}while(!S.StackEmpty());
		cout<<"此迷宫没有从入口到出口的路径"<<endl;
		return false;
	}
	void MazePathByRecursion()
	{
		maze[begin.x][begin.y]=1;
		count=0;
		Try(begin, 1);
	}
};
PosType MAZE::direc[4]={{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
//类声明外分配空间和初始化。{行增量, 列增量}，移动方向依次为南东西北
void main()
{
	int i;
	MAZE M("F2-1.txt");
	cout<<"用递归方法求迷宫的所有解请输入1；用栈求迷宫的一个解请输入0：";
	cin>>i;
	if(i==0)
		M.MazePathByStack();
	else
		M.MazePathByRecursion();
}

