#include "iostream.h"
#include "p271.cpp"
template <class NameType, class DistType>
void Graph<NameType, DistType>::Components ( ) {        //确定图的连通分量
   int *visited = new int[NumVertices];			// visited记录顶点是否访问过
   for ( int i=0; i<NumVertices; i++ ) visited[i] = 0;	//初始化, 表示所有顶点未访问过
   for ( i=0; i<NumVertices; i++ )			//顺序扫描所有顶点
	 if ( !visited[i] ) {				//若没有访问过, 则访问这个连通分量
	   DFS ( i, visited );				//从顶点i开始访问
	   OutputNewComponent ( );			//输出这个连通分量
	 }
   delete [ ] visited;
}
void OutputNewComponent()
{
  cout<<endl<<"The nodes above is of a part."<<endl;
}