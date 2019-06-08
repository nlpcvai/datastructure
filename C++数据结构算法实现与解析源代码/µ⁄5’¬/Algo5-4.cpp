//Algo5-4.cpp 构造最小生成树
const int MAX_VERTEX_NUM=6;
#include "C5-1.h"
#include "MatrixGraph.h"
template<typename VerT, typename ArcT>class MSTree:
public MatrixGraph<VerT, ArcT>
{
private:
	struct minside
	{
		int adjvex;
		VRType lowcost;
	};
	int minimum(minside SZ[])
	{
		int i=0, j, k, min;
		while(SZ[i].lowcost==0)
			i++;
		min=SZ[i].lowcost;
		k=i;
		for(j=i+1; j<VexNum; j++)
			if(SZ[j].lowcost>0 && SZ[j].lowcost<min)
			{
				min=SZ[j].lowcost;
				k=j;
			}
		return k;
	}
	struct side
	{
		int a, b;
		VRType weight;
	};
	struct cmp
	{
		bool operator()(const side &a, const side &b)const
		{
			return a.weight>b.weight;
		}
	};
public:
	void MiniSpanTree_PRIM(int k)
	{
		if(VexNum>0 && Weight && !Directed)
		{
			int i, j, m;
			minside closedge[MAX_VERTEX_NUM];
			for(j=0; j<VexNum; ++j)
			{
				closedge[j].adjvex=k;
				closedge[j].lowcost=arcs[k][j].adj;
			}
			closedge[k].lowcost=0;
			cout<<"普里姆算法构造的最小代价生成树的各条边为"<<endl;
			for(i=1; i<VexNum; ++i)
			{
				m=minimum(closedge);
				cout<<GetVex(closedge[m].adjvex).name<<'-'<<GetVex(m).name<<endl;
				
				closedge[m].lowcost=0;
				for(j=0; j<VexNum; ++j)
					if(arcs[m][j].adj<closedge[j].lowcost)
					{
						closedge[j].adjvex=m;
						closedge[j].lowcost=arcs[m][j].adj;
					}
			}
		}
	}
	void Kruskal()
	{
		if(VexNum>0 && Weight && !Directed)
		{
			priority_queue<side, vector<side>, cmp> q;
			
			int i, j, k, set[MAX_VERTEX_NUM];
			side se;
			for(i=0; i<VexNum; ++i)
				for(j=i+1; j<VexNum; ++j)
					if(arcs[i][j].adj<INFINITY)
					{
						se.a=i;
						se.b=j;
						se.weight=arcs[i][j].adj;
						q.push(se);
					}
			for(i=0; i<VexNum; i++)
				set[i]=i;
			cout<<"克鲁斯卡尔算法构造的最小代价生成树的各条边为"<<endl;
			k=0;
			while(k<VexNum-1)
			{
				if(!q.empty())
				{
					se=q.top();
					q.pop();
					if(set[se.a]!=set[se.b])
					{
						cout<<GetVex(se.a).name<<'-'<<GetVex(se.b).name<<endl;
						j=set[se.b];
						for(i=0; i<VexNum; i++)
							if(set[i]==j)
								set[i]=set[se.a];
						k++;
					}
				}
				else
				{
					cout<<"无法构成最小生成树。"<<endl;
					break;
				}
			}
		}
	}
};
#include "Func5-1.cpp"
#include "Func5-2.cpp"
void main()
{
	MSTree<V, A> m;
	m.CreateFromFile("F5-8.txt");
	m.Display();
	m.MiniSpanTree_PRIM(0);
	m.Kruskal();
}

