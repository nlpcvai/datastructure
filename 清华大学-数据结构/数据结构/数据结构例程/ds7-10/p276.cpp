#include "stack.h"
#include "P267E.cpp"


struct BiEdge
{
		BiEdge(){a=b=0;};
		BiEdge(int p1, int p2):a(p1),b(p2){};
		void SetVertex(int p1, int p2){a=p1;b=p2;};
		int operator==(BiEdge e)
		{
		  return ((a==e.a)&&(b==e.b)) || ((a==e.b)&&(b==e.a));
		};
		int a,b;
};
ostream& operator <<(ostream& strm, BiEdge& e)
{
  strm<<"("<<e.a<<","<<e.b<<")";
  return strm;
};

static int * dfn,*low;

//static int dfn[MaxNumVertices];
//static int low[MaxNumVertices];


static int num;


static  Stack< BiEdge >   S(MaxNumEdges);
static int min2(const int a, const int b)
{
	return a>b?b:a;
};



template <class NameType, class DistType> 
void Graph<NameType,DistType>::DfnLow ( const int x ) {				//从顶点x开始深度优先搜索
		   num = 1;							// num是访问计数器, 是一个整型数据
		   dfn = new int[NumVertices];					// dfn是深度优先数, 是一个整型数组
		   low = new int[NumVertices];					// low是最小祖先访问顺序号, 是一个整型数组
		   for ( int i=0; i<NumVertices; i++ ) { dfn[i] = low[i] = 0; }
		   DfnLow ( x, -1 );
		   delete [ ] dfn;  delete [ ] low;
		}

template <class NameType, class DistType> 
void Graph<NameType,DistType>::DfnLow ( const int u, const int v ) {
		//从顶点u开始深度优先搜索计算dfn和low。在产生的生成树中v是u的双亲。
		   dfn[u] = low[u] = num++;					//给予访问计数器num及dfn[u], low[u]初值
		   int w = GetFirstNeighbor (u);
		   while ( w != -1 ) {						//对顶点u的所有邻接顶点w循环
			 if ( dfn[w] == 0 ) {					//未访问过, w是u的孩子
			   DfnLow ( w, u );					//递归深度优先搜索
			   low[u] = min2 ( low[u], low[w] );			//low[ ]的值是逆向计算, 先求出子女的再求自身
			 }
			 else if ( w != v )						//除去(u, v)边以外, (u, w)都是回边
				  low[u] = min2 ( low[u], dfn[w] );		//取两者中的小者
			 w = GetNextNeighbor (v, w);				//找顶点v的下一个邻接顶点
		   }
		}
template <class NameType, class DistType> 
void Graph<NameType,DistType>::Biconnected ( ) {
		   num = 1;								//访问计数器num是一个整型数据
		   dfn = new int[NumVertices];						// dfn是深度优先数, 是一个整型数组
		   low = new int[NumVertices];						// low是最小祖先顺序号, 是整型数组
		   for ( int i=0; i<NumVertices; i++ ) { dfn[i] = low[i] = 0; }
//		   DfnLow ( 0, -1 );							//从顶点0开始
		   Biconnected(0,-1);
		   delete [ ] dfn;  delete [ ] low;
		}

template <class NameType, class DistType> 
void Graph<NameType,DistType>::Biconnected ( const int u, const int v ) {
		//计算dfn与low, 并根据其重连通分量输出G的边。在产生的生成树中, v是u的父结点, S是一个初始为空的
		//栈, 它被声明为图的数据成员。
		   int w;
		   BiEdge e;
		   dfn[u] = low[u] = num++;		   
		   w = GetFirstNeighbor (u);						//找顶点u的第一个邻接顶点;
		   while ( w != - 1 ) {							//w是v的邻接顶点
			 if ( v != w && dfn[w] < dfn[u] ) S.Push ( BiEdge(u,w) );
			 if ( dfn[w] == 0 ) {						//未访问过, w是的孩子
			   Biconnected (w, u);						//递归深度优先访问
			   low[u] = min2 ( low[u], low[w] );
			   if ( low[w] >= dfn[u] ) {					//无回边, 原来的重连通分量结束
				 cout << "New Biconnected Component: " << endl;
				 do {
				   e = S.Pop ( );					//输出该重连通分量的各边 
	 			   cout << GetValue(e.a) <<"-"<<GetValue(e.b)<< endl;
				 } while ( !(e==BiEdge(u,w)));
			   }
			 }
			 else if ( w != v ) low[u] = min2 ( low[u], low[w] );		//有回边, 计算
			 w = GetNextNeighbor (u, w);					//找顶点v的下一个邻接顶点
		   }
		}