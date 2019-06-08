//Algo5-3.cpp AdjListGraph.h类对象将无向图构造为生成森林，并以孩子-兄弟二叉链表存储之
#include "C5-1.h"
#include "AdjListGraph.h"
#include "CSTree.h"
template<typename VerT, typename ArcT>class DFST
{
private:
	bool *visited;
	void DFSTree(const AdjListGraph<VerT, ArcT> &G, int v, CSNode<VerT>* &t)
	{
		bool first=true;
		int w;
		CSNode<VerT> *p, *q;
		visited[v]=true;
		for(w=G.FirstAdjVex(v); w>=0; w=G.NextAdjVex(v, w))
			if(!visited[w])
			{
				p=new CSNode<VerT>;
				p->data=G.GetVex(w);
				p->firstchild=NULL;
				p->nextsibling=NULL;
				if(first)
				{
					t->firstchild=p;
					first=false;
				}
				else
					q->nextsibling=p;
				
				q=p;
				DFSTree(G, w, q);
			}
	}
public:
	CSTree<VerT> t;
	void DFSForest(const AdjListGraph<VerT, ArcT> &G)
	{
		CSNode<VerT> *p, *q;
		int v;
		visited=new bool[G.GetVexNumOrArcNum(0)];
		for(v=0; v<G.GetVexNumOrArcNum(0); ++v)
			visited[v]=false;
		for(v=0; v<G.GetVexNumOrArcNum(0); ++v)
			if(!visited[v])
			{
				p=new CSNode<VerT>;
				p->data=G.GetVex(v);
				p->firstchild=NULL;
				p->nextsibling=NULL;
				if(t.root==NULL)
					t.root=p;
				else
					q->nextsibling=p;
					
				q=p;
				DFSTree(G, v, p);
			}
		delete[]visited;
	}
};
#include "Func5-1.cpp"
#include "Func5-5.cpp"
void Visit1(CSNode<V>* tt)
{
	cout<<tt->data.name<<' ';
}
void main()
{
	AdjListGraph<V, A> g;
	DFST<V, A> tr;
	char filename[13];
	cout<<"请输入数据文件名（F5-7.txt）：";
	cin>>filename;
	g.CreateFromFile(filename);
	g.Display();
	tr.DFSForest(g);
	cout<<"先根遍历生成森林tr："<<endl;
	tr.t.PreOrderTraverse(Visit1);
	cout<<endl<<"后根遍历生成森林tr："<<endl;
	tr.t.PostOrderTraverse(Visit1);
	cout<<endl;
}

