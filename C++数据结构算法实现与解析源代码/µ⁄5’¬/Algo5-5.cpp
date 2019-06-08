//Algo5-5.cpp 求连通图关节点的算法
#include "C5-1.h"
#include "AdjListGraph.h"
template<typename VerT, typename ArcT>class Articul
{
private:
	int count, lowcount;
	int *low, *lowOrder;
	int *visited;
	void DFSArticul(const AdjListGraph<VerT, ArcT> &G, int v0)
	{
		int min, w;
		list<AdjListGraph<VerT, ArcT>::ArcTNode>::const_iterator p;
		visited[v0]=min=++count;
		for(p=G.vexs[v0].arcs.begin(); p!=G.vexs[v0].arcs.end(); p++)
		{
			w=p->adjvex;
			if(visited[w]==0)
			{
				DFSArticul(G, w);
				
				if(low[w]<min)
					min=low[w];
				else if(low[w]>=visited[v0])
					cout<<v0<<' '<<G.vexs[v0].vex.name<<endl;
			}
			else if(visited[w]<min)
				min=visited[w];
		}
		low[v0]=min;
		lowOrder[v0]=lowcount++;
		
	}
public:
	void FindArticul(const AdjListGraph<VerT, ArcT> &G)
	{
		int i, v;
		list<AdjListGraph<VerT, ArcT>::ArcTNode>::const_iterator p;
		count=1;
		lowcount=1;
		visited=new int[G.vexs.size()];
		low=new int[G.vexs.size()];
		lowOrder=new int[G.vexs.size()];
		visited[0]=count;
		for(i=1; i<G.GetVexNumOrArcNum(0); ++i)
			visited[i]=0;
		p=G.vexs[0].arcs.begin();
		v=p->adjvex;
		DFSArticul(G, v);
		if(count<G.GetVexNumOrArcNum(0))
		{
			cout<<"0 "<<G.vexs[0].vex.name<<endl;
			p++;
			while(p!=G.vexs[0].arcs.end())
			{
				v=p->adjvex;
				if(visited[v]==0)
					DFSArticul(G, v);
				p++;
			}
		}
		cout<<" i G.vertices[i].data visited[i] low[i] lowOrder[i]"<<endl;
		cout<<setw(2)<<0<<setw(10)<<G.vexs[0].vex.name;
		cout<<setw(15)<<visited[0]<<endl;
		for(i=1; i<G.GetVexNumOrArcNum(0); ++i)
			cout<<setw(2)<<i<<setw(10)<<G.vexs[i].vex.name<<setw(15)
			<<visited[i]<<setw(9)<<low[i]<<setw(10)<<lowOrder[i]<<endl;
		delete[]visited;
		delete[]low;
		delete[]lowOrder;
	}
};
#include "Func5-1.cpp"
#include "Func5-5.cpp"
void main()
{
	AdjListGraph<V, A> g;
	Articul<V, A> a;
	g.CreateFromFile("F5-9.txt");
	g.Display();
	cout<<"输出关节点："<<endl;
	a.FindArticul(g);
}

