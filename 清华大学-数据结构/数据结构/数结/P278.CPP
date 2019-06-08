#include "IOSTREAM.H"
#ifndef SetMaxVertices
#define SetMaxVertices
const int MaxNumVertices=10;
#endif

#ifndef MAXINT
#define MAXINT 32767		// 机器可表示的, 问题中不可能出现的大数
#endif

class MinSpanTree;			//最小生成树的前视类声明99

class MSTEdgeNode 
{			//最小生成树边结点的类声明
public:
	friend class MinSpanTree;
	friend ostream& operator <<(ostream& strm, MSTEdgeNode e);
private:
   int tail, head;				//两顶点位置
   int cost;					//边上的权值
};

class MinSpanTree {				//最小生成树的类定义
public:
   MinSpanTree ( int sz = MaxNumVertices-1 ) : MaxSize (sz), n (0),cost(0) { edgeValue = new MSTEdgeNode[MaxSize]; }
   void addEdge(int ,int ,int );
   friend ostream& operator <<(ostream& strm, MinSpanTree t);
private:
   MSTEdgeNode *edgeValue;			//用边值数组表示树
   int MaxSize, n,cost;				//数组的最大元素个数和当前个数
};
void MinSpanTree::addEdge(int tail,int head,int dist)//向生成树边值数组内存放
{
	   edgeValue[n].tail = tail;  
	   edgeValue[n].head = head;  
	   edgeValue[n].cost = dist;
	   cost=cost+dist;	   
	   n++;
}
ostream& operator <<(ostream& strm, MSTEdgeNode e)
{
	strm<<"("<<e.tail<<","<<e.head<<")";
	return strm;
}
ostream& operator <<(ostream& strm, MinSpanTree t)
{
	for (int i=0;i<t.n;i++)
		strm<<t.edgeValue[i];
	strm<<endl;
	strm<<"Total Cost="<<t.cost<<endl;
	return strm;
}
