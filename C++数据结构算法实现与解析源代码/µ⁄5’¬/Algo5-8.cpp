//Algo5-8.cpp 迪杰斯特拉算法，从某个源点到其余各顶点的最短路径
const int MAX_VERTEX_NUM=6;
#include "C5-1.h"
#include "MatrixGraph.h"
template<typename VerT, typename ArcT>class ShortestPath
{
private:
	bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	VRType D[MAX_VERTEX_NUM];
	void Path(const MatrixGraph<VerT, ArcT> &G, int v0, int v)
	{
		bool path[MAX_VERTEX_NUM];
		VRType min;
		int i, j=0, k, m;
		for(i=0; i<G.GetVexNumOrArcNum(0); ++i)
		{
			path[i]=P[v][i];
			if(path[i])
				j++;
		}
		path[v0]=false;
		if(j!=0)
			j--;
		k=v0;
		while(j>0)
		{
			min=INFINITY;
			cout<<G.GetVex(k).name<<"→";
			for(i=0; i<G.GetVexNumOrArcNum(0); ++i)
				if(path[i]&&G.GetArc(k,i).adj<min)
				{
					min=G.GetArc(k, i).adj;
					m=i;
				}
			k=m;
			path[k]=false;
			j--;
		}
		if(k!=v0)
			cout<<G.GetVex(k).name<<endl;
	}
public:
	void ShortestPath_DIJ(const MatrixGraph<VerT, ArcT> &G, int v0)
	{
	 
	 
		int v, w, i, j;
		VRType min;
		bool final[MAX_VERTEX_NUM];
		
		for(v=0; v<G.GetVexNumOrArcNum(0); ++v)
		{
			final[v]=false;
			D[v]=G.GetArc(v0, v).adj;
			for(w=0; w<G.GetVexNumOrArcNum(0); ++w)
				P[v][w]=false;
			if(D[v]<INFINITY)
				P[v][v0]=P[v][v]=true;
				
		}
		D[v0]=0;
		final[v0]=true;
		for(i=1; i<G.GetVexNumOrArcNum(0); ++i)
		{
			min=INFINITY;
			for(w=0; w<G.GetVexNumOrArcNum(0); ++w)
				if(!final[w] && D[w]<min)
				{
					v=w;
					min=D[w];
				}
			final[v]=true;
			for(w=0; w<G.GetVexNumOrArcNum(0); ++w)
			
				if(!final[w] && min<INFINITY && G.GetArc(v, w).adj<INFINITY && 
				(min+G.GetArc(v, w).adj<D[w]))
				{
					D[w]=min+G.GetArc(v, w).adj;
					for(j=0; j<G.GetVexNumOrArcNum(0); ++j)
					
						P[w][j]=P[v][j];
					P[w][w]=true;
				}
		}
		cout<<"最短路径数组P[i][j]如下："<<endl;
		for(i=0; i<G.GetVexNumOrArcNum(0); ++i)
		{
			for(j=0; j<G.GetVexNumOrArcNum(0); ++j)
				cout<<setw(3)<<P[i][j];
			cout<<endl;
		}
		cout<<G.GetVex(v0).name<<"到各顶点的最短路径依次经过的顶点为"<<endl;
		for(i=0; i<G.GetVexNumOrArcNum(0); ++i)
			Path(G, v0, i);
		cout<<G.GetVex(v0).name<<"到各顶点的最短路径长度为"<<endl;
		for(i=0; i<G.GetVexNumOrArcNum(0); ++i)
			if(i!=v0)
			{
				cout<<G.GetVex(v0).name<<"→"<<G.GetVex(i).name<<"：";
				if(D[i]<INFINITY)
					cout<<D[i]<<endl;
				else
					cout<<"∞"<<endl;
			}
	}
};
#include "Func5-1.cpp"
#include "Func5-2.cpp"
void main()
{
	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;
	g.CreateFromFile("F5-12.txt");
	g.Display();
	m.ShortestPath_DIJ(g, 0);
}

