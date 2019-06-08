#include "p284b.cpp"
void Graph::AllLengths ( )
{
//Edge[n][n]是一个具有n个顶点的图的邻接矩阵。a[i][j]是顶点i和j之间的最短路径长度。path[i][j]是相应路
//径上顶点j的前一顶点的顶点号, 在求最短路径时图的类定义中要修改path为path[NumVertices][NumVertices]。
   for ( int i=0; i<n; i++ )
      for ( int j=0; j<n; j++ ) {							//矩阵a与path初始化
	 if (i!=j) dist[i][j] = Edge[i][j]; else dist[i][j]=0;
	 if ( i != j && dist[i][j] < MAXINT ) path[i][j] = i;			//有路径
	 else path[i][j] =-1;							// i到j无路径
      }
   for ( int k=0; k<n; k++ )							//产生a(k)及相应的path(k)
	 for ( i=0; i<n; i++ )
	   if (path[i][k]>=0)
	   for ( int j=0; j<n; j++ )
		 if
		 (
		  path[k][j]>=0 &&
		  dist[i][k] + dist[k][j] < dist[i][j] )
		 {
		   dist[i][j] = dist[i][k] + dist[k][j];
		   path[i][j] = path[k][j];		//缩短路径长度, 绕过k到j
		 }
}
