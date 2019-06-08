//AGraph.h 图抽象类的定义
#ifndef _AGRAPH_H_
#define _AGRAPH_H_
#include "C.h"
template<typename VerT>class AGraph
{
private:
	int LocateVex(VerT u)const;
	void DFS(int i, void(*visit)(VerT), bool Visited[])
	{
		Visited[i]=true;
		visit(GetVex(i));
		for(int j=FirstAdjVex(i); j>=0; j=NextAdjVex(i, j))
		
			if(!Visited[j])
				DFS(j, visit, Visited);
				
	}
protected:
	int ArcNum;
	bool Weight;
	bool Directed;
public:
	void CreateFromFile(char* FileName);
	bool PutVex(VerT v, VerT value);
	virtual int FirstAdjVex(int i)const=0;
	
	virtual int NextAdjVex(int i, int j)const=0;
	
	void InsertVex(VerT v);
	bool DeleteVex(VerT v);
	bool InsertArc(VerT v, VerT w);
	bool DeleteArc(VerT v, VerT w);
	void Display()const;
	void DFSTraverse(void(*visit)(VerT))
	{
		int i;
		bool *Visited=new bool[GetVexNumOrArcNum(0)];
		for(i=0; i<GetVexNumOrArcNum(0); i++)
			Visited[i]=false;
		for(i=0; i<GetVexNumOrArcNum(0); i++)
			if(!Visited[i])
				DFS(i, visit, Visited);
		cout<<endl;
		delete[]Visited;
	}
	void BFSTraverse(void(*visit)(VerT))
	{
		int i, j, k;
		bool *Visited=new bool[GetVexNumOrArcNum(0)];
		queue<int> q;
		for(i=0; i<GetVexNumOrArcNum(0); i++)
			Visited[i]=false;
		for(i=0; i<GetVexNumOrArcNum(0); i++)
			if(!Visited[i])
			{
				Visited[i]=true;
				visit(GetVex(i));
				q.push(i);
				while(!q.empty())
				{
					j=q.front();
					q.pop();
					for(k=FirstAdjVex(j); k>=0; k=NextAdjVex(j, k))
					
						if(!Visited[k])
						{
							Visited[k]=true;
							visit(GetVex(k));
							q.push(k);
						}
				}
			}
		cout<<endl;
		delete[]Visited;
	}
	virtual int GetVexNumOrArcNum(int i)const=0;
	bool GetDirectedOrWeight(int i)const
	{
		if(i==0)
			return Directed;
		else
			return Weight;
	}
	virtual VerT GetVex(int i)const=0;
};
#endif

