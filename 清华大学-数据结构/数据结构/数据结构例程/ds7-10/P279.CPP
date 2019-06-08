#include "P190.cpp"
#include "P223.cpp"
#include "P263.cpp"

template <class NameType, class DistType>
void Graph< NameType, DistType>::Kruskal ( MinSpanTree &T ) {	//克鲁斯卡尔算法
   MSTEdgeNode e;
   MinHeap<MSTEdgeNode> H (CurrentEdges );	//最小堆
   int NumVertices = VerticesList.Length();			//图中顶点个数
   UFSets F (NumVertices);			//连通分量
   for ( int u=0; u<NumVertices; u++ ) 			//建立最小堆的数据
	 for ( int v=u+1; v<NumVertices; v++ )
	   if ( Edge[u][v] != 0 ) {		//插入新边值结点到最小堆中
	   e.tail=u;e.head=v;e.key=Edge[u][v];
		 H.Insert (e);
	   }
   int count = 1;					//生成树边计数
   while ( count < NumVertices ) {			//反复执行, 取n-1条边
	 H.RemoveMin (e );				//从最小堆中退出具最小权值的边
	 int u = F.Find ( e.tail );
	 int v = F.Find ( e.head );			//取两顶点所在集合的根
	 if ( u != v ) {				//不是同一集合, 说明不连通
	   F.Union ( u, v );
	   T.addEdge(e.tail,e.head,e.key);
	   count++;	//合并, 连通它们, 该边加入生成树
	 }
   }
}



