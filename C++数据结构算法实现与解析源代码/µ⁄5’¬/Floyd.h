//Floyd.h 弗洛伊德最短路径类（Floyd类）
#ifndef _FLORD_H_
#define _FLORD_H_
#include "MatrixGraph.h"
template<typename VerT, typename ArcT>class Floyd
{
private:
	bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	
	VRType D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	MatrixGraph<VerT, ArcT> G;
	void ShortestPath_FLOYD()
	{
	 
		int u, v, w, i;
		for(v=0; v<G.GetVexNumOrArcNum(0); v++)
			for(w=0; w<G.GetVexNumOrArcNum(0); w++)
			{
				D[v][w]=G.GetArc(v, w).adj;
				for(u=0; u<G.GetVexNumOrArcNum(0); u++)
					P[v][w][u]=false;
				if(D[v][w]<INFINITY)
					P[v][w][v]=P[v][w][w]=true;
			}
			for(u=0; u<G.GetVexNumOrArcNum(0); u++)
				for(v=0; v<G.GetVexNumOrArcNum(0); v++)
					for(w=0; w<G.GetVexNumOrArcNum(0); w++)
						if(D[v][u]<INFINITY && D[u][w]<INFINITY && D[v][u]+D[u][w]<D[v][w])
						{
							D[v][w]=D[v][u]+D[u][w];
							for(i=0; i<G.GetVexNumOrArcNum(0); i++)
								P[v][w][i]=P[v][u][i] || P[u][w][i];
								
						}
	}
public:
	Floyd(MatrixGraph<VerT, ArcT> g)
	{
		G=g;
		ShortestPath_FLOYD();
	}
	void DisplayD()const
	{
		cout<<"D矩阵："<<endl;
		for(int i=0; i<G.GetVexNumOrArcNum(0); i++)
		{
			for(int j=0; j<G.GetVexNumOrArcNum(0); j++)
				cout<<setw(6)<<D[i][j];
			cout<<endl;
		}
	}
	void Path(int i, int j)const
	{
		bool p[MAX_VERTEX_NUM];
		int k, n, m=i;
		VRType a;
		if(i!=j)
		{
			for(k=0; k<G.GetVexNumOrArcNum(0); k++)
				p[k]=P[i][j][k];
			cout<<"P["<<i<<"]["<<j<<"]=";
			for(k=0; k<G.GetVexNumOrArcNum(0); k++)
				cout<<p[k]<<' ';
			cout<<endl;
			if(D[i][j]<INFINITY)
			{
				while(m!=j)
				{
					a=INFINITY;
					for(k=0; k<G.GetVexNumOrArcNum(0); k++)
						if(G.GetArc(m, k).adj<a && p[k])
						{
							a=G.GetArc(m, k).adj;
							n=k;
						}
					cout<<G.GetVex(n).name;
					if(n!=j)
						cout<<"→";
					p[n]=false;
					m=n;
				}
				cout<<"："<<D[i][j]<<endl;
			}
			else
				cout<<G.GetVex(i).name<<"到"<<G.GetVex(j).name<<"没有路径可通。"<<endl;
		}
	}
};
#endif

